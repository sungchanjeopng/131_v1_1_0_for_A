package com.wws2.densitymeter.service

import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.bluetooth.le.*
import android.content.Context
import android.os.SystemClock
import android.util.Log
import com.wws2.densitymeter.model.ScannedDevice
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.update
import java.util.Collections

private const val TAG = "BleConnection"

class BleConnectionService(private val context: Context) {

    private val bluetoothManager = context.getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
    private val bluetoothAdapter: BluetoothAdapter? = bluetoothManager.adapter
    private var scanner: BluetoothLeScanner? = null
    private var scanCallback: ScanCallback? = null

    private val _scannedDevices = MutableStateFlow<Map<String, ScannedDevice>>(emptyMap())
    val scannedDevices: StateFlow<Map<String, ScannedDevice>> = _scannedDevices

    private val _isScanning = MutableStateFlow(false)
    val isScanning: StateFlow<Boolean> = _isScanning

    val connectingIds: MutableSet<String> = Collections.synchronizedSet(mutableSetOf())

    // 스캔 재시작 속도 제한: Android BLE 스캔 빈도 제한 + 자체 재시도 루프 방지
    @Volatile private var lastScanStartMs: Long = 0L
    private val SCAN_RESTART_MIN_INTERVAL_MS = 1000L

    @SuppressLint("MissingPermission")
    fun startScan() {
        if (_isScanning.value) return

        val now = SystemClock.elapsedRealtime()
        if (now - lastScanStartMs < SCAN_RESTART_MIN_INTERVAL_MS) {
            Log.d(TAG, "startScan throttled (last=${now - lastScanStartMs}ms ago)")
            return
        }
        lastScanStartMs = now

        scanner = bluetoothAdapter?.bluetoothLeScanner ?: return

        val callback = object : ScanCallback() {
            override fun onScanResult(callbackType: Int, result: ScanResult) {
                val device = result.device
                val name = result.scanRecord?.deviceName ?: device.name ?: ""
                if (name.isBlank()) return
                val lower = name.lowercase()
                // 우리 제품만: W3(계면계), W2(농도계), 기존 호환(WE13, WE23, ENV, CHIPSEN)
                if (!(lower.startsWith("w3") || lower.startsWith("w2")
                    || lower.contains("we13") || lower.contains("we23")
                    || lower.contains("env") || lower.contains("chipsen"))) return

                val address = device.address
                Log.d(TAG, "SCAN: name=$name, addr=$address")

                // AT+MANUF 이름에서 제품 타입 + 기기번호 파싱
                // W3A01A02 → 계면계, CH1=A01, CH2=A02
                // W2A01    → 농도계, CH1=A01
                // WE13/WE23 → 기존 호환
                val isInterface = lower.startsWith("w3") || lower.contains("we13") || lower.contains("env130")
                val productName = if (isInterface) "ENV130" else "ENV230"

                var ch1Site = ""
                var ch2Site = ""
                val stripped = when {
                    lower.startsWith("w3") -> name.substring(2)   // "W3A01A02" → "A01A02"
                    lower.startsWith("w2") -> name.substring(2)   // "W2A01" → "A01"
                    else -> ""
                }
                if (stripped.length >= 6) {
                    ch1Site = stripped.substring(0, 3)
                    ch2Site = stripped.substring(3, 6)
                } else if (stripped.length >= 3) {
                    ch1Site = stripped.substring(0, 3)
                }

                val displayName = if (ch1Site.isNotEmpty()) {
                    if (ch2Site.isNotEmpty()) "$productName  $ch1Site / $ch2Site"
                    else "${productName}_$ch1Site"
                } else {
                    productName
                }

                _scannedDevices.update { existing ->
                    existing + (address to ScannedDevice(
                        address = address,
                        name = displayName,
                        rawName = name,
                        rssi = result.rssi,
                        ch1SiteName = ch1Site,
                        ch2SiteName = ch2Site,
                    ))
                }
            }

            override fun onScanFailed(errorCode: Int) {
                Log.e(TAG, "Scan failed: $errorCode")
                _isScanning.value = false
            }
        }

        scanCallback = callback
        val settings = ScanSettings.Builder()
            .setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY)
            .build()

        scanner?.startScan(null, settings, callback)
        _isScanning.value = true
    }

    @SuppressLint("MissingPermission")
    fun stopScan() {
        val cb = scanCallback ?: return
        try {
            scanner?.stopScan(cb)
        } catch (e: Exception) {
            Log.w(TAG, "stopScan failed: ${e.message}")
        }
        scanCallback = null
        _isScanning.value = false
    }

    @SuppressLint("MissingPermission")
    fun getRemoteDevice(address: String): BluetoothDevice? {
        return bluetoothAdapter?.getRemoteDevice(address)
    }

    fun signalLevel(rssi: Int): Int {
        return when {
            rssi >= -55 -> 3
            rssi >= -72 -> 2
            else -> 1
        }
    }

    /**
     * BLE Advertising raw bytes에서 ADVDATA(User Data) 추출.
     * BoT-nLE521은 AT+ADVDATA를 Manufacturer Specific Data(type=0xFF)로 광고함.
     */
    private fun parseAdvData(scanBytes: ByteArray): String {
        var i = 0
        while (i < scanBytes.size - 1) {
            val len = scanBytes[i].toInt() and 0xFF
            if (len == 0 || i + len >= scanBytes.size) break
            val type = scanBytes[i + 1].toInt() and 0xFF
            if (type == 0xFF && len > 3) {
                // Manufacturer Specific Data: skip 2-byte company ID
                val dataStart = i + 4
                val dataEnd = i + 1 + len
                if (dataEnd <= scanBytes.size) {
                    return String(scanBytes, dataStart, dataEnd - dataStart, Charsets.US_ASCII).trim('\u0000')
                }
            }
            i += len + 1
        }
        return ""
    }

    fun dispose() {
        stopScan()
    }
}
