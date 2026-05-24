package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.time.LocalDateTime

/**
 * Interface meter trend record - 13 bytes per record
 * [time 5B] [CH1_Light 2B] [CH1_Heavy 2B] [CH2_Light 2B] [CH2_Heavy 2B]
 */
data class InterfaceTrendRecord(
    val dateTime: LocalDateTime,
    val ch1Light: Double,      // x0.01m
    val ch1Heavy: Double,      // x0.01m
    val ch2Light: Double,      // x0.01m
    val ch2Heavy: Double,      // x0.01m
) {
    companion object {
        const val RECORD_SIZE = 13

        fun fromBytes(data: ByteArray): InterfaceTrendRecord? {
            if (data.size < RECORD_SIZE) return null
            val year = 2000 + (data[0].toInt() and 0xFF)
            val month = (data[1].toInt() and 0xFF).coerceIn(1, 12)
            val day = (data[2].toInt() and 0xFF).coerceIn(1, 31)
            val hour = (data[3].toInt() and 0xFF).coerceIn(0, 23)
            val minute = (data[4].toInt() and 0xFF).coerceIn(0, 59)

            val buf = ByteBuffer.wrap(data, 5, 8).order(ByteOrder.BIG_ENDIAN)
            val ch1LightRaw = buf.short.toInt() and 0xFFFF
            val ch1HeavyRaw = buf.short.toInt() and 0xFFFF
            val ch2LightRaw = buf.short.toInt() and 0xFFFF
            val ch2HeavyRaw = buf.short.toInt() and 0xFFFF

            return try {
                InterfaceTrendRecord(
                    dateTime = LocalDateTime.of(year, month, day, hour, minute),
                    ch1Light = ch1LightRaw * 0.01,
                    ch1Heavy = ch1HeavyRaw * 0.01,
                    ch2Light = ch2LightRaw * 0.01,
                    ch2Heavy = ch2HeavyRaw * 0.01,
                )
            } catch (_: Exception) { null }
        }
    }
}
