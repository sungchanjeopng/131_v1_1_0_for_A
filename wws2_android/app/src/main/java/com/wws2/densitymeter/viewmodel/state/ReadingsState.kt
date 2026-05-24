package com.wws2.densitymeter.viewmodel.state

import com.wws2.densitymeter.model.*

data class ReadingsState(
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
    val asf: Int = 0,
    val relay: Int = 0,
    val echoReading: EchoReading? = null,
    val interfaceEchoReading: InterfaceEchoReading? = null,
    val interfaceDiag: InterfaceDiagReading? = null,
    val echoMode: EchoMode = EchoMode.REAL,
    val interfaceReading: InterfaceReading? = null,
)
