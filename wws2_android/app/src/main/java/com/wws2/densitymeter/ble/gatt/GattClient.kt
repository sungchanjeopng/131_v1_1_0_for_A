package com.wws2.densitymeter.ble.gatt

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
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.delay
import kotlinx.coroutines.flow.MutableSharedFlow
import kotlinx.coroutines.flow.SharedFlow
import kotlinx.coroutines.sync.Mutex
import kotlinx.coroutines.sync.withLock
import kotlinx.coroutines.withContext
import kotlinx.coroutines.withTimeoutOrNull
import java.util.UUID

private const val TAG = "GattClient"
const val PHY_MODE = "2m"

/**
 * Low-level BLE GATT connection management.
 * Handles connect/disconnect, characteristic discovery, MTU negotiation,
 * write operations with mutex, and notification flow.
 *
 * This class has zero knowledge of protocol framing — it only deals with raw bytes.
 * Corresponds to the firmware's BSP layer (bsp_uart.c / bsp_demux.c).
 */
class GattClient(private val context: Context) {

    @Volatile private var gatt: BluetoothGatt? = null
    @Volatile private var writeChar: BluetoothGattCharacteristic? = null
    @Volatile private var notifyChar: BluetoothGattCharacteristic? = null
    @Volatile private var useWriteNoResponse = false
    @Volatile var currentMtu: Int = 23
        private set
    @Volatile private var writeDeferred: CompletableDeferred<Int>? = null
    private val writeMutex = Mutex()

    private val _notifications = MutableSharedFlow<ByteArray>(extraBufferCapacity = 64)
    val notifications: SharedFlow<ByteArray> = _notifications

    private val _connectionState = MutableSharedFlow<Boolean>(extraBufferCapacity = 4)
    val connectionState: SharedFlow<Boolean> = _connectionState

    val isConnected: Boolean get() = gatt != null && writeChar != null

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

    @SuppressLint("MissingPermission")
    suspend fun forceReconnect(maxRetries: Int = 5): Boolean {
        val device = gatt?.device ?: return false
        for (t in 0 until maxRetries) {
            Log.d(TAG, "Reconnect attempt ${t + 1}/$maxRetries")
            try { gatt?.disconnect() } catch (e: Exception) { Log.w(TAG, "disconnect() during reconnect failed: ${e.message}") }
            delay(100)
            try { gatt?.close() } catch (e: Exception) { Log.w(TAG, "close() during reconnect failed: ${e.message}") }
            delay(100)
            try {
                val ok = connect(device)
                if (ok) {
                    Log.d(TAG, "Reconnect succeeded on attempt ${t + 1}")
                    return true
                }
            } catch (e: Exception) { Log.w(TAG, "connect() during reconnect failed: ${e.message}") }
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
    fun setNotifyEnabled(enabled: Boolean) {
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

    fun payloadFromMtu(): Int {
        var p = currentMtu - 3
        if (p < 20) p = 20
        if (p > 244) p = 244
        return p
    }
}
