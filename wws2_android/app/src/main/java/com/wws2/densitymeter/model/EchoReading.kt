package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder

data class EchoReading(
    val eeaR: Int,
    val eeaD: Int,
    val level: Double,       // raw U16 from firmware
    val detAreaLO: Int,
    val detAreaHI: Int,
    val pipeDia: Int,
    val rawWave: List<Int>,  // 103 points
    val wave: List<Double>,  // 816 points interpolated
    val sampleUs: Float,     // ADC sample interval in µs (from DWT measurement)
    // THR (계면계专用)
    val thrLightDist: Int,   // x0.01m, 미검출=0
    val thrHeavyDist: Int,   // x0.01m, 미검출=0
    val thrLightAmp: Int,    // 0~65535
    val thrHeavyAmp: Int,    // 0~65535
) {
    companion object {
        const val INTP_SIZE = 816       // 102 intervals × 8 (firmware ADC_INTP_SIZE)
        const val MM_RANGE  = 300       // display window in mm
        fun fromBytes(data: ByteArray, sampleUs: Float = 2.0f): EchoReading? {
            if (data.size < 220) return null
            val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)
            val eeaR = buf.short.toInt() and 0xFFFF
            val eeaD = buf.short.toInt() and 0xFFFF
            val rawLevel = buf.short.toInt() and 0xFFFF
            val detLO = buf.short.toInt() and 0xFFFF
            val detHI = buf.short.toInt() and 0xFFFF
            val pipeDia = buf.short.toInt() and 0xFFFF
            buf.short  // err (에러코드) — skip

            val rawWave = mutableListOf<Int>()
            for (i in 0 until 103) {
                rawWave.add(buf.short.toInt() and 0xFFFF)
            }

            val wave = interpolateX8(rawWave)

            // THR 추가 필드 (220B 이후, 계면계)
            val thrLightDist = if (data.size >= 222) (buf.short.toInt() and 0xFFFF) else 0
            val thrHeavyDist = if (data.size >= 224) (buf.short.toInt() and 0xFFFF) else 0
            val thrLightAmp = if (data.size >= 226) (buf.short.toInt() and 0xFFFF) else 0
            val thrHeavyAmp = if (data.size >= 228) (buf.short.toInt() and 0xFFFF) else 0

            return EchoReading(eeaR, eeaD, rawLevel.toDouble(), detLO, detHI, pipeDia, rawWave, wave, sampleUs, thrLightDist, thrHeavyDist, thrLightAmp, thrHeavyAmp)
        }

        private fun interpolateX8(src: List<Int>): List<Double> {
            val dst = DoubleArray(INTP_SIZE)
            // 102 intervals × 8 = 816 points (firmware ADC_INTP_SIZE)
            for (j in 0 until 102) {
                val base = j * 8
                val cur = src[j].toDouble()
                val nxt = src[j + 1].toDouble()
                val diff = (nxt - cur) / 8.0
                dst[base] = cur
                for (k in 1 until 8) {
                    val idx = base + k
                    if (idx >= INTP_SIZE) break
                    dst[idx] = cur + diff * k
                }
            }
            return dst.toList()
        }
    }
}
