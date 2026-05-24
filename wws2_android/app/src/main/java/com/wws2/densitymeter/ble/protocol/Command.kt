package com.wws2.densitymeter.ble.protocol

/**
 * BLE protocol command constants.
 * Matches firmware Comm_ProcBle() command IDs.
 */
object Command {
    // Pairing / Device Info
    const val CMD_DEVICE_INFO = 0x00F0

    // Heartbeat
    const val CMD_OTA_START = 0x0050
    const val CMD_OTA_END = 0x0051

    // Density meter responses
    const val CMD_STATUS = 0x0000
    const val CMD_ECHO = 0x0001
    const val CMD_TREND = 0x0002
    const val CMD_CALIB = 0x0003
    const val CMD_DIAG = 0x0004

    // Interface meter responses (CH1)
    const val CMD_IF_ECHO_REAL = 0x0001
    const val CMD_IF_ECHO_AVG = 0x0005

    // Interface meter CH2 offsets
    const val CMD_STATUS_CH2 = 0x0010
    const val CMD_ECHO_CH2 = 0x0011
    const val CMD_TREND_CH2 = 0x0012
    const val CMD_DIAG_CH2 = 0x0014
    const val CMD_IF_ECHO_AVG_CH2 = 0x0015

    // Data download
    const val CMD_DOWNLOAD = 0x0007
    const val CMD_DOWNLOAD_CH2 = 0x0017

    // Data download cancel (app -> device request; device echoes same CMD as ack)
    const val CMD_DOWNLOAD_CANCEL = 0x0008
    const val CMD_DOWNLOAD_CANCEL_CH2 = 0x0018

    // Stream end marker
    const val CMD_TREND_END = 0x00FE

    // Heartbeat page indices (app -> device)
    const val PAGE_STATUS = 0x00
    const val PAGE_ECHO = 0x01
    const val PAGE_TREND = 0x02
    const val PAGE_MENU = 0x04
    const val PAGE_PAIRING = 0x05
    const val PAGE_UPLOAD = 0x06
    const val PAGE_DOWNLOAD = 0x07

    // CH2 page offsets
    const val PAGE_STATUS_CH2 = 0x10
    const val PAGE_ECHO_CH2 = 0x11
    const val PAGE_TREND_CH2 = 0x12
    const val PAGE_ECHO_AVG_CH2 = 0x15
    const val PAGE_DOWNLOAD_CH2 = 0x17

    // Device info lengths
    const val LEN_DEVICE_INFO_DENSITY: Short = 0x0005
    const val LEN_DEVICE_INFO_INTERFACE: Short = 0x0007
}
