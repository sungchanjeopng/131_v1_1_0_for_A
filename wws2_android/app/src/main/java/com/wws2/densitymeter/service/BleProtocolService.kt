package com.wws2.densitymeter.service

import android.annotation.SuppressLint
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothGatt
import android.bluetooth.BluetoothGattCallback
import android.bluetooth.BluetoothGattCharacteristic
import android.bluetooth.BluetoothGattDescriptor
import android.bluetooth.BluetoothProfile
import android.bluetooth.BluetoothStatusCodes
import android.content.Context
import android.os.Build
import android.util.Log
import kotlinx.coroutines.CompletableDeferred
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.SharedFlow
import kotlinx.coroutines.flow.collect
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.flow.mapNotNull
import kotlinx.coroutines.launch
import kotlinx.coroutines.sync.Mutex
import kotlinx.coroutines.sync.withLock
import kotlinx.coroutines.withContext
import kotlinx.coroutines.withTimeoutOrNull
import kotlinx.coroutines.coroutineScope
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.util.UUID
import kotlin.math.max
import kotlin.math.min

private const val TAG = "BleProtocol"
const val PHY_MODE = "2m" // "coded" / "2m" / "1m"

class BleProtocolService(private val context: Context) {

    @Volatile private var gatt: BluetoothGatt? = null
    @Volatile private var writeChar: BluetoothGattCharacteristic? = null
    @Volatile private var notifyChar: BluetoothGattCharacteristic? = null
    @Volatile private var useWriteNoResponse = false
    @Volatile private var currentMtu = 23
    @Volatile private var writeDeferred: CompletableDeferred<Int>? = null
    private val writeMutex = Mutex()

    // Buffer sized for high-throughput bursts (e.g., dual-device trend download).
    // 1024 slots ≈ 1.3 seconds of back-pressure margin at peak notification rate.
    // Previous value (64) overflowed in multi-device scenarios, silently dropping
    // notifications via tryEmit → ~35% density-data loss.
    private val _notifications = MutableSharedFlow<ByteArray>(extraBufferCapacity = 1024)
    val notifications: SharedFlow<ByteArray> = _notifications

    private val _connectionState = MutableSharedFlow<Boolean>(extraBufferCapacity = 4)
    val connectionState: SharedFlow<Boolean> = _connectionState

    val isConnected: Boolean get() = gatt != null && writeChar != null

    companion object {
        const val CMD_DEVICE_INFO: Short = 0x00F0
        const val LEN_DEVICE_INFO_DENSITY: Short = 0x0005
        const val LEN_DEVICE_INFO_INTERFACE: Short = 0x0007
    }

    data class FwVersion(val major: Int, val minor: Int, val patch: Int) {
        companion object {
            fun fromBytes(major: Int, minor: Int, patch: Int): FwVersion {
                return FwVersion(major, minor, patch)
            }
        }

        override fun toString() = "v$major.$minor.$patch"
    }

    data class DeviceInfo(
        val siteNameHi: Char,
        val siteNameLo: Int,
        val ch2SiteNameHi: Char = '\u0000',
        val ch2SiteNameLo: Int = 0,
        val fwVersion: FwVersion,
    )

    sealed class PairingResult {
        data class Success(val deviceInfo: DeviceInfo) : PairingResult()
        object PinFailed : PairingResult()
    }

    data class ParsedFrame(val cmd: Int, val data: ByteArray)

    fun buildDeviceInfoRequest(pin: Int = 0): ByteArray {
        val payload = byteArrayOf(
            0x02,
            0x00,
            CMD_DEVICE_INFO.toByte(),
            ((pin shr 8) and 0xFF).toByte(),
            (pin and 0xFF).toByte(),
        )
        val crc = crc16Modbus(payload)
        return payload + byteArrayOf((crc and 0xFF).toByte(), ((crc shr 8) and 0xFF).toByte())
    }

    fun parsePairingResponse(frame: ByteArray): PairingResult? {
        if (frame.size < 7) return null
        if (frame[0] != 0x02.toByte()) return null

        val cmd = ((frame[1].toInt() and 0xFF) shl 8) or (frame[2].toInt() and 0xFF)
        if (cmd != 0x00F0) return null

        val crcExpected = crc16Modbus(frame.copyOfRange(0, 5))
        val crcReceived = (frame[5].toInt() and 0xFF) or ((frame[6].toInt() and 0xFF) shl 8)
        if (crcExpected != crcReceived) return null

        val result = ((frame[3].toInt() and 0xFF) shl 8) or (frame[4].toInt() and 0xFF)
        return if (result == 0x0000) {
            Log.d(TAG, "Pairing PIN OK")
            PairingResult.Success(DeviceInfo('?', 0, fwVersion = FwVersion(0, 0, 0)))
        } else {
            Log.w(TAG, "Pairing PIN failed")
            PairingResult.PinFailed
        }
    }

    fun crc16Modbus(data: ByteArray): Int {
        var crc = 0xFFFF
        for (b in data) {
            crc = crc xor (b.toInt() and 0xFF)
            repeat(8) {
                crc = if ((crc and 1) != 0) {
                    (crc ushr 1) xor 0xA001
                } else {
                    crc ushr 1
                }
            }
        }
        return crc and 0xFFFF
    }

    fun buildFrame(len: Int, data: ByteArray = ByteArray(0)): ByteArray {
        val sof = byteArrayOf(0x02)
        val lenBytes = byteArrayOf(((len shr 8) and 0xFF).toByte(), (len and 0xFF).toByte())
        val payload = sof + lenBytes + data
        val crc = crc16Modbus(payload)
        return payload + byteArrayOf((crc and 0xFF).toByte(), ((crc shr 8) and 0xFF).toByte())
    }

    fun buildHeartbeat(pageIndex: Int, data: Int = 0): ByteArray {
        val sof = byteArrayOf(0x02)
        val cmdBytes = byteArrayOf(((pageIndex shr 8) and 0xFF).toByte(), (pageIndex and 0xFF).toByte())
        val dataBytes = byteArrayOf(((data shr 8) and 0xFF).toByte(), (data and 0xFF).toByte())
        val payload = sof + cmdBytes + dataBytes
        val crc = crc16Modbus(payload)
        return payload + byteArrayOf((crc and 0xFF).toByte(), ((crc shr 8) and 0xFF).toByte())
    }

    fun parseFrame(raw: ByteArray): ParsedFrame? {
        if (raw.size < 5) return null
        if (raw[0] != 0x02.toByte()) return null

        val cmd = ((raw[1].toInt() and 0xFF) shl 8) or (raw[2].toInt() and 0xFF)
        val dataSize = raw.size - 5
        val payloadEnd = raw.size - 2
        val crcReceived = (raw[payloadEnd].toInt() and 0xFF) or ((raw[payloadEnd + 1].toInt() and 0xFF) shl 8)
        val crcCalc = crc16Modbus(raw.copyOfRange(0, payloadEnd))
        if (crcReceived != crcCalc) return null
        val data = if (dataSize > 0) raw.copyOfRange(3, payloadEnd) else ByteArray(0)
        return ParsedFrame(cmd, data)
    }

    fun makeStartFrame(fileSizeBytes: Int = 0): ByteArray {
        val sizeKB = (fileSizeBytes + 1023) / 1024  // 올림 KB
        return buildHeartbeat(0x0050, sizeKB)
    }
    fun makeEndFrame(): ByteArray = buildHeartbeat(0x0051)

    fun crc32(data: ByteArray): Int {
        val poly = 0xEDB88320.toInt()
        val table = IntArray(256) { i ->
            var c = i
            repeat(8) {
                c = if ((c and 1) != 0) poly xor (c ushr 1) else c ushr 1
            }
            c
        }
        var crc = -1
        for (b in data) {
            crc = table[(crc xor (b.toInt() and 0xFF)) and 0xFF] xor (crc ushr 8)
        }
        return crc xor -1
    }

    fun u32le(v: Int): ByteArray {
        val buf = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN)
        buf.putInt(v)
        return buf.array()
    }

    fun indexOfSubsequence(data: ByteArray, pattern: ByteArray): Int {
        if (pattern.isEmpty() || data.size < pattern.size) return -1
        outer@ for (i in 0..data.size - pattern.size) {
            for (j in pattern.indices) {
                if (data[i + j] != pattern[j]) continue@outer
            }
            return i
        }
        return -1
    }

    @Suppress("DEPRECATION")
    @SuppressLint("MissingPermission")
    private fun gattWriteCharacteristic(
        g: BluetoothGatt,
        c: BluetoothGattCharacteristic,
        data: ByteArray,
        writeType: Int,
    ): Boolean {
        return if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            g.writeCharacteristic(c, data, writeType) == BluetoothStatusCodes.SUCCESS
        } else {
            c.writeType = writeType
            c.value = data
            g.writeCharacteristic(c)
        }
    }

    @Suppress("DEPRECATION")
    @SuppressLint("MissingPermission")
    private fun gattWriteDescriptor(g: BluetoothGatt, d: BluetoothGattDescriptor, value: ByteArray): Boolean {
        return if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.TIRAMISU) {
            g.writeDescriptor(d, value) == BluetoothStatusCodes.SUCCESS
        } else {
            d.value = value
            g.writeDescriptor(d)
        }
    }

    @SuppressLint("MissingPermission")
    suspend fun connect(device: BluetoothDevice): Boolean = withContext(Dispatchers.IO) {
        val result = CompletableDeferred<Boolean>()

        val callback = object : BluetoothGattCallback() {
            override fun onConnectionStateChange(g: BluetoothGatt, status: Int, newState: Int) {
                if (newState == BluetoothProfile.STATE_CONNECTED) {
                    Log.d(TAG, "Connected, discovering services...")
                    g.requestConnectionPriority(BluetoothGatt.CONNECTION_PRIORITY_HIGH)
                    g.requestMtu(247)
                } else if (newState == BluetoothProfile.STATE_DISCONNECTED) {
                    Log.d(TAG, "Disconnected, status=$status")
                    // GATT client 인터페이스 누수 방지: gatt 참조를 null로 만들기 전에 반드시 close()
                    try { g.close() } catch (e: Exception) { Log.w(TAG, "close on disconnect failed: ${e.message}") }
                    gatt = null
                    writeChar = null
                    notifyChar = null
                    _connectionState.tryEmit(false)
                    if (!result.isCompleted) result.complete(false)
                }
            }

            override fun onMtuChanged(g: BluetoothGatt, mtu: Int, status: Int) {
                Log.d(TAG, "MTU changed to $mtu")
                currentMtu = mtu
                g.discoverServices()
            }

            override fun onServicesDiscovered(g: BluetoothGatt, status: Int) {
                if (status != BluetoothGatt.GATT_SUCCESS) {
                    if (!result.isCompleted) result.complete(false)
                    return
                }

                var nc: BluetoothGattCharacteristic? = null
                var wnr: BluetoothGattCharacteristic? = null
                var wr: BluetoothGattCharacteristic? = null

                for (service in g.services) {
                    for (c in service.characteristics) {
                        val props = c.properties
                        if ((props and BluetoothGattCharacteristic.PROPERTY_NOTIFY) != 0 && nc == null) nc = c
                        if ((props and BluetoothGattCharacteristic.PROPERTY_INDICATE) != 0 && nc == null) nc = c
                        if ((props and BluetoothGattCharacteristic.PROPERTY_WRITE_NO_RESPONSE) != 0 && wnr == null) wnr = c
                        if ((props and BluetoothGattCharacteristic.PROPERTY_WRITE) != 0 && wr == null) wr = c
                    }
                }

                val wc = wnr ?: wr
                nc = nc ?: wc

                if (wc == null || nc == null) {
                    if (!result.isCompleted) result.complete(false)
                    return
                }

                writeChar = wc
                notifyChar = nc
                useWriteNoResponse = wnr != null
                gatt = g

                val notifyProps = nc.properties
                if ((notifyProps and BluetoothGattCharacteristic.PROPERTY_NOTIFY) != 0 ||
                    (notifyProps and BluetoothGattCharacteristic.PROPERTY_INDICATE) != 0
                ) {
                    g.setCharacteristicNotification(nc, true)
                    val descriptor = nc.getDescriptor(UUID.fromString("00002902-0000-1000-8000-00805f9b34fb"))
                    if (descriptor != null) {
                        val value = if ((notifyProps and BluetoothGattCharacteristic.PROPERTY_INDICATE) != 0) {
                            BluetoothGattDescriptor.ENABLE_INDICATION_VALUE
                        } else {
                            BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE
                        }
                        gattWriteDescriptor(g, descriptor, value)
                    } else {
                        applyPreferredPhy(g)
                        _connectionState.tryEmit(true)
                        if (!result.isCompleted) result.complete(true)
                    }
                } else {
                    applyPreferredPhy(g)
                    _connectionState.tryEmit(true)
                    if (!result.isCompleted) result.complete(true)
                }
            }

            override fun onDescriptorWrite(g: BluetoothGatt, descriptor: BluetoothGattDescriptor, status: Int) {
                Log.d(TAG, "Descriptor write status=$status")
                applyPreferredPhy(g)
                _connectionState.tryEmit(true)
                if (!result.isCompleted) result.complete(true)
            }

            override fun onCharacteristicWrite(g: BluetoothGatt, characteristic: BluetoothGattCharacteristic, status: Int) {
                writeDeferred?.complete(status)
            }

            @Suppress("DEPRECATION")
            override fun onCharacteristicChanged(
                g: BluetoothGatt,
                characteristic: BluetoothGattCharacteristic,
                value: ByteArray,
            ) {
                Log.d(TAG, "RX [${value.size}B]: ${value.joinToString(" ") { "%02X".format(it) }}")
                _notifications.tryEmit(value)
            }

            @Suppress("DEPRECATION")
            override fun onCharacteristicChanged(g: BluetoothGatt, characteristic: BluetoothGattCharacteristic) {
                val v = characteristic.value ?: return
                Log.d(TAG, "RX [${v.size}B]: ${v.joinToString(" ") { "%02X".format(it) }}")
                _notifications.tryEmit(v)
            }
        }

        gatt = device.connectGatt(context, false, callback, BluetoothDevice.TRANSPORT_LE)
        withTimeoutOrNull(10_000L) { result.await() } ?: false
    }

    @SuppressLint("MissingPermission")
    private fun applyPreferredPhy(g: BluetoothGatt) {
        try {
            val (tx, rx, option) = when (PHY_MODE.lowercase()) {
                "2m" -> Triple(BluetoothDevice.PHY_LE_2M_MASK, BluetoothDevice.PHY_LE_2M_MASK, BluetoothDevice.PHY_OPTION_NO_PREFERRED)
                "1m" -> Triple(BluetoothDevice.PHY_LE_1M_MASK, BluetoothDevice.PHY_LE_1M_MASK, BluetoothDevice.PHY_OPTION_NO_PREFERRED)
                else -> Triple(BluetoothDevice.PHY_LE_CODED_MASK, BluetoothDevice.PHY_LE_CODED_MASK, BluetoothDevice.PHY_OPTION_S8)
            }
            g.setPreferredPhy(tx, rx, option)
        } catch (e: Exception) {
            Log.w(TAG, "applyPreferredPhy failed: ${e.message}")
        }
    }

    @SuppressLint("MissingPermission")
    suspend fun write(data: ByteArray, withoutResponse: Boolean = false): Boolean {
        val g = gatt ?: return false
        val c = writeChar ?: return false
        return writeMutex.withLock {
            withContext(Dispatchers.IO) {
                try {
                    val writeType = if (withoutResponse && useWriteNoResponse) {
                        BluetoothGattCharacteristic.WRITE_TYPE_NO_RESPONSE
                    } else {
                        BluetoothGattCharacteristic.WRITE_TYPE_DEFAULT
                    }

                    if (writeType == BluetoothGattCharacteristic.WRITE_TYPE_NO_RESPONSE) {
                        gattWriteCharacteristic(g, c, data, writeType)
                        delay(5L)
                    } else {
                        val deferred = CompletableDeferred<Int>()
                        writeDeferred = deferred
                        gattWriteCharacteristic(g, c, data, writeType)
                        val status = withTimeoutOrNull(3000L) { deferred.await() }
                        writeDeferred = null
                        if (status == null || status != BluetoothGatt.GATT_SUCCESS) {
                            Log.e(TAG, "Write callback failed: status=$status")
                            return@withContext false
                        }
                    }
                    true
                } catch (e: Exception) {
                    Log.e(TAG, "Write failed: ${e.message}")
                    false
                }
            }
        }
    }

    suspend fun sendHeartbeat(pageIndex: Int = 0): Boolean {
        return write(buildHeartbeat(pageIndex), withoutResponse = true)
    }

    /**
     * Request HIGH connection priority (shortest interval, ~11.25~15ms).
     * Call before bulk transfers (OTA upload, data download) to maximize throughput,
     * especially critical in multi-device scenarios where Android may have downgraded
     * individual connections to BALANCED automatically.
     *
     * Kept HIGH after transfer completes — no automatic restore.
     */
    @SuppressLint("MissingPermission")
    fun requestHighPriority(): Boolean {
        val g = gatt ?: return false
        return try {
            val ok = g.requestConnectionPriority(BluetoothGatt.CONNECTION_PRIORITY_HIGH)
            Log.d(TAG, "requestHighPriority → $ok")
            ok
        } catch (e: Exception) {
            Log.w(TAG, "requestHighPriority failed: ${e.message}")
            false
        }
    }

    @SuppressLint("MissingPermission")
    suspend fun forceReconnect(maxRetries: Int = 5): Boolean {
        val device = gatt?.device ?: return false
        for (t in 0 until maxRetries) {
            Log.d(TAG, "Reconnect attempt ${t + 1}/$maxRetries")
            try {
                gatt?.disconnect()
            } catch (e: Exception) {
                Log.w(TAG, "disconnect() during reconnect failed: ${e.message}")
            }
            delay(100)
            try {
                gatt?.close()
            } catch (e: Exception) {
                Log.w(TAG, "close() during reconnect failed: ${e.message}")
            }
            delay(100)
            try {
                val ok = connect(device)
                if (ok) {
                    Log.d(TAG, "Reconnect succeeded on attempt ${t + 1}")
                    return true
                }
            } catch (e: Exception) {
                Log.w(TAG, "connect() during reconnect failed: ${e.message}")
            }
            delay(300L * (t + 1))
        }
        Log.e(TAG, "Reconnect failed after $maxRetries attempts")
        return false
    }

    @SuppressLint("MissingPermission")
    suspend fun refreshWriteChar(): BluetoothGattCharacteristic? {
        val g = gatt ?: return null
        return withContext(Dispatchers.IO) {
            try {
                val services = g.services ?: return@withContext null
                var wnr: BluetoothGattCharacteristic? = null
                var wr: BluetoothGattCharacteristic? = null
                for (s in services) {
                    for (c in s.characteristics) {
                        if ((c.properties and BluetoothGattCharacteristic.PROPERTY_WRITE_NO_RESPONSE) != 0 && wnr == null) wnr = c
                        if ((c.properties and BluetoothGattCharacteristic.PROPERTY_WRITE) != 0 && wr == null) wr = c
                    }
                }
                val fresh = wnr ?: wr
                if (fresh != null) {
                    writeChar = fresh
                    useWriteNoResponse = wnr != null
                }
                fresh
            } catch (e: Exception) {
                Log.w(TAG, "refreshWriteChar failed: ${e.message}")
                null
            }
        }
    }

    @SuppressLint("MissingPermission")
    private fun clearGattCache() {
        try {
            val g = gatt ?: return
            val method = g.javaClass.getMethod("refresh")
            method.invoke(g)
            Thread.sleep(100)
        } catch (e: Exception) {
            Log.w(TAG, "clearGattCache failed: ${e.message}")
        }
    }

    @SuppressLint("MissingPermission")
    private fun setNotifyEnabled(enabled: Boolean) {
        val g = gatt ?: return
        val nc = notifyChar ?: return
        try {
            g.setCharacteristicNotification(nc, enabled)
            val descriptor = nc.getDescriptor(UUID.fromString("00002902-0000-1000-8000-00805f9b34fb"))
            if (descriptor != null) {
                val value = if (enabled) {
                    BluetoothGattDescriptor.ENABLE_NOTIFICATION_VALUE
                } else {
                    BluetoothGattDescriptor.DISABLE_NOTIFICATION_VALUE
                }
                gattWriteDescriptor(g, descriptor, value)
            }
        } catch (e: Exception) {
            Log.w(TAG, "setNotifyEnabled($enabled) failed: ${e.message}")
        }
    }


    @SuppressLint("MissingPermission")
    suspend fun uploadFirmware(
        data: ByteArray,
        awaitStartAck: suspend (Long) -> Boolean,
        onProgress: (Double) -> Unit,
    ): Long {
        val startTime = System.currentTimeMillis()

        try {
            Log.d(TAG, "OTA start frame sent (fileSize=${data.size}); fixed 3000ms wait before payload")
            delay(50)
            write(makeStartFrame(data.size), withoutResponse = true)
            delay(3000)

            var payload = min(200, payloadFromMtu(currentMtu))
            val total = data.size
            var i = 0
            var lastProgress = 0.0

            while (i < total) {
                val end = min(i + payload, total)
                val chunk = data.copyOfRange(i, end)

                try {
                    write(chunk, withoutResponse = true)
                    delay(30)
                    i = end
                } catch (e: Exception) {
                    val msg = e.message ?: ""

                    if (msg.contains("133") || msg.contains("disconnected") || msg.contains("not connected")) {
                        val reconnected = forceReconnect(maxRetries = 5)
                        if (!reconnected) throw Exception("BLE reconnect failed")
                        refreshWriteChar()
                        delay(150)
                        continue
                    }

                    if (payload > 32) {
                        payload = max(32, payload - 16)
                        delay(100)
                        continue
                    }

                    throw e
                }

                val progress = i.toDouble() / total
                if (progress > lastProgress + 0.001) {
                    lastProgress = progress
                    onProgress(progress)
                }
            }

            delay(80)
            write(u32le(crc32(data)), withoutResponse = true)
            delay(30)
            write(makeEndFrame(), withoutResponse = true)

            // 기기 결과 프레임 대기 (CMD=0x0051, DATA=결과코드)
            val resultFrame = withTimeoutOrNull(10_000L) {
                notifications.mapNotNull { raw ->
                    val frame = parseFrame(raw)
                    if (frame != null && frame.cmd == 0x0051) frame else null
                }.first()
            }

            if (resultFrame == null) {
                throw Exception("Device response timeout (10s)")
            }
            val resultCode = if (resultFrame.data.size >= 2)
                ((resultFrame.data[0].toInt() and 0xFF) shl 8) or (resultFrame.data[1].toInt() and 0xFF)
            else 0
            if (resultCode != 0x0001) {
                throw Exception("Device rejected: error 0x${"%04X".format(resultCode)}")
            }

            onProgress(1.0)
            return System.currentTimeMillis() - startTime
        } finally {
            try {
                setNotifyEnabled(true)
            } catch (e: Exception) {
                Log.w(TAG, "Re-enable notifications after upload failed: ${e.message}")
            }
        }
    }

    private fun payloadFromMtu(mtu: Int): Int {
        var p = mtu - 3
        if (p < 20) p = 20
        if (p > 244) p = 244
        return p
    }

    @SuppressLint("MissingPermission")
    fun disconnect() {
        try {
            val nc = notifyChar
            val g = gatt
            if (nc != null && g != null) {
                g.setCharacteristicNotification(nc, false)
            }
            g?.disconnect()
            g?.close()
        } catch (e: Exception) {
            Log.w(TAG, "disconnect cleanup failed: ${e.message}")
        }

        gatt = null
        writeChar = null
        notifyChar = null
        _connectionState.tryEmit(false)
    }
}