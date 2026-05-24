package com.wws2.densitymeter.model

import android.bluetooth.BluetoothDevice

data class ConnectedBleDevice(
    val id: String,
    val label: String,
    val device: BluetoothDevice? = null,
    val firmwareVersion: String = "",  // "V0.1", "V1.1" 등
    val deviceType: Int = 0,  // 0=DENSITY, 1=INTERFACE
)
