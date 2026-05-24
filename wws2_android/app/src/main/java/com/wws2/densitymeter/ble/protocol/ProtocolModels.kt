package com.wws2.densitymeter.ble.protocol

/**
 * Data types used in the BLE protocol layer.
 * Extracted from BleProtocolService nested classes.
 */

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
    data object PinFailed : PairingResult()
}

data class ParsedFrame(val cmd: Int, val data: ByteArray)
