package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder

/**
 * 계면계 Diag 응답 (LEN=0x12, 18B)
 *
 * | offset | size | name        |
 * |--------|------|-------------|
 * |   0    |  2B  | temperature | S16, x0.1°C
 * |   2    |  2B  | current     | U16, x0.01mA
 * |   4    |  1B  | freq        | enum (0=130K,1=160K,2=270K,3=380K)
 * |   5    |  2B  | offset      | S16, x0.01m
 * |   7    |  2B  | set4mA      | U16, x0.01
 * |   9    |  2B  | set20mA     | U16, x0.01
 * |  11    |  2B  | tvg         | U16
 * |  13    |  2B  | damp        | U16
 * |  15    |  2B  | asf         | U16
 * |  17    |  1B  | relay       | 0=OPEN(ON), 1=CLOSED(OFF)
 */
data class InterfaceDiagReading(
    val temperature: Double,
    val currentMA: Double,
    val freq: Int,
    val offset: Double,
    val set4mA: Double,
    val set20mA: Double,
    val tvg: Int,
    val damp: Int,
    val asf: Int,
    val relayOn: Boolean,
) {
    val freqLabel: String get() = when (freq) {
        0 -> "130K"
        1 -> "160K"
        2 -> "270K"
        3 -> "380K"
        else -> "--"
    }

    companion object {
        fun fromBytes(data: ByteArray): InterfaceDiagReading? {
            if (data.size < 22) return null
            val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)
            val rawTemp    = buf.short.toInt()                // S16 온도
            val rawCurrent = buf.short.toInt() and 0xFFFF     // U16 전류
            val rawFreq    = buf.short.toInt() and 0xFFFF     // U16 주파수 (2B)
            val rawOffset  = buf.short.toInt()                // S16 오프셋
            val raw4mA     = buf.short.toInt() and 0xFFFF     // U16
            val raw20mA    = buf.short.toInt() and 0xFFFF     // U16
            val rawTvg     = buf.short.toInt() and 0xFFFF     // U16
            val rawDamp    = buf.short.toInt() and 0xFFFF     // U16
            val rawAsf     = buf.short.toInt() and 0xFFFF     // U16
            val rawRelay   = buf.short.toInt() and 0xFFFF     // U16 릴레이 (2B)
            val rawError   = buf.short.toInt() and 0xFFFF     // U16 에러코드 (2B)

            return InterfaceDiagReading(
                temperature = rawTemp * 0.1,
                currentMA   = rawCurrent * 0.01,
                freq        = rawFreq,
                offset      = rawOffset * 0.01,
                set4mA      = raw4mA * 0.01,
                set20mA     = raw20mA * 0.01,
                tvg         = rawTvg,
                damp        = rawDamp,
                asf         = rawAsf,
                relayOn     = rawRelay == 0,
            )
        }
    }
}
