package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder

data class DiagReading(
    val temperature: Double, // x0.1°C
    val currentMA: Double,   // x0.01mA
    val damping: Int,
    val set4mA: Double,      // x0.01m
    val set20mA: Double,     // x0.01m
    val pipeDia: Int,
    val freqMHz: Double,     // x0.001MHz
) {
    companion object {
        fun fromBytes(data: ByteArray): DiagReading? {
            if (data.size != 16) return null
            val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)
            val rawTemp = buf.short.toInt()
            val rawCurrent = buf.short.toInt() and 0xFFFF
            val rawDamping = buf.short.toInt() and 0xFFFF
            val raw4mA = buf.short.toInt() and 0xFFFF
            val raw20mA = buf.short.toInt() and 0xFFFF
            val rawPipeDia = buf.short.toInt() and 0xFFFF
            val rawFreq = buf.short.toInt() and 0xFFFF
            buf.short  // err (에러코드) — Status 응답에서 수신하므로 skip
            return DiagReading(
                temperature = rawTemp * 0.1,
                currentMA = rawCurrent * 0.01,
                damping = rawDamping,
                set4mA = raw4mA * 0.01,
                set20mA = raw20mA * 0.01,
                pipeDia = rawPipeDia,
                freqMHz = rawFreq * 0.001,
            )
        }
    }
}
