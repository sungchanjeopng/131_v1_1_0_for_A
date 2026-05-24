package com.wws2.densitymeter.viewmodel.state

import com.wws2.densitymeter.model.ConnectedBleDevice
import com.wws2.densitymeter.model.DeviceType

data class ConnectionState(
    val connectedDevices: List<ConnectedBleDevice> = emptyList(),
    val visibleDeviceIds: Set<String> = emptySet(),
    val activeDeviceId: String = "",
    val activeDeviceLabel: String = "",
    val connectingIds: Set<String> = emptySet(),
    val deviceType: DeviceType = DeviceType.DENSITY,
    val rxBlink: Boolean = false,
)
