package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder

/**
 * 계면계 Echo 파형 데이터 (헤더 25B + wave 가변)
 *
 * | # | offset | size | name          |
 * |---|--------|------|---------------|
 * | 1 |   0    |  2B  | lightLevel    |
 * | 2 |   2    |  2B  | heavyLevel    |
 * | 3 |   4    |  2B  | deadzone      |
 * | 4 |   6    |  2B  | empty         |
 * | 5 |   8    |  2B  | thrLightDist  |
 * | 6 |  10    |  2B  | thrHeavyDist  |
 * | 7 |  12    |  2B  | thrLightReal  |
 * | 8 |  14    |  2B  | thrHeavyReal  |
 * | 9 |  16    |  2B  | thrLightSet   |
 * |10 |  18    |  2B  | thrHeavySet   |
 * |11 |  20    |  1B  | thrLightMode  |
 * |12 |  21    |  1B  | thrHeavyMode  |
 * |13 |  22    |  2B  | echoAmp       |
 * |14 |  24    |  1B  | statusCh      |
 * |15 |  25    | N×2B | wave[0~N-1]   |
 */
data class InterfaceEchoReading(
    val lightLevel: Double,    // x0.01m
    val heavyLevel: Double,    // x0.01m
    val deadzone: Int,
    val empty: Int,
    val thrLightDist: Int,
    val thrHeavyDist: Int,
    val thrLightReal: Int,     // 실제 계산된 THR 진폭 (0~4095)
    val thrHeavyReal: Int,
    val thrLightSet: Int,      // 설정 THR (Auto:0~95%, Manual:0~32)
    val thrHeavySet: Int,
    val thrLightMode: Int,     // 0=Auto, 1=Manual
    val thrHeavyMode: Int,
    val echoAmp: Int,
    val statusCh: Int,         // 0=WEAK, 1=TRAC, 2=OK, 3=STOP, 4=IDLE, 5=NG, 6=TPR_NG
    val temperature: Int = 0,  // signed, x0.1°C
    val wave: List<Int>,       // raw wave samples (0~4095)
) {
    val statusLabel: String
        get() = when (statusCh) {
            0, 4 -> "ST00"
            1    -> "ST01"
            2    -> "ST02"
            3    -> "ST03"
            5    -> "ER01"
            6    -> "ER02"
            else -> "--"
        }

    val thrLightModeLabel: String get() = if (thrLightMode == 0) "Auto" else "Manual"
    val thrHeavyModeLabel: String get() = if (thrHeavyMode == 0) "Auto" else "Manual"

    /** EchoChart 표시용 EchoReading 변환 (보간 없이 raw wave 그대로) */
    fun toEchoReading(): EchoReading {
        val waveDouble = wave.map { it.toDouble() }
        return EchoReading(
            eeaR = echoAmp,
            eeaD = echoAmp,
            level = lightLevel,
            detAreaLO = deadzone,
            detAreaHI = empty,
            pipeDia = 0,
            rawWave = wave,
            wave = waveDouble,
            sampleUs = 2.0f,
            thrLightDist = thrLightDist,
            thrHeavyDist = thrHeavyDist,
            thrLightAmp = thrLightReal,
            thrHeavyAmp = thrHeavyReal,
        )
    }

    companion object {
        private const val HEADER_SIZE = 30  // 14필드×2B + Temperature 2B

        fun fromBytes(data: ByteArray): InterfaceEchoReading? {
            if (data.size < HEADER_SIZE) return null
            val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)

            val rawLightLevel = buf.short.toInt() and 0xFFFF
            val rawHeavyLevel = buf.short.toInt() and 0xFFFF
            val deadzone      = buf.short.toInt() and 0xFFFF
            val empty         = buf.short.toInt() and 0xFFFF
            val thrLightDist  = buf.short.toInt() and 0xFFFF
            val thrHeavyDist  = buf.short.toInt() and 0xFFFF
            val thrLightReal  = buf.short.toInt() and 0xFFFF
            val thrHeavyReal  = buf.short.toInt() and 0xFFFF
            val thrLightSet   = buf.short.toInt() and 0xFFFF
            val thrHeavySet   = buf.short.toInt() and 0xFFFF
            val thrLightMode  = buf.short.toInt() and 0xFFFF  // 2B
            val thrHeavyMode  = buf.short.toInt() and 0xFFFF  // 2B
            val echoAmp       = buf.short.toInt() and 0xFFFF
            val statusCh      = buf.short.toInt() and 0xFFFF  // 2B
            val temperature   = buf.short.toInt()              // signed, x0.1°C

            // wave: remaining bytes → N samples (U16 each)
            val waveByteCount = data.size - HEADER_SIZE
            val waveSampleCount = waveByteCount / 2
            val wave = mutableListOf<Int>()
            for (i in 0 until waveSampleCount) {
                wave.add(buf.short.toInt() and 0xFFFF)
            }

            return InterfaceEchoReading(
                lightLevel   = rawLightLevel * 0.01,
                heavyLevel   = rawHeavyLevel * 0.01,
                deadzone     = deadzone,
                empty        = empty,
                thrLightDist = thrLightDist,
                thrHeavyDist = thrHeavyDist,
                thrLightReal = thrLightReal,
                thrHeavyReal = thrHeavyReal,
                thrLightSet  = thrLightSet,
                thrHeavySet  = thrHeavySet,
                thrLightMode = thrLightMode,
                thrHeavyMode = thrHeavyMode,
                echoAmp      = echoAmp,
                statusCh     = statusCh,
                temperature  = temperature,
                wave         = wave,
            )
        }
    }
}
