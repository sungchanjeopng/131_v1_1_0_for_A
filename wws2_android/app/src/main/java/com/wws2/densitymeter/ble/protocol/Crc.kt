package com.wws2.densitymeter.ble.protocol

/**
 * CRC algorithms used by the BLE protocol.
 * Pure functions with no state or dependencies.
 */
object Crc {

    /** CRC-16 Modbus (polynomial 0xA001) */
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

    /** Incremental CRC-16 update for a single byte */
    fun crc16Update(crc: Int, b: Byte): Int {
        var c = crc xor (b.toInt() and 0xFF)
        repeat(8) {
            c = if (c and 0x0001 != 0) (c ushr 1) xor 0xA001 else c ushr 1
        }
        return c
    }

    /** CRC-32 (polynomial 0xEDB88320, same as firmware BspMram_Crc32) */
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
}
