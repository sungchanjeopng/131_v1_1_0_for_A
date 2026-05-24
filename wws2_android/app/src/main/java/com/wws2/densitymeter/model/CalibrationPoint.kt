package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder

data class CalibrationPoint(
    val fEEA: Boolean,
    val fLV: Boolean,
    val eea: Int,
    val density: Double,   // raw U16 from firmware
    val year: Int,
    val month: Int,
    val day: Int,
    val hour: Int,
    val minute: Int,
) {
    companion object {
        fun fromBytes(data: ByteArray): List<CalibrationPoint>? {
            if (data.size < 80) return null
            val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)
            return List(5) { i ->
                val o = i * 16
                val flag = buf.getShort(o).toInt() and 0xFFFF
                CalibrationPoint(
                    fEEA = (flag and 0x0001) != 0,
                    fLV  = (flag and 0x0002) != 0,
                    eea = buf.getShort(o + 2).toInt() and 0xFFFF,
                    density = (buf.getShort(o + 4).toInt() and 0xFFFF).toDouble(),
                    year = (buf.getShort(o + 6).toInt() and 0xFFFF) + 2000,
                    month = buf.getShort(o + 8).toInt() and 0xFFFF,
                    day = buf.getShort(o + 10).toInt() and 0xFFFF,
                    hour = buf.getShort(o + 12).toInt() and 0xFFFF,
                    minute = buf.getShort(o + 14).toInt() and 0xFFFF,
                )
            }
        }
    }
}
