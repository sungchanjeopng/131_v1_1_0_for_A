package com.wws2.densitymeter.ble.scanner

import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.bluetooth.le.*
import android.content.Context
import android.util.Log
import com.wws2.densitymeter.model.ScannedDevice
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.StateFlow
import kotlinx.coroutines.flow.update
import java.util.Collections

private const val TAG = "BleScanner"

/**
 * BLE device discovery and scanning.
 * Filters for WESSWARE devices (W2/W3/ENV/CHIPSEN).
 * Renamed from BleConnectionService to better reflect its single responsibility.
 */
class BleScanner(private val context: Context) {

    private val bluetoothManager = context.getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
    private val bluetoothAdapter: BluetoothAdapter? = bluetoothManager.adapter
    private var scanner: BluetoothLeScanner? = null
    private var scanCallback: ScanCallback? = null

    private val _scannedDevices = MutableStateFlow<Map<String, ScannedDevice>>(emptyMap())
    val scannedDevices: StateFlow<Map<String, ScannedDevice>> = _scannedDevices

    private val _isScanning = MutableStateFlow(false)
    val isScanning: StateFlow<Boolean> = _isScanning

    val connectingIds: MutableSet<String> = Collections.synchronizedSet(mutableSetOf())

    @SuppressLint("MissingPermission")
    fun startScan() {
        if (_isScanning.value) return

        scanner = bluetoothAdapter?.bluetoothLeScanner ?: return

        val callback = object : ScanCallback() {
            override fun onScanResult(callbackType: Int, result: ScanResult) {
                val device = result.device
                val name = result.scanRecord?.deviceName ?: device.name ?: ""
                if (name.isBlank()) return
                val lower = name.lowercase()
                if (!(lower.startsWith("w3") || lower.startsWith("w2")
                            || lower.contains("we13") || lower.contains("we23")
                            || lower.contains("env") || lower.contains("chipsen"))) return

                val address = device.address
                Log.d(TAG, "SCAN: name=$name, addr=$address")

                val isInterface = lower.startsWith("w3") || lower.contains("we13") || lower.contains("env130")
                val productName = if (isInterface) "ENV130" else "ENV230"

                var ch1Site = ""
                var ch2Site = ""
                val stripped = when {
                    lower.startsWith("w3") -> name.substring(2)
                    lower.startsWith("w2") -> name.substring(2)
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

    fun dispose() {
        stopScan()
    }
}
