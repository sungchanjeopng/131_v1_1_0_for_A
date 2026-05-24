package com.wws2.densitymeter.model

data class ScannedDevice(
    val address: String,
    val name: String,
    val rawName: String = "",     // 원본 BLE 이름 (AT+MANUF)
    val rssi: Int,
    val advData: String = "",     // AT+ADVDATA 원본
    val ch1SiteName: String = "", // 파싱된 CH1 기기번호 (예: "A01")
    val ch2SiteName: String = "", // 파싱된 CH2 기기번호 (예: "A02", 없으면 "")
    val fwVersion: String = "",   // 파싱된 FW 버전 (예: "1.0.9")
)
