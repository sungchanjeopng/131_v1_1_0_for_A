package com.wws2.densitymeter.viewmodel

import android.app.Application
import android.content.Context
import android.content.Intent
import android.os.PowerManager
import android.util.Log
import androidx.core.content.FileProvider
import androidx.lifecycle.AndroidViewModel
import android.os.Environment
import java.io.File
import androidx.lifecycle.viewModelScope
import com.wws2.densitymeter.model.*
import com.wws2.densitymeter.service.BleConnectionService
import com.wws2.densitymeter.service.BleForegroundService
import com.wws2.densitymeter.service.BleProtocolService
import kotlinx.coroutines.*
import kotlinx.coroutines.flow.*
import java.time.LocalDateTime
import java.time.format.DateTimeFormatter
import kotlin.math.min
import kotlin.math.sin
import kotlin.math.cos

private const val TAG = "MainVM"

enum class DeviceType { DENSITY, INTERFACE }
enum class EchoMode { REAL, AVG }

data class DataFileItem(
    val name: String,
    val recordCount: Int,
    val rangeLabel: String,
    val sizeBytes: Int,
    val targetDevice: String,
    val chartRecords: List<TrendRecord>,
    val allRecords: List<TrendRecord> = chartRecords,
)

enum class DataFilesStage { LIST, DOWNLOADING, COMPLETE, VIEW, ERROR }

data class MainUiState(
    val tabIndex: Int = 0,
    val subPage: String? = null, // "pairing", "download", "upload", "chatbot"

    val connectedDevices: List<ConnectedBleDevice> = emptyList(),
    val visibleDeviceIds: Set<String> = emptySet(), // Main ???????????
    val activeDeviceId: String = "",
    val activeDeviceLabel: String = "",
    val deviceReadings: Map<String, DeviceReading> = emptyMap(),
    val deviceEchoReadings: Map<String, EchoReading> = emptyMap(),

    val temperatureC: Double = 0.0,
    val currentMA: Double = 0.0,
    val damping: Int = 0,
    val set4mA: Double = 0.0,
    val set20mA: Double = 0.0,
    val pipeDia: Int = 0,
    val freqMHz: Double = 0.0,
    val tvg: Int = 0,
    val offset: Double = 0.0,
    val emptyDistance: Double = 0.0,
    val deadZone: Double = 0.0,
    val asf: Int = 0,
    val relay: Int = 0,
    val densUnit: Int = 0,
    val extIn1En: Int = 0,
    val extIn1State: Int = 0,
    val extIn2En: Int = 0,
    val extIn2State: Int = 0,

    val echoReading: EchoReading? = null,
    val interfaceEchoReading: InterfaceEchoReading? = null,
    val interfaceDiag: InterfaceDiagReading? = null,
    val echoMode: EchoMode = EchoMode.REAL, // ??傭?끆??????????룰퀡????????獄쏅챶留?? ???????댄뱼????????
    val rxBlink: Boolean = false,

    val trendRecords: List<TrendRecord> = emptyList(),
    val downloadRecords: List<TrendRecord> = emptyList(),
    val trendExpectedRecords: Int = 0,
    val isTrendStreaming: Boolean = false,
    val trendError: String? = null,

    // Upload
    val pickedFileName: String? = null,
    val pickedFileSize: Int? = null,
    // pickedBytes stored separately in ViewModel to avoid ByteArray in data class equals/hashCode
    val isUploading: Boolean = false,
    val uploadProgress: Double = 0.0,
    val uploadDone: Boolean = false,
    val uploadElapsed: Long = 0L, // ms
    val firmwareTargetDeviceId: String = "",

    // Data files
    val dataFilesStage: DataFilesStage = DataFilesStage.LIST,
    val activeDataFile: DataFileItem? = null,
    val dataDownloadProgress: Double = 0.0,
    val savedDataFiles: List<DataFileItem> = emptyList(),

    // Scan
    val connectingIds: Set<String> = emptySet(),

    // Device type (auto-detected from response LEN)
    val deviceType: DeviceType = DeviceType.DENSITY,
    // Interface meter reading (kept for Diag display)
    val interfaceReading: InterfaceReading? = null,

    // Calibration
    val calibrationPoints: List<com.wws2.densitymeter.model.CalibrationPoint> = emptyList(),

    // Units
    val tempUnit: Int = 0, // 0=Celsius, 1=Fahrenheit
)

class MainViewModel(application: Application) : AndroidViewModel(application) {

    val connectionService = BleConnectionService(application)
    private val protocolServices = mutableMapOf<String, BleProtocolService>()
    private val activeProtocol: BleProtocolService? get() = protocolServices[_state.value.activeDeviceId]

    private val _state = MutableStateFlow(MainUiState())
    val state: StateFlow<MainUiState> = _state.asStateFlow()

    // pickedBytes stored outside data class to avoid equals/hashCode issues with ByteArray
    private var pickedBytes: ByteArray? = null

    // Snackbar one-shot events
    private val _snackbarMessage = MutableSharedFlow<String>(extraBufferCapacity = 4)
    val snackbarMessage: SharedFlow<String> = _snackbarMessage

    // PIN request flow for device pairing (full-screen)
    private var pendingPinAddress: String? = null
    private val _showPinForPairing = MutableStateFlow(false)
    val showPinForPairing: StateFlow<Boolean> = _showPinForPairing

    // BLE error dialog
    data class BleError(val message: String, val retryAddress: String)
    private val _bleError = MutableStateFlow<BleError?>(null)
    val bleError: StateFlow<BleError?> = _bleError

    fun dismissBleError() { _bleError.value = null }
    fun retryBleError() {
        val err = _bleError.value ?: return
        _bleError.value = null
        pendingPinAddress = err.retryAddress
        _showPinForPairing.value = true
    }

    private var heartbeatJob: Job? = null
    private var notifyJob: Job? = null
    private var parseJob: Job? = null
    private var uploadTimerJob: Job? = null
    private var uploadJob: Job? = null
    @Volatile private var pageTransitionBlockedUntil: Long = 0L  // OTA 취소 후 5초 동안 페이지 전환 차단
    private var otaWakeLock: android.os.PowerManager.WakeLock? = null
    private var downloadTimerJob: Job? = null

    private val rxBuf = mutableListOf<Byte>()
    private var rxChannel = kotlinx.coroutines.channels.Channel<ByteArray>(kotlinx.coroutines.channels.Channel.UNLIMITED)
    private var parseSignal = kotlinx.coroutines.channels.Channel<Unit>(kotlinx.coroutines.channels.Channel.CONFLATED)
    private var trendTabFirstVisit = true
    private var trendTotalRecords = 0
    private var trendTotalChunks = 0
    private var trendChunkIndex = 0
    private var trendRunningCrc = 0xFFFF
    private var trendStreamState = 0
    private var trendTimeoutJob: Job? = null
    private var trendLastBufSize = -1
    // 다운로드 시작 시점에 pin된 device type. state.deviceType가 중간에 바뀌어도
    // 파싱 recSize가 엉키지 않도록 함 (multi-device scenario race 방지)
    private var trendIsInterface: Boolean = false
    private var rxMuted = false  // ???????ш내?℡ㅇ???????轅붽틓????嚥??????癲ル슢캉????
    private var otaStartAckDeferred: CompletableDeferred<Boolean>? = null
    private val otaStartAckBuf = mutableListOf<Byte>()
    private var uploadPreSyncDeferred: CompletableDeferred<Boolean>? = null
    private var trendStartRetryCount = 0

    // Interface Echo (??傭?끆??????????룰퀡??????????????? ???????轅붽틓????嚥?????????거?뜮?????遺븍き????鸚??
    private var ifEchoState = 0          // 0=idle, 1=collecting_chunks
    private var ifEchoN = 0              // ???????????
    private var ifEchoFullChunks = 0     // ???????? ??????(98????????
    private var ifEchoChunksDone = 0     // ?????밸븶筌믩끃??? ?? ??????
    private var ifEchoHeaderData = ByteArray(0)  // 28B ?????袁⑸즴筌? ?????獄쏅챶留???
    private val ifEchoWave = mutableListOf<Int>() // ?????獄쏅챶留?????????????????????
    private var ifEchoRunningCrc = 0xFFFF
    private var ifEchoCmd = 0

    init {
    }

    // ?????? Tab navigation ??????
    fun setTab(index: Int) {
        val s = _state.value
        // 트렌드/다운로드 스트리밍 중 탭 전환 차단
        if (s.isTrendStreaming) return
        // 펌웨어 업로드 중 + 취소 직후 5초 탭 전환 차단
        if (s.isUploading) return
        if (System.currentTimeMillis() < pageTransitionBlockedUntil) return
        if (s.tabIndex == 4 && s.subPage == "pairing") {
            connectionService.stopScan()
        }
        // 페이지 전환 시 잔여 RX 차단 + 버퍼 클리어
        rxMuted = true
        rxBuf.clear()
        ifEchoState = 0
        ifEchoWave.clear()
        // ??饔낅떽?????????????거?뜮????????硫멸킐???(??饔낅떽????????????????獄쏅챶留?????????Β????????????ш내?℡ㅇ????
        if (index != 2) {
            trendStreamState = 0
            _state.update { it.copy(isTrendStreaming = false) }
        }
        _state.update {
            it.copy(
                tabIndex = index,
                subPage = null,
                trendError = if (index == 2 && s.tabIndex != 2) null else it.trendError,
            ).let { updated ->
                if (index == 2 && s.tabIndex != 2) {
                    trendTabFirstVisit = true
                }
                updated
            }
        }
    }

    fun setSubPage(page: String?) {
        // 펌웨어 업로드 중 + 취소 직후 5초간 서브페이지 전환 차단
        if (_state.value.isUploading) return
        if (System.currentTimeMillis() < pageTransitionBlockedUntil) return
        _state.update { it.copy(subPage = page) }
    }

    // ?????? Heartbeat page index ??????
    // ??傭?끆??????????룰퀡???CH2: Main=0x08, Echo=0x07, Trend=0x09
    private val heartbeatPageIndex: Int
        get() {
            val s = _state.value
            val isCh2 = s.activeDeviceId.endsWith("_CH2")

            if (s.tabIndex == 4) {
                return when (s.subPage) {
                    "pairing" -> 5
                    "download" -> if (isCh2) 0x17 else 0x07  // ?????獄쏅챶留??????μ떜媛?걫??????癲????ル㎦??(?耀붾굝??????鶯? 10000??
                    "upload" -> 6
                    "calib" -> 0x03
                    else -> 4
                }
            }
            if (s.tabIndex == 3) return if (isCh2) 0x10 else 0x00 // Diag (Status 통합)
            return when (s.tabIndex) {
                0 -> if (isCh2) 0x10 else 0x00  // Main (Status)
                1 -> {
                    val isAvg = s.echoMode == EchoMode.AVG && s.deviceType == DeviceType.INTERFACE
                    if (isCh2) { if (isAvg) 0x15 else 0x11 } else { if (isAvg) 0x05 else 0x01 }
                }  // Echo
                2 -> if (isCh2) 0x10 else 0x00  // Trend (Status 실시간)
                else -> s.tabIndex
            }
        }

    // ?????? Echo ?耀붾굝?????????붾눀?????? (??傭?끆??????????룰퀡????????獄쏅챶留?? ??????
    fun setEchoMode(mode: EchoMode) {
        _state.update { it.copy(echoMode = mode) }
    }

    // ?????? Main ???????????곌떽?댁젢?????????? ??????
    fun toggleDeviceVisibility(deviceId: String) {
        _state.update {
            val current = it.visibleDeviceIds
            val updated = if (deviceId in current) {
                if (current.size > 1) current - deviceId else current // ?耀붾굝??????鶯??1?????ル뒌???????
            } else {
                current + deviceId
            }
            it.copy(visibleDeviceIds = updated)
        }
    }

    fun cycleDensityUnit() {
        val current = com.wws2.densitymeter.model.DensityUnit.fromInt(_state.value.densUnit)
        _state.update { it.copy(densUnit = current.next().ordinal) }
    }


    fun cycleTemperatureUnit() {
        val current = com.wws2.densitymeter.model.TemperatureUnit.fromInt(_state.value.tempUnit)
        _state.update { it.copy(tempUnit = current.next().ordinal) }
    }

    fun openCalib() {
        _state.update { it.copy(tabIndex = 4, subPage = "calib") }
    }

    private fun appSettingCmd(baseCmd: Int): Int {
        return if (_state.value.activeDeviceId.endsWith("_CH2")) baseCmd + 1000 else baseCmd
    }

    fun sendAppSetting(baseCmd: Int, value: Int) {
        val proto = activeProtocol
        if (proto == null) {
            _snackbarMessage.tryEmit("No active device.")
            return
        }
        viewModelScope.launch {
            val cmd = appSettingCmd(baseCmd)
            val ok = proto.write(proto.buildSettingFrame(cmd, value), withoutResponse = false)
            _snackbarMessage.tryEmit(if (ok) "Setting sent." else "Setting failed.")
        }
    }

    // ?????? BLE Pairing ??????
    fun openPairing() {
        _state.update { it.copy(tabIndex = 4, subPage = "pairing") }
        // Don't start scan here - PairingScreen handles permissions first
    }

    fun requestConnectDevice(address: String) {
        val s = _state.value
        // Already connected? Just activate.
        val existing = s.connectedDevices.find { it.id == address }
        if (existing != null) {
            viewModelScope.launch { activateDevice(address) }
            return
        }
        if (s.connectedDevices.size >= 4) {
            _snackbarMessage.tryEmit("Up to 4 devices can be connected.")
            return
        }
        // Require PIN before connecting new device
        pendingPinAddress = address
        _showPinForPairing.value = true
    }

    fun onPairingPinResult(pin: Int) {
        _showPinForPairing.value = false
        val address = pendingPinAddress
        pendingPinAddress = null
        if (pin < 0 || address == null) return  // pin < 0 = ??????
        performConnect(address, pin)
    }

    private fun performConnect(address: String, pin: Int = 0) {
        _state.update { it.copy(connectingIds = it.connectingIds + address) }

        viewModelScope.launch {
            try {
                connectionService.stopScan()

                val device = connectionService.getRemoteDevice(address) ?: return@launch

                // Retry up to 3 times — Android BLE often returns status 133 on 1st attempt,
                // and the peer module may need a moment to recover from a prior session.
                val maxAttempts = 3
                var protocol: BleProtocolService? = null
                var ok = false
                for (attempt in 1..maxAttempts) {
                    protocol = BleProtocolService(getApplication())
                    ok = protocol.connect(device)
                    if (ok) {
                        Log.d(TAG, "Connect succeeded on attempt $attempt for $address")
                        break
                    }
                    Log.w(TAG, "Connect attempt $attempt/$maxAttempts failed for $address")
                    try { protocol.disconnect() } catch (_: Exception) {}
                    protocol = null
                    if (attempt < maxAttempts) delay(1000)
                }

                if (!ok || protocol == null) {
                    _bleError.value = BleError("Could not connect to device.", address)
                    return@launch
                }
                val proto: BleProtocolService = protocol!!  // smart-cast helper for var

                protocolServices[address] = proto

                // ?????? Pairing Protocol: PIN ??汝뷴젆?琉????+ ?????????곌떽?댁젢???饔낅떽????????????椰???(0xF0) ??????
                var fwVersion = ""
                var isInterface = false
                var siteName = ""
                delay(300)  // BLE notification ????μ떜媛?걫????????
                // ?耀붾굝??????鶯? 2?????轅붽틓?????
                var pairingResult = requestPairing(proto, pin)
                if (pairingResult == null) {
                    delay(500)
                    pairingResult = requestPairing(proto, pin)
                }
                when (pairingResult) {
                    is BleProtocolService.PairingResult.PinFailed -> {
                        proto.disconnect()
                        protocolServices.remove(address)
                        _bleError.value = BleError("PIN code incorrect.", address)
                        return@launch
                    }
                    is BleProtocolService.PairingResult.Success -> {
                        val deviceInfo = pairingResult.deviceInfo
                        fwVersion = deviceInfo.fwVersion.toString()
                        val hi = deviceInfo.siteNameHi
                        val lo = deviceInfo.siteNameLo
                        siteName = if (hi in 'A'..'Z' && lo in 0..99)
                            "${hi}${"%02d".format(lo)}" else ""
                        Log.d(TAG, "Pairing OK: site=$siteName (hi=0x${"%02X".format(hi.code)}, lo=$lo), fw=$fwVersion")
                    }
                    null -> {
                        Log.w(TAG, "Pairing protocol timeout, fallback to BLE name parsing")
                    }
                }

                // BLE ??????????????????곌떽?댁젢??????????
                val scanInfo = connectionService.scannedDevices.value[address]
                val bleName = scanInfo?.rawName ?: scanInfo?.name ?: ""
                val upper = bleName.uppercase()
                isInterface = upper.startsWith("W3") || upper.contains("WE13") || upper.contains("ENV130")

                // ???轅붽틓????????긺춯癒?뼔?????????獄쏅챶留?????BLE ?????????FW ???????fallback
                if (fwVersion.isEmpty()) {
                    fwVersion = extractFirmwareVersion(bleName)
                }

                if (isInterface) {
                    // Interface meter: create 2 virtual devices (CH1, CH2)
                    val ch1Id = "${address}_CH1"
                    val ch2Id = "${address}_CH2"
                    // ????癲ル슢??????饔낅떽?????????????????????곌떽?댁젢??壤굿?????????筌뤾퍜???????ル뒌????饔낅떽?????嶺뚮ㅎ?닺짆?汝뷴젆????? ???????ㅻ쑄?癲ル슢캉??뮻????轅붽틓????????긺춯癒?뼔??fallback
                    val ch1Site = scanInfo?.ch1SiteName ?: ""
                    val ch2Site = scanInfo?.ch2SiteName ?: ""
                    val ch1Label = if (ch1Site.isNotEmpty()) "ENV130_$ch1Site"
                        else allocateInterfaceLabels(_state.value.connectedDevices).first
                    // Only create CH2 when the device actually advertises a CH2 site name.
                    // (Dual-channel mode vs single-channel mode is decided by whether ch2Site is present.)
                    protocolServices[ch1Id] = proto
                    val ch1Dev = ConnectedBleDevice(id = ch1Id, label = ch1Label, device = device, firmwareVersion = fwVersion, deviceType = 1)

                    if (ch2Site.isNotEmpty()) {
                        val ch2Label = "ENV130_$ch2Site"
                        protocolServices[ch2Id] = proto
                        val ch2Dev = ConnectedBleDevice(id = ch2Id, label = ch2Label, device = device, firmwareVersion = fwVersion, deviceType = 1)
                        _state.update {
                            it.copy(
                                connectedDevices = it.connectedDevices + ch1Dev + ch2Dev,
                                visibleDeviceIds = it.visibleDeviceIds + ch1Id + ch2Id,
                            )
                        }
                    } else {
                        _state.update {
                            it.copy(
                                connectedDevices = it.connectedDevices + ch1Dev,
                                visibleDeviceIds = it.visibleDeviceIds + ch1Id,
                            )
                        }
                    }
                    activateDevice(ch1Id)
                } else {
                    // Density meter: 1?????ル뒌??亦껋꼦維뽬뜎??????????⑤벡瑜??(????癲ル슢???????????? _D1/_D2???????Β?レ름????
                    val ch1Site = scanInfo?.ch1SiteName ?: ""
                    val label = when {
                        siteName.isNotEmpty() -> "ENV230_$siteName"
                        ch1Site.isNotEmpty() -> "ENV230_$ch1Site"
                        else -> allocateLabel()
                    }
                    val connected = ConnectedBleDevice(id = address, label = label, device = device, firmwareVersion = fwVersion)
                    _state.update {
                        it.copy(
                            connectedDevices = it.connectedDevices + connected,
                            visibleDeviceIds = it.visibleDeviceIds + address,
                        )
                    }
                    activateDevice(address)
                }
                startForegroundService()

                // BLE ??????⑤벡瑜?????????ㅻ쑋???????ル뒌??? ???????disconnect ?耀붾굝????鶯ㅺ동??筌믡룓愿??
                viewModelScope.launch {
                    proto.connectionState.collect { connected ->
                        if (!connected) {
                            Log.w(TAG, "BLE disconnected: $address")
                            disconnectDevice(address)
                            if (isInterface) {
                                disconnectDevice("${address}_CH1")
                                disconnectDevice("${address}_CH2")
                            }
                        }
                    }
                }

                if (_state.value.subPage == "pairing") {
                    connectionService.startScan()
                }
            } catch (e: Exception) {
                Log.e(TAG, "Connect failed: ${e.message}")
                _bleError.value = BleError(e.message ?: "Unknown error", address)
            } finally {
                _state.update { it.copy(connectingIds = it.connectingIds - address) }
            }
        }
    }

    fun disconnectDevice(id: String) {
        viewModelScope.launch {
            val s = _state.value
            // Find sibling virtual device (interface: _CH1 ??_CH2, density: _D1 ??_D2)
            val siblingId = when {
                id.endsWith("_CH1") -> id.replace("_CH1", "_CH2")
                id.endsWith("_CH2") -> id.replace("_CH2", "_CH1")
                else -> null
            }
            val rawAddress = id.replace("_CH1", "").replace("_CH2", "")
            val idsToRemove = listOfNotNull(id, siblingId)

            val wasActive = id == s.activeDeviceId || siblingId == s.activeDeviceId
            val wasFirmwareTarget = s.firmwareTargetDeviceId in idsToRemove

            if (wasActive) {
                stopHeartbeat()
                notifyJob?.cancel()
                parseJob?.cancel()
            }

            // Disconnect the actual BLE connection (once, shared protocol)
            val proto = protocolServices[id] ?: protocolServices[rawAddress]
            proto?.disconnect()
            idsToRemove.forEach { protocolServices.remove(it) }
            protocolServices.remove(rawAddress)

            _state.update { st ->
                val newDevices = st.connectedDevices.filter { it.id !in idsToRemove }
                val newReadings = st.deviceReadings - idsToRemove.toSet()
                val newEchos = st.deviceEchoReadings - idsToRemove.toSet()

                var updated = st.copy(
                    connectedDevices = newDevices,
                    deviceReadings = newReadings,
                    deviceEchoReadings = newEchos,
                )

                if (wasFirmwareTarget) {
                    pickedBytes = null
                    updated = updated.copy(
                        firmwareTargetDeviceId = "",
                        pickedFileName = null, pickedFileSize = null,
                        isUploading = false, uploadDone = false, uploadProgress = 0.0, uploadElapsed = 0,
                    )
                }

                if (wasActive) {
                    updated = updated.copy(activeDeviceId = "", activeDeviceLabel = "")
                }

                if (newDevices.isEmpty()) {
                    updated = resetLiveData(updated)
                    stopForegroundService()
                }

                updated
            }

            if (wasActive && _state.value.connectedDevices.isNotEmpty()) {
                activateDevice(_state.value.connectedDevices.first().id)
            }

            if (_state.value.subPage == "pairing") {
                connectionService.startScan()
            }
        }
    }

    private suspend fun activateDevice(id: String) {
        val s = _state.value
        val session = s.connectedDevices.find { it.id == id } ?: return
        val cachedReading = s.deviceReadings[id]
        val cachedEcho = s.deviceEchoReadings[id]

        stopHeartbeat()
        notifyJob?.cancel()
        parseJob?.cancel()

        _state.update { st ->
            var updated = st.copy(
                activeDeviceId = session.id,
                activeDeviceLabel = session.label,
                echoReading = cachedEcho,
                deviceType = if (session.deviceType == 1) DeviceType.INTERFACE else DeviceType.DENSITY,
            )
            if (cachedReading != null) {
                updated = updated.copy(
                    temperatureC = cachedReading.temperature,
                    currentMA = cachedReading.currentMA,
                    damping = cachedReading.damping,
                    set4mA = cachedReading.set4mA,
                    set20mA = cachedReading.set20mA,
                    pipeDia = cachedReading.pipeDia,
                    freqMHz = cachedReading.freqMHz,
                )
            }
            updated
        }
        trendTabFirstVisit = true

        listenNotifications(id)
        startHeartbeat()
    }

    // ?????? Heartbeat (????椰??????????????1??????? ??????

    private fun startHeartbeat() {
        stopHeartbeat()
        heartbeatJob = viewModelScope.launch {
            while (isActive) {
                val s = _state.value
                if (s.isUploading || s.isTrendStreaming) { delay(1000); continue }
                val proto = activeProtocol
                if (proto == null) { delay(1000); continue }

                var pageIndex = heartbeatPageIndex
                // ?耀붾굝??????????????? heartbeat ???????곕츥????(???轅붽틓????????긺춯癒?뼔??????μ떜媛?걫??????癲????ル㎦??????????轅붽틓???????????곕츥????
                if (s.tabIndex == 4 && s.subPage in listOf("chatbot", null)) {
                    if (rxMuted) { rxBuf.clear(); rxMuted = false }
                    delay(1000); continue
                }
                // Trend: ?耀붾굝??????鶯??1??????????獄쏅챶留덌┼??뭬?怨좊뭽? ??????諛몃마??heartbeat ???????곕츥????
                if ((pageIndex == 0x02 || pageIndex == 0x12)) {
                    if (trendTabFirstVisit && _state.value.trendRecords.isEmpty()) {
                        pageIndex = if (pageIndex == 0x12) 0x0012 else 0x0002
                        trendTabFirstVisit = false
                        rxBuf.clear()
                        trendStreamState = 1
                        trendStartRetryCount = 0
                        _state.update { it.copy(isTrendStreaming = true, trendRecords = emptyList(), trendError = null) }
                        startTrendTimeout(proto)
                    } else if (trendTabFirstVisit) {
                        trendTabFirstVisit = false
                        pageIndex = 0x00
                    } else {
                        pageIndex = 0x00// ??饔낅떽?????????????轅붽틓??????heartbeat ???????곕츥????
                    }
                }
                // Download: startDataDownload()??????耀붾굝????????耀붾굝????鶯ㅺ동??筌믡룓愿?? heartbeat???????????곕츥????????繹먮겧?? ???????깅즿??
                if (pageIndex == 0x07 || pageIndex == 0x17) {
                    delay(1000); continue
                }

                if (s.tabIndex == 4 && s.subPage == "upload") {
                    delay(1000); continue
                }
                proto.sendHeartbeat(pageIndex)
                if (rxMuted) {
                    rxBuf.clear()
                    rxMuted = false  // cmd ?????곕츥?????????轅붽틓????嚥???????
                }
                delay(1000)
            }
        }
    }

    private fun stopHeartbeat() {
        heartbeatJob?.cancel()
        heartbeatJob = null
    }

    // ?????? Notification listener ??????
    private fun listenNotifications(deviceId: String) {
        notifyJob?.cancel()
        parseJob?.cancel()
        rxBuf.clear()
        parseSignal.close()
        parseSignal = kotlinx.coroutines.channels.Channel(kotlinx.coroutines.channels.Channel.CONFLATED)

        val proto = protocolServices[deviceId] ?: return

        // ???轅붽틓????嚥????????獄쏅챶留?? rxBuf???????쇰뮡????????????????욧펾??븐낯筌???얜????????곕츥????
        notifyJob = viewModelScope.launch {
            proto.notifications.collect { chunk ->
                val preSyncWaiter = uploadPreSyncDeferred
                if (preSyncWaiter != null && !preSyncWaiter.isCompleted && chunk.isNotEmpty()) {
                    Log.d(TAG, "Upload pre-sync response observed in general listener")
                    preSyncWaiter.complete(true)
                }
                val otaAckWaiter = otaStartAckDeferred
                if (otaAckWaiter != null && !otaAckWaiter.isCompleted) {
                    otaStartAckBuf.addAll(chunk.toList())
                    if (otaStartAckBuf.size > 256) {
                        otaStartAckBuf.subList(0, otaStartAckBuf.size - 256).clear()
                    }
                    if (proto.indexOfSubsequence(otaStartAckBuf.toByteArray(), byteArrayOf(0x02, 0x00, 0x50)) >= 0) {
                        Log.d(TAG, "OTA start ACK matched in general listener")
                        otaStartAckBuf.clear()
                        otaAckWaiter.complete(true)
                    }
                }
                if (rxMuted) {
                    Log.w(TAG, "[DBG] rxMuted=true, dropping ${chunk.size}B")
                    return@collect
                }
                // Skip UI blink update during trend streaming / download — the
                // state.update → Compose recomposition chain is slow enough that
                // it can cause SharedFlow back-pressure and notification drops
                // when bursts arrive (dual-device scenario).
                if (trendStreamState == 0) {
                    _state.update { it.copy(rxBlink = !it.rxBlink) }
                }
                rxBuf.addAll(chunk.toList())
                Log.d(TAG, "[DBG] rxBuf+=${chunk.size}B total=${rxBuf.size}")
                val maxBuf = if (trendStreamState > 0) 120000 else 8000
                if (rxBuf.size > maxBuf) {
                    rxBuf.subList(0, rxBuf.size - maxBuf / 2).clear()
                }
                parseSignal.trySend(Unit)
            }
        }

        // ??????????獄쏅챶留?? ???????욧펾???????????????????癲??????
        parseJob = viewModelScope.launch {
            for (unit in parseSignal) {
                if (trendStreamState > 0) {
                    tryParseTrend(proto)
                } else {
                    tryParseFrame(proto, deviceId)
                }
            }
        }
    }

    // CMD????????DATA ????(CRC ???轅붽틓?????
    private fun expectedDataSize(cmd: Int): Int {
        val isIf = _state.value.deviceType == DeviceType.INTERFACE
        return when (cmd) {
            0x0000, 0x0010 -> if (isIf) 200 else 34  // Status: 농도계 34B / 계면계 200B (DATA 26B + 174B 예약, 앞 26B만 사용)
            0x0001 -> if (isIf) -1 else 224         // Echo: CRC fallback으로 226B 자동 검출
            0x0003 -> 80                             // Calib (16B x 5pts)
            0x0004, 0x0014 -> if (isIf) 22 else 16  // ??傭?끆??????????룰퀡???Diag=22B, ????癲????16B
            else -> -1
        }
    }

    private fun crc16Update(crc: Int, b: Byte): Int {
        var c = crc xor (b.toInt() and 0xFF)
        repeat(8) { c = if (c and 0x0001 != 0) (c ushr 1) xor 0xA001 else c ushr 1 }
        return c
    }

    private fun tryParseFrame(proto: BleProtocolService, deviceId: String) {
        // ??傭?끆??????????룰퀡??????????????????????轅붽틓????嚥????????袁ⓦ걤???ш낄猷??????????????耀붾굝????鶯ㅺ동??筌믡룓愿????????耀붾굝??????μ떜媛?걫????
        if (ifEchoState == 1) {
            tryParseIfEchoChunks(deviceId)
            return
        }

        while (rxBuf.size >= 7) {
            // SOF(0x02) ?耀붾굝????????됰Ŧ瑗????ъ젢?
            if (rxBuf[0] != 0x02.toByte()) {
                val idx = rxBuf.indexOfFirst { it == 0x02.toByte() }
                if (idx < 0) { rxBuf.clear(); return }
                rxBuf.subList(0, idx).clear()
                if (rxBuf.size < 7) return
            }

            val cmd = ((rxBuf[1].toInt() and 0xFF) shl 8) or (rxBuf[2].toInt() and 0xFF)

            // ??傭?끆??????????룰퀡????????????????????袁⑸즴筌?: ?????????獄쏅챶留덌┼??뭬?怨좊뭽??????獄쏅챶留??貫?????????먃????곕선?????????곕츥??????耀붾굝????鶯ㅺ동??筌믡룓愿??
            if ((cmd == 0x0001 || cmd == 0x0011 || cmd == 0x0005 || cmd == 0x0015)
                && _state.value.deviceType == DeviceType.INTERFACE) {
                if (rxBuf.size < 203) return  // 헤더 패킷 = SOF(1)+CMD(2)+DATA(200, 30B+170B 패딩)  // ?????袁⑸즴筌? ?????35B ????
                val headerPkt = ByteArray(203) { rxBuf[it] }
                rxBuf.subList(0, 203).clear()

                // 28B ?????獄쏅챶留?????????꾨굴???(SOF+CMD 3B ??????諛몃마?? ?????嶺뚮ㅎ?댐쭕?4B ???轅붽틓???????bytes[3..30])
                ifEchoHeaderData = headerPkt.copyOfRange(3, 33)

                // N = empty ??1.1, ?耀붾굝??????鶯? 1100 (ADC_BUFF_MAX)
                val emptyVal = ((ifEchoHeaderData[6].toInt() and 0xFF) shl 8) or
                               (ifEchoHeaderData[7].toInt() and 0xFF)
                ifEchoN = minOf((emptyVal * 1.1).toInt(), 1100)
                if (ifEchoN == 0) ifEchoN = 1

                ifEchoFullChunks = ifEchoN / 98
                ifEchoChunksDone = 0
                ifEchoWave.clear()
                ifEchoCmd = cmd

                // CRC ??????硫멸킐??? ?????袁⑸즴筌? 31B (SOF+CMD+28B ?????獄쏅챶留??? ?????獄쏅챶留??
                ifEchoRunningCrc = 0xFFFF
                for (i in 0 until 203) {
                    ifEchoRunningCrc = crc16Update(ifEchoRunningCrc, headerPkt[i])
                }

                ifEchoState = 1
                tryParseIfEchoChunks(deviceId)
                return
            }

            val expectedData = expectedDataSize(cmd)
            val primaryLen = if (expectedData >= 0) 3 + expectedData + 2 else 7
            Log.d(TAG, "[DBG] cmd=0x%04X expectedData=%d primaryLen=%d rxBuf=%d".format(cmd, expectedData, primaryLen, rxBuf.size))

            if (rxBuf.size < primaryLen) return

            var frameBytes = ByteArray(primaryLen) { rxBuf[it] }
            var parsed = proto.parseFrame(frameBytes)
            var totalLen = primaryLen

            // CRC 실패 시 대체 크기 시도 (펌웨어 버전에 따라 데이터 크기 다를 수 있음)
            if (parsed == null && expectedData >= 0) {
                for (extra in listOf(2, 4, 6)) {
                    val altLen = primaryLen + extra
                    if (rxBuf.size < altLen) break
                    val altBytes = ByteArray(altLen) { rxBuf[it] }
                    val p = proto.parseFrame(altBytes)
                    if (p != null) {
                        parsed = p
                        totalLen = altLen
                        Log.d(TAG, "[DBG] CRC fallback OK at +$extra => totalLen=$altLen dataSize=${p.data.size}")
                        break
                    }
                }
            }

            if (parsed != null) {
                Log.d(TAG, "[DBG] PARSED cmd=0x%04X dataSize=${parsed.data.size} totalLen=$totalLen".format(parsed.cmd))
                rxBuf.subList(0, totalLen).clear()
            } else {
                Log.w(TAG, "[DBG] CRC FAIL cmd=0x%04X, skip 1 byte".format(cmd))
                rxBuf.removeAt(0)
                continue
            }

            // 확장 데이터를 기존 핸들러 호환 크기로 정규화 (계면계/Diag만 — 농도계 Status/Echo는 전체 수신)
            val isIf = _state.value.deviceType == DeviceType.INTERFACE
            val normSize = when {
                (parsed.cmd == 0x0004 || parsed.cmd == 0x0014) && parsed.data.size > 22 ->
                    if (isIf) 22 else 16
                else -> -1
            }
            if (normSize > 0 && parsed.data.size > normSize) {
                parsed = BleProtocolService.ParsedFrame(parsed.cmd, parsed.data.copyOf(normSize))
            }

            // ?????? CMD ???????癲??됀??????????????Β?レ름?????????

            // Status: CMD=0x0000 / CMD=0x0010
            if (parsed.cmd == 0x0000 || parsed.cmd == 0x0010) {
                Log.d(TAG, "[DBG] STATUS handler: dataSize=${parsed.data.size} deviceId=$deviceId isIf=${_state.value.deviceType == DeviceType.INTERFACE}")
                if (parsed.data.size == 4) {
                    val dst = (((parsed.data[0].toInt() and 0xFF) shl 8) or (parsed.data[1].toInt() and 0xFF)).toDouble()
                    val errorCode = ((parsed.data[2].toInt() and 0xFF) shl 8) or (parsed.data[3].toInt() and 0xFF)
                    val reading = DeviceReading(
                        level = dst,
                        temperature = 0.0, currentMA = 0.0, damping = 0,
                        set4mA = 0.0, set20mA = 0.0, pipeDia = 0, freqMHz = 0.0,
                        errorCode = errorCode,
                    )
                    _state.update { st -> st.copy(deviceReadings = st.deviceReadings + (deviceId to reading)) }
                } else if (_state.value.deviceType == DeviceType.INTERFACE && parsed.data.size >= 26) {
                    val buf = java.nio.ByteBuffer.wrap(parsed.data).order(java.nio.ByteOrder.BIG_ENDIAN)
                    val light = (buf.short.toInt() and 0xFFFF).toDouble()
                    val heavy = (buf.short.toInt() and 0xFFFF).toDouble()
                    val temperature = buf.short.toInt() * 0.1
                    val currentMA = (buf.short.toInt() and 0xFFFF) * 0.01
                    // 계면계 FREQ: 인덱스 0/1/2/3 → 380/270/160/130 kHz
                    val freqIdx = buf.short.toInt() and 0xFFFF
                    val freq = when (freqIdx) { 0 -> 380; 1 -> 270; 2 -> 160; 3 -> 130; else -> 0 }
                    val offset = buf.short.toInt()
                    val set4mA = (buf.short.toInt() and 0xFFFF) * 0.01
                    val set20mA = (buf.short.toInt() and 0xFFFF) * 0.01
                    val tvg = buf.short.toInt() and 0xFFFF
                    val damping = buf.short.toInt() and 0xFFFF
                    val asf = buf.short.toInt() and 0xFFFF
                    val relay = buf.short.toInt() and 0xFFFF
                    val errorCode = buf.short.toInt() and 0xFFFF
                    val echoAmpReserved = if (parsed.data.size >= 28) buf.short.toInt() and 0xFFFF else 0
                    val emptyDistance = if (parsed.data.size >= 30) (buf.short.toInt() and 0xFFFF) * 0.01 else _state.value.emptyDistance
                    val deadZone = if (parsed.data.size >= 32) (buf.short.toInt() and 0xFFFF) * 0.01 else _state.value.deadZone
                    val reading = DeviceReading(
                        level = light, heavyLevel = heavy,
                        temperature = temperature, currentMA = currentMA,
                        damping = damping, set4mA = set4mA, set20mA = set20mA,
                        pipeDia = 0, freqMHz = freq * 0.001, errorCode = errorCode,
                    )
                    _state.update { st ->
                        st.copy(
                            deviceReadings = st.deviceReadings + (deviceId to reading),
                            temperatureC = temperature,
                            currentMA = currentMA,
                            damping = damping,
                            set4mA = set4mA,
                            set20mA = set20mA,
                            freqMHz = freq * 0.001,
                            tvg = tvg,
                            offset = offset * 0.01,
                            emptyDistance = emptyDistance,
                            deadZone = deadZone,
                            asf = asf,
                            relay = relay,
                        )
                    }
                    if (!_state.value.isTrendStreaming && !_state.value.isUploading) {
                        val newRecord = TrendRecord(
                            dateTime = java.time.LocalDateTime.now(),
                            eeaD = heavy.toInt(),
                            dst = light,
                            temperature = temperature,
                            deviceId = deviceId,
                        )
                        _state.update { st ->
                            val updated = (st.trendRecords + newRecord).let {
                                if (it.size > 10000) it.drop(it.size - 10000) else it
                            }
                            st.copy(trendRecords = updated)
                        }
                    }
                } else if (parsed.data.size >= 22) {
                    val buf = java.nio.ByteBuffer.wrap(parsed.data).order(java.nio.ByteOrder.BIG_ENDIAN)
                    val dst = (buf.short.toInt() and 0xFFFF).toDouble()
                    val eeaD = buf.short.toInt() and 0xFFFF
                    val eeaR = buf.short.toInt() and 0xFFFF
                    val temperature = buf.short.toInt() * 0.1  // signed
                    val currentMA = (buf.short.toInt() and 0xFFFF) * 0.01
                    val damping = buf.short.toInt() and 0xFFFF
                    val set4mA = (buf.short.toInt() and 0xFFFF).toDouble()
                    val set20mA = (buf.short.toInt() and 0xFFFF).toDouble()
                    val pipeDia = buf.short.toInt() and 0xFFFF
                    val freqMHz = (buf.short.toInt() and 0xFFFF) * 0.001
                    val errorCode = buf.short.toInt() and 0xFFFF
                    // 34B: relay + densUnit + ext{1,2}{En,State}
                    val relay = if (parsed.data.size >= 24) buf.short.toInt() and 0xFFFF else 0
                    val densUnit = if (parsed.data.size >= 26) buf.short.toInt() and 0xFFFF else 0
                    val extIn1En = if (parsed.data.size >= 28) buf.short.toInt() and 0xFFFF else 0
                    val extIn1State = if (parsed.data.size >= 30) buf.short.toInt() and 0xFFFF else 0
                    val extIn2En = if (parsed.data.size >= 32) buf.short.toInt() and 0xFFFF else 0
                    val extIn2State = if (parsed.data.size >= 34) buf.short.toInt() and 0xFFFF else 0
                    Log.d(TAG, "[DBG] DENSITY STATUS: dst=%.2f eeaD=%d eeaR=%d temp=%.1f mA=%.2f err=%d".format(dst, eeaD, eeaR, temperature, currentMA, errorCode))

                    val reading = DeviceReading(level = dst, eeaR = eeaR, eeaD = eeaD, pipeDia = pipeDia, freqMHz = freqMHz,
                        temperature = temperature, currentMA = currentMA, damping = damping,
                        set4mA = set4mA, set20mA = set20mA, errorCode = errorCode,
                    )
                    _state.update { st ->
                        st.copy(
                            deviceReadings = st.deviceReadings + (deviceId to reading),
                            temperatureC = temperature,
                            currentMA = currentMA,
                            damping = damping,
                            set4mA = set4mA,
                            set20mA = set20mA,
                            pipeDia = pipeDia,
                            freqMHz = freqMHz,
                            relay = relay,
                            densUnit = densUnit,
                            extIn1En = extIn1En,
                            extIn1State = extIn1State,
                            extIn2En = extIn2En,
                            extIn2State = extIn2State,
                        )
                    }

                    // Real-time append (when not streaming)
                    if (!_state.value.isTrendStreaming && !_state.value.isUploading) {
                        val newRecord = TrendRecord(
                            dateTime = java.time.LocalDateTime.now(),
                            eeaD = eeaD,
                            dst = dst,
                            temperature = temperature,
                            deviceId = deviceId,
                        )
                        _state.update { st ->
                            val updated = (st.trendRecords + newRecord).let {
                                if (it.size > 10000) it.drop(it.size - 10000) else it
                            }
                            st.copy(trendRecords = updated)
                        }
                    }
                }
            }

            // Density Echo: CMD=0x0001, 222B~226B (err 뒤 tmp 2B, wave 앞)
            if (parsed.cmd == 0x0001 && parsed.data.size >= 222) {
                Log.d(TAG, "[DBG] ECHO handler: dataSize=${parsed.data.size}")
                // 온도는 offset 14-15 (err 뒤, wave 앞) → 제거하고 220B로 EchoReading 파싱
                val echoData = parsed.data.copyOfRange(0, 14) + parsed.data.copyOfRange(16, 222)
                // 224B: densUnit, 226B: sampleUs (x0.01µs, e.g. 320 = 3.20µs)
                val densUnit = if (parsed.data.size >= 224)
                    ((parsed.data[222].toInt() and 0xFF) shl 8) or (parsed.data[223].toInt() and 0xFF) else 0
                val sampleUsRaw = if (parsed.data.size >= 226)
                    ((parsed.data[224].toInt() and 0xFF) shl 8) or (parsed.data[225].toInt() and 0xFF) else 0
                val sampleUs = if (sampleUsRaw > 0) sampleUsRaw / 100.0f else 2.0f
                val echo = EchoReading.fromBytes(echoData, sampleUs)
                if (echo == null) { Log.w(TAG, "[DBG] EchoReading.fromBytes FAILED echoData.size=${echoData.size}"); continue }
                val rawTemp = ((parsed.data[14].toInt() and 0xFF) shl 8) or (parsed.data[15].toInt() and 0xFF)
                val tempSigned = if (rawTemp > 32767) rawTemp - 65536 else rawTemp
                val temperature = tempSigned * 0.1
                _state.update { st ->
                    st.copy(deviceEchoReadings = st.deviceEchoReadings + (deviceId to echo),
                        echoReading = echo, densUnit = densUnit)
                }
                if (!_state.value.isTrendStreaming && !_state.value.isUploading) {
                    val newRecord = TrendRecord(
                        dateTime = java.time.LocalDateTime.now(),
                        eeaD = echo.eeaD,
                        dst = echo.level,
                        temperature = temperature,
                        deviceId = deviceId,
                    )
                    _state.update { st ->
                        val updated = (st.trendRecords + newRecord).let {
                            if (it.size > 10000) it.drop(it.size - 10000) else it
                        }
                        st.copy(trendRecords = updated)
                    }
                }
            }

            // Calib: CMD=0x0003, 80B (16B x 5pts)
            if (parsed.cmd == 0x0003 && parsed.data.size >= 80) {
                val pts = com.wws2.densitymeter.model.CalibrationPoint.fromBytes(parsed.data)
                if (pts != null) {
                    _state.update { st -> st.copy(calibrationPoints = pts) }
                }
            }

            // Density Diag: CMD=0x0004, 16B
            if (parsed.cmd == 0x0004 && parsed.data.size == 16) {
                val diag = DiagReading.fromBytes(parsed.data) ?: continue
                _state.update { st ->
                    st.copy(
                        temperatureC = diag.temperature, currentMA = diag.currentMA,
                        damping = diag.damping, set4mA = diag.set4mA, set20mA = diag.set20mA,
                        pipeDia = diag.pipeDia, freqMHz = diag.freqMHz,
                    )
                }
            }

            // Interface Diag: CMD=0x0004/0x0014, 22B
            if ((parsed.cmd == 0x0004 || parsed.cmd == 0x0014) && parsed.data.size >= 22) {
                val diag = InterfaceDiagReading.fromBytes(parsed.data) ?: continue
                _state.update { st -> st.copy(interfaceDiag = diag) }
            }
        }
    }

    // ??傭?끆??????????룰퀡??????????????????????轅붽틓????嚥??? ??????196B??? + ?耀붾굝???????耀붾굝?????傭?????????????CRC+?????嶺뚮ㅎ?댐쭕?
    private fun tryParseIfEchoChunks(deviceId: String) {
        // ?? ???????轅붽틓????嚥???(98???????= 196B?? 7??8 = ?????嶺뚮ㅎ?댐쭕??????Β?ル윲????
        while (ifEchoChunksDone < ifEchoFullChunks) {
            if (rxBuf.size < 196) return
            for (i in 0 until 196) {
                ifEchoRunningCrc = crc16Update(ifEchoRunningCrc, rxBuf[i])
            }
            for (j in 0 until 98) {
                val hi = rxBuf[j * 2].toInt() and 0xFF
                val lo = rxBuf[j * 2 + 1].toInt() and 0xFF
                ifEchoWave.add((hi shl 8) or lo)
            }
            rxBuf.subList(0, 196).clear()
            ifEchoChunksDone++
        }

        // ?耀붾굝????????????? ??? ???????lastSamples??B) + CRC(2B) + ?????嶺뚮ㅎ?댐쭕?7B ?????밸븶筌믩끃????
        val lastSamples = ifEchoN % 98
        val lastBase = lastSamples * 2 + 2
        val lastSize = lastBase

        if (rxBuf.size < lastSize) return

        // ??? ????????????+ CRC ?????獄쏅챶留??
        for (j in 0 until lastSamples) {
            val b0 = rxBuf[j * 2]
            val b1 = rxBuf[j * 2 + 1]
            ifEchoRunningCrc = crc16Update(ifEchoRunningCrc, b0)
            ifEchoRunningCrc = crc16Update(ifEchoRunningCrc, b1)
            ifEchoWave.add(((b0.toInt() and 0xFF) shl 8) or (b1.toInt() and 0xFF))
        }

        // CRC ??汝뷴젆?琉????
        val crcOff = lastSamples * 2
        val recvCrc = (rxBuf[crcOff].toInt() and 0xFF) or ((rxBuf[crcOff + 1].toInt() and 0xFF) shl 8)
        rxBuf.subList(0, lastSize).clear()
        ifEchoState = 0

        if (ifEchoRunningCrc != recvCrc) {
            Log.w(TAG, "[IFECHO] CRC FAIL: calc=%04X recv=%04X".format(ifEchoRunningCrc, recvCrc))
            return
        }

        // ?????袁⑸즴筌? 28B + ????????????N??B ??InterfaceEchoReading
        val waveBytes = ByteArray(ifEchoWave.size * 2)
        for (i in ifEchoWave.indices) {
            waveBytes[i * 2] = ((ifEchoWave[i] shr 8) and 0xFF).toByte()
            waveBytes[i * 2 + 1] = (ifEchoWave[i] and 0xFF).toByte()
        }
        val ifEcho = InterfaceEchoReading.fromBytes(ifEchoHeaderData + waveBytes) ?: return
        _state.update { st -> st.copy(interfaceEchoReading = ifEcho) }
        Log.d(TAG, "[IFECHO] OK cmd=0x%04X samples=%d".format(ifEchoCmd, ifEchoWave.size))
    }

    private fun tryParseTrend(proto: BleProtocolService) {
        // Cancel ack from device (CMD 0x0008 / 0x0018) may arrive any time during streaming.
        if (downloadCancelRequested) {
            checkDownloadCancelAck(proto)
            if (!downloadCancelRequested && trendStreamState == 0) return
        }

        if (trendStreamState == 1) {
            while (rxBuf.size >= 7) {
                val data = rxBuf.toByteArray()
                val sofIdx = proto.indexOfSubsequence(data, byteArrayOf(0x02))
                if (sofIdx < 0) { rxBuf.clear(); return }
                if (sofIdx > 0) { rxBuf.subList(0, sofIdx).clear() }
                if (rxBuf.size < 7) return

                // Trend header: [SOF][CMD_HI][CMD_LO][records_HI][records_LO][CRC_L][CRC_H] = 7B
                val cmd = ((rxBuf[1].toInt() and 0xFF) shl 8) or (rxBuf[2].toInt() and 0xFF)
                if (cmd != 0x0002 && cmd != 0x0012 && cmd != 0x0007 && cmd != 0x0017) {
                    rxBuf.removeAt(0)
                    continue
                }

                // CRC ??汝뷴젆?琉????(SOF+CMD+DATA = 5B)
                val hdrBytes = ByteArray(5) { rxBuf[it] }
                val hdrCrcCalc = proto.crc16Modbus(hdrBytes)
                val hdrCrcRecv = (rxBuf[5].toInt() and 0xFF) or ((rxBuf[6].toInt() and 0xFF) shl 8)
                if (hdrCrcCalc != hdrCrcRecv) {
                    Log.w(TAG, "[TREND] header CRC FAIL: calc=%04X recv=%04X".format(hdrCrcCalc, hdrCrcRecv))
                    if (retryTrendTransferOnce(proto, "header CRC FAIL")) {
                        return
                    }
                    showTrendError("Header CRC error. Transfer failed.")
                    return
                }

                trendTotalRecords = ((rxBuf[3].toInt() and 0xFF) shl 8) or (rxBuf[4].toInt() and 0xFF)
                _state.update { it.copy(trendExpectedRecords = trendTotalRecords) }
                rxBuf.subList(0, 7).clear()
                trendChunkIndex = 0
                trendRunningCrc = 0xFFFF
                trendStreamState = 2
                break
            }
        }

        if (trendStreamState == 2) {
            parseTrendChunks(proto)
        }
    }

    // Trend End ?耀붾굝?????????寃밴콞??????ル뒌???: [02][00 FE][00 00][CRC_L][CRC_H] = 7B
    private fun checkTrendEnd(proto: BleProtocolService): Boolean {
        if (rxBuf.size < 7) return false
        if (rxBuf[0] != 0x02.toByte()) return false
        if (rxBuf[1] != 0x00.toByte() || rxBuf[2] != 0xFE.toByte()) return false
        val frame = ByteArray(7) { rxBuf[it] }
        val parsed = proto.parseFrame(frame)
        if (parsed != null && parsed.cmd == 0x00FE) {
            rxBuf.subList(0, 7).clear()
            return true
        }
        return false
    }

    private fun parseTrendChunks(proto: BleProtocolService) {
        // Use pinned value captured at startDataDownload(). state.deviceType
        // may differ if activateDevice() runs mid-stream in multi-device setups.
        val isIface = trendIsInterface
        val recSize = if (isIface) InterfaceTrendRecord.RECORD_SIZE else 24
        val parsed = _state.value.downloadRecords.size
        val newRecords = mutableListOf<TrendRecord>()

        while (parsed + newRecords.size < trendTotalRecords && rxBuf.size >= recSize) {
            val recBytes = ByteArray(recSize) { rxBuf[it] }
            rxBuf.subList(0, recSize).clear()

            for (b in recBytes) {
                trendRunningCrc = trendRunningCrc xor (b.toInt() and 0xFF)
                repeat(8) {
                    trendRunningCrc = if (trendRunningCrc and 0x0001 != 0)
                        (trendRunningCrc ushr 1) xor 0xA001
                    else
                        trendRunningCrc ushr 1
                }
            }

            val rec: TrendRecord? = if (isIface) {
                InterfaceTrendRecord.fromBytes(recBytes)?.let { ir ->
                    TrendRecord(
                        dateTime    = ir.dateTime,
                        dst         = ir.ch1Light,
                        eeaD        = (ir.ch1Heavy * 100).toInt(),
                        temperature = 0.0,
                    )
                }
            } else {
                TrendRecord.fromBytes(recBytes)
            }
            if (rec != null) newRecords.add(rec)
        }

        if (newRecords.isNotEmpty()) {
            Log.d(TAG, "[TREND] parsed ${parsed + newRecords.size} / $trendTotalRecords, rxBuf=${rxBuf.size}")
            appendTrendRecords(newRecords)
        }

        // ?耀붾굝?????????붾눀??????????????轅붽틓????嚥????????獄쏅챶留?????????嶺뚮ㅎ?댐쭕????????밸븶?????CRC ??汝뷴젆?琉????
        if (_state.value.downloadRecords.size >= trendTotalRecords) {
            // ?????嶺뚮ㅎ?댐쭕????????밸븶??? ???????????????????7???????밸븶筌믩끃?????耀붾굝???????????????ш내?℡ㅇ?⑤뼰?踰??0x00
            if (rxBuf.size >= 2) {
                // ?????嶺뚮ㅎ?댐쭕??????ㅼ뒭??????
                val crcReceived = (rxBuf[0].toInt() and 0xFF) or ((rxBuf[1].toInt() and 0xFF) shl 8)
                rxBuf.subList(0, 2).clear()
                if (crcReceived != trendRunningCrc) {
                    Log.w(TAG, "[TREND] CRC FAIL: received=%04X calc=%04X".format(crcReceived, trendRunningCrc))
                    if (retryTrendTransferOnce(proto, "final CRC FAIL")) {
                        return
                    }
                    showTrendError("CRC verification failed. Data corrupted.")
                    return
                } else {
                    Log.d(TAG, "[TREND] CRC OK: %04X".format(crcReceived))
                }
            }
            finishTrendStream(emptyList())
        }
    }

    private fun appendTrendRecords(records: List<TrendRecord>) {
        _state.update { st ->
            val updated = st.downloadRecords + records
            // ????μ떜媛?걫??????癲????ル㎦???????袁ⓦ걤???ш낄猷??????????????獄쏅챶留??貫????????亦낆떣?????????????????댁댉??????諛몃마???
            val progress = if (trendTotalRecords > 0) updated.size.toDouble() / trendTotalRecords else 0.0
            st.copy(
                downloadRecords = updated,
                dataDownloadProgress = if (st.subPage == "download") progress.coerceAtMost(0.99) else st.dataDownloadProgress,
            )
        }
    }

    private fun retryTrendTransferOnce(proto: BleProtocolService, reason: String): Boolean {
        // Retry disabled: 1st failure goes straight to error UI.
        // (Caller treats `false` return as "no retry attempted" → shows error.)
        Log.w(TAG, "[TREND] $reason -> retry disabled, showing error")
        return false
    }

    private fun startTrendTimeout(proto: BleProtocolService) {
        trendTimeoutJob?.cancel()
        var lastRecordCount = -1
        var unchangedCount = 0
        trendTimeoutJob = viewModelScope.launch {
            while (isActive && _state.value.isTrendStreaming) {
                delay(1000)
                val currentRecords = _state.value.downloadRecords.size
                if (currentRecords == lastRecordCount) {
                    unchangedCount++
                    if (unchangedCount < 5) continue  // 5초 연속 레코드 수 변화 없을 때 처리
                    Log.w(TAG, "[TREND] Timeout(5s): no new records, retrying...")
                    if (retryTrendTransferOnce(proto, "timeout")) {
                        break
                    }
                    showTrendError("Timeout: No response from device.")
                    break
                } else {
                    unchangedCount = 0
                }
                lastRecordCount = currentRecords
            }
        }
    }

    private fun showTrendError(msg: String) {
        trendTimeoutJob?.cancel()
        trendStreamState = 0
        val isDownload = _state.value.subPage == "download"
        _state.update {
            it.copy(
                isTrendStreaming = false,
                trendError = msg,
                dataFilesStage = if (isDownload) DataFilesStage.ERROR else it.dataFilesStage,
            )
        }
        Log.e(TAG, "[TREND] Error: $msg")
    }

    private fun finishTrendStream(remaining: List<TrendRecord>) {
        trendTimeoutJob?.cancel()
        trendStreamState = 0
        val finalRecords = _state.value.downloadRecords + remaining
        val chartRecords = finalRecords.associateBy { it.dateTime }.values.toList()
        val isDownload = _state.value.subPage == "download"

        _state.update {
            it.copy(
                downloadRecords = finalRecords,
                isTrendStreaming = false,
            )
        }

        if (isDownload && finalRecords.isNotEmpty()) {
            val elapsed = System.currentTimeMillis() - downloadStartTime
            val label = _state.value.activeDeviceLabel.ifEmpty { deviceLabelOrDefault }
            val fileName = _state.value.activeDataFile?.name ?: "${label}_trend.csv"
            val csvSize = finalRecords.size * 40

            val file = buildDataFile(label, LocalDateTime.now(), fileName, csvSize, finalRecords.size)
                .copy(recordCount = finalRecords.size, chartRecords = chartRecords, allRecords = finalRecords,
                    rangeLabel = if (finalRecords.size >= 2) {
                        val times = finalRecords.map { it.dateTime }
                        val earliest = times.min()
                        val latest = times.max()
                        val fmt = java.time.format.DateTimeFormatter.ofPattern("MM/dd HH:mm:ss")
                        "${earliest.format(fmt)} ~ ${latest.format(fmt)}"
                    } else "--")

            val savedPath = saveCsvToDocuments(file)

            _state.update { st ->
                val newFiles = (listOf(file) + st.savedDataFiles.filter { it.name != file.name }).take(8)
                st.copy(
                    dataDownloadProgress = 1.0,
                    activeDataFile = file,
                    savedDataFiles = newFiles,
                    dataFilesStage = DataFilesStage.COMPLETE,
                )
            }

            Log.d(TAG, "Download complete: ${finalRecords.size} records, ${elapsed}ms")
            if (savedPath != null) {
                _snackbarMessage.tryEmit("CSV saved: $savedPath (${finalRecords.size} records)")
            }
        }
    }


    // ?????? Upload ??????
    fun openFirmwareFlow() {
        val s = _state.value
        if (s.isUploading) {
            _state.update { it.copy(subPage = "upload") }
            return
        }
        // OTA 페이지 진입 시 잔여 RX 차단 + 버퍼 클리어
        rxMuted = true
        rxBuf.clear()
        pickedBytes = null
        _state.update {
            it.copy(
                subPage = "upload", firmwareTargetDeviceId = "",
                pickedFileName = null, pickedFileSize = null,
                uploadProgress = 0.0, uploadDone = false, uploadElapsed = 0,
            )
        }
    }

    fun selectFirmwareTarget(id: String) {
        viewModelScope.launch {
            activateDevice(id)
            _state.update {
                it.copy(
                    subPage = "upload", firmwareTargetDeviceId = id,
                    pickedFileName = null, pickedFileSize = null,                     uploadProgress = 0.0, uploadDone = false, uploadElapsed = 0,
                )
            }
        }
    }

    fun backToFirmwareDeviceSelect() {
        if (_state.value.isUploading) return
        _state.update {
            it.copy(
                firmwareTargetDeviceId = "",
                pickedFileName = null, pickedFileSize = null,                 uploadProgress = 0.0, uploadDone = false, uploadElapsed = 0,
            )
        }
    }

    fun setPickedFile(name: String, size: Int, bytes: ByteArray) {
        pickedBytes = bytes
        _state.update {
            it.copy(pickedFileName = name, pickedFileSize = size, uploadDone = false, uploadProgress = 0.0)
        }
    }

    fun startUpload() {
        // 이전 OTA job(forceReconnect 등에서 막혀있을 수 있음) 강제 종료 — race 방지
        uploadJob?.cancel()
        uploadJob = null
        uploadTimerJob?.cancel()
        uploadTimerJob = null
        // 이전 실행의 잔여 progress(예: 56%) 즉시 리셋
        _state.update {
            it.copy(uploadProgress = 0.0, uploadDone = false, isUploading = false, uploadElapsed = 0)
        }

        val s = _state.value
        val bytes = pickedBytes
        if (s.firmwareTargetDeviceId.isEmpty() || bytes == null) {
            _snackbarMessage.tryEmit("Select a file and target device first.")
            return
        }
        val proto = protocolServices[s.firmwareTargetDeviceId] ?: run {
            _snackbarMessage.tryEmit("No BLE device connected.")
            return
        }

        var uploadData = bytes
        val bootloaderSize = 0x8000
        if (uploadData.size > bootloaderSize) {
            uploadData = uploadData.copyOfRange(bootloaderSize, uploadData.size)
        }

        // Re-request HIGH connection priority — Android may have downgraded to
        // BALANCED, especially in multi-device setups. Boosts OTA throughput.
        proto.requestHighPriority()

        // OTA ???轅붽틓???壤굿??걜???heartbeat ??? (notifyJob?? ??? ??ACK ???轅붽틓????嚥????????獄쏅챶留??

        _state.update {
            it.copy(isUploading = true, uploadProgress = 0.0, uploadDone = false, uploadElapsed = 0, subPage = "upload")
        }

        // Wake Lock — OTA 중 CPU 절전 방지
        val pm = getApplication<Application>().getSystemService(Context.POWER_SERVICE) as android.os.PowerManager
        otaWakeLock = pm.newWakeLock(android.os.PowerManager.PARTIAL_WAKE_LOCK, "wessware:ota").apply { acquire(10 * 60 * 1000L) }

        val startTime = System.currentTimeMillis()
        uploadTimerJob?.cancel()
        uploadTimerJob = viewModelScope.launch {
            while (isActive) {
                delay(1000)
                _state.update { it.copy(uploadElapsed = System.currentTimeMillis() - startTime) }
            }
        }

        uploadJob = viewModelScope.launch {
            try {
                delay(500)  // heartbeat ?????獄쏅챶留????? ????
                rxBuf.clear()
                rxMuted = false
                otaStartAckDeferred?.cancel()
                otaStartAckDeferred = CompletableDeferred()
                otaStartAckBuf.clear()
                proto.uploadFirmware(
                    data = uploadData,
                    awaitStartAck = { timeoutMs ->
                        val waiter = otaStartAckDeferred
                        if (waiter == null) {
                            false
                        } else {
                            val ok = withTimeoutOrNull(timeoutMs) { waiter.await() } ?: false
                            if (!ok) {
                                val tail = otaStartAckBuf.takeLast(32).joinToString(" ") { "%02X".format(it.toInt() and 0xFF) }
                                Log.w(TAG, "OTA start ACK timeout in general listener; buffered=${otaStartAckBuf.size}B tail=[$tail]")
                            }
                            ok
                        }
                    },
                    onProgress = { progress ->
                        _state.update { it.copy(uploadProgress = progress) }
                    }
                )
                // uploadFirmware가 예외 없이 완료되면 성공
                uploadTimerJob?.cancel()
                val elapsed = System.currentTimeMillis() - startTime
                _state.update {
                    it.copy(
                        isUploading = false, uploadProgress = 1.0, uploadDone = true,
                        uploadElapsed = elapsed,
                    )
                }
                val sec = "%.2f".format(elapsed / 1000.0)
                _snackbarMessage.tryEmit("Firmware update successful! (${sec}s)\nDevice will reboot.")
                delay(1000)
                val targetId = s.firmwareTargetDeviceId
                if (targetId.isNotEmpty()) {
                    disconnectDevice(targetId)
                }
            } catch (e: kotlinx.coroutines.CancellationException) {
                Log.d(TAG, "Upload cancelled by user")
                throw e
            } catch (e: Exception) {
                uploadTimerJob?.cancel()
                // 실패/끊김 시 로딩 상태 완전 초기화 (다음 OTA 가 fresh 하게 시작되도록)
                _state.update {
                    it.copy(
                        isUploading = false,
                        uploadProgress = 0.0,
                        uploadDone = false,
                        uploadElapsed = System.currentTimeMillis() - startTime,
                    )
                }
                Log.e(TAG, "Upload failed: ${e.message}")
                _snackbarMessage.tryEmit("Upload failed: ${e.message}")
            } finally {
                otaWakeLock?.let { if (it.isHeld) it.release() }
                otaWakeLock = null
                uploadPreSyncDeferred = null
                otaStartAckDeferred = null
                otaStartAckBuf.clear()
                // OTA ?????獄쏅챶留?????????ㅼ뒩????listener + heartbeat ?????곕츥?嶺뚮?爰???
                val activeId = _state.value.activeDeviceId
                if (activeId.isNotEmpty()) {
                    listenNotifications(activeId)
                    startHeartbeat()
                }
            }
        }
    }

    fun cancelUpload() {
        uploadJob?.cancel()
        uploadJob = null
        uploadTimerJob?.cancel()
        otaWakeLock?.let { if (it.isHeld) it.release() }
        otaWakeLock = null
        // 취소 후 1초 페이지 전환 차단
        pageTransitionBlockedUntil = System.currentTimeMillis() + 1000
        _state.update {
            it.copy(isUploading = false, uploadProgress = 0.0)
        }
        _snackbarMessage.tryEmit("Firmware upload cancelled.")
    }

    // ?????? Chatbot ??????
    fun openChatbot() {
        _state.update { it.copy(tabIndex = 4, subPage = "chatbot") }
    }

    // ?????? Data files ??????
    fun openDataFilesList() {
        downloadTimerJob?.cancel()
        val files = loadSavedFilesFromDisk()
        _state.update { it.copy(subPage = "download", dataFilesStage = DataFilesStage.LIST, savedDataFiles = files, trendError = null) }
    }

    private fun loadSavedFilesFromDisk(): List<DataFileItem> {
        return try {
            val docsDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS)
            val appDir = java.io.File(docsDir, "WESSWARE")
            if (!appDir.exists()) return emptyList()
            appDir.listFiles { f -> f.extension.equals("csv", ignoreCase = true) }
                ?.sortedByDescending { it.lastModified() }
                ?.map { f ->
                    val lines = f.readLines()
                    val recordCount = (lines.size - 1).coerceAtLeast(0) // 헤더 제외
                    DataFileItem(
                        name = f.name,
                        recordCount = recordCount,
                        rangeLabel = if (lines.size >= 3) {
                            val first = lines[1].split(",").firstOrNull() ?: "--"
                            val last = lines.last().split(",").firstOrNull() ?: "--"
                            "$first ~ $last"
                        } else "--",
                        sizeBytes = f.length().toInt(),
                        targetDevice = f.nameWithoutExtension.substringBefore("_20"),
                        chartRecords = emptyList(),
                    )
                } ?: emptyList()
        } catch (e: Exception) {
            Log.e(TAG, "Failed to load saved files: ${e.message}")
            emptyList()
        }
    }

    private var downloadStartTime = 0L

    // Data download cancel (user-initiated)
    @Volatile private var downloadCancelRequested: Boolean = false
    private var downloadCancelJob: kotlinx.coroutines.Job? = null

    fun cancelDataDownload() {
        if (downloadCancelRequested) return
        if (trendStreamState == 0 && !_state.value.isTrendStreaming) return

        downloadCancelRequested = true
        val proto = activeProtocol ?: run {
            finalizeDownloadCancelled()
            return
        }
        val isCh2 = _state.value.activeDeviceId.endsWith("_CH2")
        val cancelCmd = if (isCh2) com.wws2.densitymeter.ble.protocol.Command.CMD_DOWNLOAD_CANCEL_CH2
                        else       com.wws2.densitymeter.ble.protocol.Command.CMD_DOWNLOAD_CANCEL

        Log.d(TAG, "[TREND] cancel requested cmd=0x%04X".format(cancelCmd))

        downloadCancelJob?.cancel()
        downloadCancelJob = viewModelScope.launch {
            // Firmware masks RXNE while transmitting a chunk (~20 ms) so the
            // cancel frame may be lost. Retransmit a few times at 50 ms apart
            // until the device echoes the cancel ack back (handled in tryParseTrend).
            repeat(5) {
                if (!downloadCancelRequested) return@launch
                proto.sendHeartbeat(cancelCmd)
                delay(50)
            }
            // No ack after repeated sends — finalize locally
            if (downloadCancelRequested) {
                Log.w(TAG, "[TREND] cancel ack not received, forcing local finish")
                finalizeDownloadCancelled()
            }
        }
    }

    private fun checkDownloadCancelAck(proto: BleProtocolService) {
        if (rxBuf.size < 7) return
        var i = 0
        while (i + 6 < rxBuf.size) {
            val b0 = rxBuf[i].toInt() and 0xFF
            val b1 = rxBuf[i + 1].toInt() and 0xFF
            val b2 = rxBuf[i + 2].toInt() and 0xFF
            if (b0 == 0x02 && b1 == 0x00 && (b2 == 0x08 || b2 == 0x18)) {
                val hdr = ByteArray(5) { rxBuf[i + it] }
                val calc = proto.crc16Modbus(hdr)
                val recv = (rxBuf[i + 5].toInt() and 0xFF) or ((rxBuf[i + 6].toInt() and 0xFF) shl 8)
                if (calc == recv) {
                    rxBuf.subList(i, i + 7).clear()
                    Log.d(TAG, "[TREND] cancel ack received (cmd=0x%02X)".format(b2))
                    finalizeDownloadCancelled()
                    return
                }
            }
            i++
        }
    }

    private fun finalizeDownloadCancelled() {
        downloadCancelRequested = false
        downloadCancelJob?.cancel()
        downloadCancelJob = null
        trendTimeoutJob?.cancel()
        trendStreamState = 0
        rxBuf.clear()
        _state.update {
            it.copy(
                isTrendStreaming = false,
                dataFilesStage = DataFilesStage.LIST,
                dataDownloadProgress = 0.0,
                downloadRecords = emptyList(),
                trendError = null,
            )
        }
        _snackbarMessage.tryEmit("Download cancelled.")
    }

    /**
     * 다운로드 버튼에서 호출. 선택한 기기를 먼저 activate 하고 (await) 그 뒤에
     * 다운로드를 시작한다. 이전의 `requestConnectDevice() + startDataDownload()`
     * 2-단계 호출은 async/sync race 때문에 multi-device 에서 stale state 로
     * 다운로드가 시작되는 문제가 있었음.
     */
    fun activateAndDownload(address: String) {
        viewModelScope.launch {
            if (_state.value.activeDeviceId != address) {
                val existing = _state.value.connectedDevices.find { it.id == address }
                if (existing != null) {
                    activateDevice(address)
                } else {
                    _snackbarMessage.tryEmit("Device not connected.")
                    return@launch
                }
            }
            startDataDownload()
        }
    }

    fun startDataDownload() {
        val s = _state.value
        if (s.connectedDevices.isEmpty()) {
            _snackbarMessage.tryEmit("No BLE device connected.")
            return
        }

        // Pin device type at download start. parseTrendChunks uses this instead of
        // state.deviceType so mid-stream activateDevice() calls can't swap recSize.
        val activeDev = s.connectedDevices.find { it.id == s.activeDeviceId }
            ?: s.connectedDevices.first()
        trendIsInterface = (activeDev.deviceType == 1)

        downloadTimerJob?.cancel()
        val label = s.activeDeviceLabel.ifEmpty { deviceLabelOrDefault }
        val fileName = "${label}_${formatDateStamp(LocalDateTime.now())}.csv"

        // ??????硫멸킐???????(???????????黎앸럽????룸돥???????轅붽틓????嚥?????????????댁댉??????諛몃마???
        val file = buildDataFile(label, LocalDateTime.now(), fileName, 0, s.savedDataFiles.size + 1)

        _state.update { it.copy(
            activeDataFile = file,
            dataDownloadProgress = 0.0,
            dataFilesStage = DataFilesStage.DOWNLOADING,
            downloadRecords = emptyList(),
            trendError = null,
        ) }

        // ??饔낅떽?????????????繹먮굝??????轅붽틓???壤굿??걜?(cmd 0x07/0x17)
        // 다운로드 시작 직전 잔여 RX 차단 + 버퍼 클리어 (cmd 0x07/0x17)
        downloadStartTime = System.currentTimeMillis()
        rxMuted = true
        rxBuf.clear()
        trendStreamState = 1
        trendStartRetryCount = 0
        trendTabFirstVisit = false
        _state.update { it.copy(isTrendStreaming = true) }
        val dlProto = activeProtocol ?: return
        // Re-request HIGH connection priority — Android may have downgraded to
        // BALANCED when a second device connected. Critical for multi-device throughput.
        dlProto.requestHighPriority()
        startTrendTimeout(dlProto)

        // cmd ?????獄쏅챶留덌┼??뭬?怨좊뭽?
        // cmd 송신 직전에 잔여 RX 가라앉기를 기다린 후 음소거 해제
        viewModelScope.launch {
            delay(1000)
            rxBuf.clear()
            rxMuted = false   // 다운로드 청크 수신 위해 명시적 해제
            val proto = activeProtocol ?: return@launch
            proto.sendHeartbeat(heartbeatPageIndex)
        }
    }

    fun viewDataFile(file: DataFileItem) {
        val loaded = if (file.chartRecords.isEmpty()) loadCsvRecords(file) else file
        _state.update { it.copy(subPage = "download", activeDataFile = loaded, dataFilesStage = DataFilesStage.VIEW) }
    }

    private fun loadCsvRecords(file: DataFileItem): DataFileItem {
        return try {
            val docsDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS)
            val csvFile = java.io.File(java.io.File(docsDir, "WESSWARE"), file.name)
            if (!csvFile.exists()) return file
            val lines = csvFile.readLines()
            if (lines.size < 2) return file
            val header = lines[0].lowercase()
            val isInterface = header.contains("light") || header.contains("heavy")
            val records = lines.drop(1).mapNotNull { line ->
                val cols = line.split(",")
                try {
                    val dt = java.time.LocalDateTime.parse(cols[0], java.time.format.DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"))
                    if (isInterface) {
                        // Time,Light,Heavy,Temp
                        val light = cols[1].toDouble()
                        val heavy = cols[2].toDouble()
                        val temp = cols[3].toDouble()
                        TrendRecord(dateTime = dt, eeaD = (heavy / 0.01).toInt(), dst = light, temperature = temp)
                    } else {
                        // Time,EEA,Density,Temp[,Step,VCA,Status]
                        val eea = cols[1].toInt()
                        val density = cols[2].toDouble()
                        val temp = cols[3].toDouble()
                        val step = if (cols.size > 4) cols[4].toInt() else 0
                        val vca = if (cols.size > 5) cols[5].toInt() else 0
                        val status = if (cols.size > 6) cols[6].toInt() else 0
                        TrendRecord(dateTime = dt, eeaD = eea, dst = density, temperature = temp, step = step, vca = vca, status = status)
                    }
                } catch (_: Exception) { null }
            }
            val unique = records.associateBy { it.dateTime }.values.toList()
            file.copy(chartRecords = unique, allRecords = records, recordCount = records.size,
                rangeLabel = if (records.size >= 2) {
                    val fmt = java.time.format.DateTimeFormatter.ofPattern("MM/dd HH:mm:ss")
                    "${records.first().dateTime.format(fmt)} ~ ${records.last().dateTime.format(fmt)}"
                } else "--")
        } catch (e: Exception) {
            Log.e(TAG, "CSV parse failed: ${e.message}")
            file
        }
    }

    fun shareDataFile(): Intent? {
        val file = _state.value.activeDataFile ?: return null
        val records = file.chartRecords
        if (records.isEmpty()) {
            _snackbarMessage.tryEmit("No data to share.")
            return null
        }

        val isIface = _state.value.deviceType == DeviceType.INTERFACE
        val csv = buildCsvContent(file.allRecords.ifEmpty { records }, isIface)

        // Write CSV to cache dir
        val context: Context = getApplication()
        val cacheDir = File(context.cacheDir, "csv_export")
        cacheDir.mkdirs()
        val csvFile = File(cacheDir, file.name)
        csvFile.writeText(csv)

        // Create share intent via FileProvider
        val uri = FileProvider.getUriForFile(context, "${context.packageName}.fileprovider", csvFile)
        return Intent(Intent.ACTION_SEND).apply {
            type = "application/octet-stream"
            putExtra(Intent.EXTRA_STREAM, uri)
            putExtra(Intent.EXTRA_SUBJECT, file.name)
            addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
        }
    }

    fun getCsvContentForSave(): Pair<String, String>? {
        val file = _state.value.activeDataFile ?: return null
        val records = file.allRecords.ifEmpty { file.chartRecords }
        if (records.isEmpty()) return null
        val isIface = _state.value.deviceType == DeviceType.INTERFACE
        val csv = buildCsvContent(records, isIface)
        return Pair(file.name, csv)
    }

    private fun saveCsvToDocuments(file: DataFileItem): String? {
        return try {
            val isIface = _state.value.deviceType == DeviceType.INTERFACE
            val csv = buildCsvContent(file.allRecords.ifEmpty { file.chartRecords }, isIface)

            val docsDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS)
            val appDir = File(docsDir, "WESSWARE")
            appDir.mkdirs()

            val csvFile = File(appDir, file.name)
            csvFile.writeText(csv)
            csvFile.absolutePath
        } catch (e: Exception) {
            Log.e(TAG, "CSV save failed: ${e.message}")
            null
        }
    }

    private fun buildCsvContent(records: List<TrendRecord>, isInterface: Boolean): String {
        val sb = StringBuilder()
        if (isInterface) {
            sb.appendLine("Time,Light,Heavy,Temp")
            for (r in records) {
                val dt = r.dateTime.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"))
                // For interface: dst = Light (level), eeaD = Heavy (stored in eeaD field)
                sb.appendLine("$dt,%.2f,%.2f,%.1f".format(r.dst, r.eeaD * 0.01, r.temperature))
            }
        } else {
            sb.appendLine("Time,EEA,Density,Temp,Step,VCA,Status")
            for (r in records) {
                val dt = r.dateTime.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"))
                sb.appendLine("$dt,%d,%.2f,%.1f,%d,%d,%d".format(r.eeaD, r.dst, r.temperature, r.step, r.vca, r.status))
            }
        }
        return sb.toString()
    }

    fun importCsvFile(name: String, size: Int) {
        val label = deviceLabelOrDefault
        val nameUpper = name.uppercase()
        val matchedCh = Regex("ENV\\d+_A\\d{2}", RegexOption.IGNORE_CASE).find(name)?.value?.uppercase()
        val targetDevice = matchedCh ?: when {
            nameUpper.contains("ENV130") -> "ENV130"
            nameUpper.contains("ENV230") -> "ENV230"
            else -> label
        }
        var file = buildDataFile(targetDevice, LocalDateTime.now(), name, size, name.hashCode().and(0x7FFFFFFF) % 7)
        file = loadCsvRecords(file)
        _state.update { st ->
            val newFiles = (listOf(file) + st.savedDataFiles.filter { it.name != file.name }).take(8)
            st.copy(
                subPage = "download",
                activeDataFile = file,
                savedDataFiles = newFiles,
                dataFilesStage = DataFilesStage.VIEW,
            )
        }
    }

    // ?????? Helpers ??????
    /** ???轅붽틓????????긺춯癒?뼔???????獄쏅챶留??貫?????????먃????곕선?0xF0) + PIN ??汝뷴젆?琉???? ?????롮쾸????怨뚮옩鴉?????????ㅼ뒩?????????獄쏅챶留????????밸븶筌믩끃???? */
    private suspend fun requestPairing(protocol: BleProtocolService, pin: Int): BleProtocolService.PairingResult? {
        return try {
            val result = CompletableDeferred<BleProtocolService.PairingResult>()
            val buf = mutableListOf<Byte>()
            val job = viewModelScope.launch {
                protocol.notifications.collect { chunk ->
                    buf.addAll(chunk.toList())
                    if (buf.size > 256) buf.subList(0, buf.size - 128).clear()

                    // SOF(0x02) ?耀붾굝????????7?????밸븶筌믩끃?????????????????????
                    while (buf.size >= 7) {
                        if (buf[0] != 0x02.toByte()) {
                            val idx = buf.indexOfFirst { it == 0x02.toByte() }
                            if (idx < 0) { buf.clear(); break }
                            buf.subList(0, idx).clear()
                            if (buf.size < 7) break
                        }
                        val frame = ByteArray(7) { buf[it] }
                        val parsed = protocol.parsePairingResponse(frame)
                        if (parsed != null && !result.isCompleted) {
                            result.complete(parsed)
                            break
                        }
                        buf.removeAt(0)
                    }
                }
            }
            delay(50)
            val request = protocol.buildDeviceInfoRequest(pin)
            Log.d(TAG, "pairing TX [${request.size}B]: ${request.joinToString(" ") { "%02X".format(it) }}")
            protocol.write(request, withoutResponse = true)
            val info = withTimeoutOrNull(5000L) { result.await() }
            job.cancel()
            Log.d(TAG, "pairing result: $info")
            info
        } catch (e: Exception) {
            Log.e(TAG, "requestPairing failed: ${e.message}")
            null
        }
    }

    /** BLE ??????????????????????꾨굴??? "WESS_V0.1_ENV230_A01" ??"V0.1" */
    private fun extractFirmwareVersion(bleName: String): String {
        val regex = Regex("V(\\d+\\.\\d+)", RegexOption.IGNORE_CASE)
        return regex.find(bleName)?.value ?: ""
    }

    /** Allocate label for density meter (ENV230_A01 ~ A04) */
    private fun allocateLabel(): String {
        val used = _state.value.connectedDevices.map { it.label }.toSet()
        for (i in 1..4) {
            val label = "ENV230_A${i.toString().padStart(2, '0')}"
            if (label !in used) return label
        }
        return "ENV230_A04"
    }

    /** Allocate labels for interface meter: ENV130_A02 + ENV130_A03, etc. */
    private fun allocateInterfaceLabels(currentDevices: List<ConnectedBleDevice>): Pair<String, String> {
        val used = currentDevices.map { it.label }.toSet()
        val pairs = listOf(2 to 3, 4 to 5, 6 to 7, 8 to 9)
        for ((a, b) in pairs) {
            val l1 = "ENV130_A${a.toString().padStart(2, '0')}"
            val l2 = "ENV130_A${b.toString().padStart(2, '0')}"
            if (l1 !in used && l2 !in used) return l1 to l2
        }
        return "ENV130_A02" to "ENV130_A03"
    }

    /** Detect device type from BLE name */
    fun detectDeviceTypeFromName(name: String): DeviceType {
        return if (name.uppercase().startsWith("W3") || name.uppercase().contains("130") || name.uppercase().contains("WE13") || name.uppercase().contains("INTERFACE")) {
            DeviceType.INTERFACE
        } else {
            DeviceType.DENSITY
        }
    }

    private fun resetLiveData(st: MainUiState): MainUiState {
        trendTabFirstVisit = true
        trendStreamState = 0
        trendStartRetryCount = 0
        return st.copy(
            deviceReadings = emptyMap(), deviceEchoReadings = emptyMap(),
            temperatureC = 0.0, currentMA = 0.0, damping = 0,
            set4mA = 0.0, set20mA = 0.0, pipeDia = 0, freqMHz = 0.0,
            echoReading = null, interfaceEchoReading = null,
            trendRecords = emptyList(),
            isTrendStreaming = false, rxBlink = false,
            interfaceReading = null,
        )
    }

    val densityValues: Map<String, Double>
        get() = _state.value.deviceReadings.mapValues { it.value.level }

    val firmwareTargetLabel: String?
        get() {
            val id = _state.value.firmwareTargetDeviceId
            if (id.isEmpty()) return null
            return _state.value.connectedDevices.find { it.id == id }?.label
        }

    val isConnected: Boolean get() = _state.value.connectedDevices.isNotEmpty()

    val statusLabel: String
        get() {
            val count = _state.value.connectedDevices.size
            return if (count > 0) "$count Connected" else "Disconnected"
        }

    val deviceLabelOrDefault: String
        get() {
            val label = _state.value.activeDeviceLabel
            if (label.isNotEmpty()) return label
            return if (_state.value.deviceType == DeviceType.INTERFACE) "ENV130_A02" else "ENV230_A01"
        }

    val currentTitle: String
        get() {
            val s = _state.value
            if (s.subPage == "pairing") return "BLE Pairing"
            if (s.subPage == "download") return "Data Files"
            if (s.subPage == "upload") return "Firmware Update"
            if (s.subPage == "chatbot") return "AI Chatbot"
            if (s.subPage == "calib") return "Calibration"
            return when (s.tabIndex) {
                0 -> "Main"; 1 -> "Echo"; 2 -> "Trend"; 3 -> "Parameter"; 4 -> "Menu"; else -> "Main"
            }
        }

    fun handleTopBarBack() {
        // OTA 취소 직후 5초 페이지 전환 차단
        if (System.currentTimeMillis() < pageTransitionBlockedUntil) return
        val s = _state.value
        when (s.subPage) {
            "pairing" -> {
                connectionService.stopScan()
                _state.update { it.copy(subPage = null) }
            }
            "download" -> {
                if (s.dataFilesStage != DataFilesStage.LIST) openDataFilesList()
                else _state.update { it.copy(subPage = null) }
            }
            "upload" -> {
                if (s.isUploading) return
                if (s.firmwareTargetDeviceId.isNotEmpty() || s.uploadDone) backToFirmwareDeviceSelect()
                else _state.update { it.copy(subPage = null) }
            }
            "chatbot" -> {
                _state.update { it.copy(subPage = null) }
            }
        }
    }

    private fun startForegroundService() {
        val intent = Intent(getApplication(), BleForegroundService::class.java)
        getApplication<Application>().startForegroundService(intent)
    }

    private fun stopForegroundService() {
        val intent = Intent(getApplication(), BleForegroundService::class.java)
        getApplication<Application>().stopService(intent)
    }

    private fun buildDataFile(target: String, endTime: LocalDateTime, name: String, sizeBytes: Int, seed: Int = 0): DataFileItem {
        return DataFileItem(name, 0, "--", sizeBytes, target, emptyList())
    }

    private fun formatDateStamp(dt: LocalDateTime): String = dt.format(DateTimeFormatter.ofPattern("yyyyMMdd_HHmmss"))

    override fun onCleared() {
        super.onCleared()
        stopHeartbeat()
        notifyJob?.cancel()
        parseJob?.cancel()
        uploadTimerJob?.cancel()
        downloadTimerJob?.cancel()
        protocolServices.values.forEach { it.disconnect() }
        connectionService.dispose()
        stopForegroundService()
    }
}