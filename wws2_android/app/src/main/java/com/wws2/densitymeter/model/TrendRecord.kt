package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.time.LocalDateTime

data class TrendRecord(
    val dateTime: LocalDateTime,
    val eeaD: Int,
    val dst: Double,          // x0.01m
    val temperature: Double,  // x0.1°C
    val step: Int = 0,
    val vca: Int = 0,
    val status: Int = 0,
    val deviceId: String = "",  // 실시간 트렌드 채널 구분용 (a01=..._CH1, a02=..._CH2). 다운로드/과거 기록은 ""
) {
    companion object {
        // 24B record from firmware: [00][year][00][month][00][day][00][hour][00][min][00][sec]
        //   [eea_H][eea_L][density_H][density_L][temp_H][temp_L]
        //   [00][step][vca_H][vca_L][00][status]
        fun fromBytes(data: ByteArray): TrendRecord? {
            if (data.size < 24) return null
            val year   = 2000 + (data[1].toInt() and 0xFF)
            val month  = (data[3].toInt() and 0xFF).coerceIn(1, 12)
            val day    = (data[5].toInt() and 0xFF).coerceIn(1, 31)
            val hour   = (data[7].toInt() and 0xFF).coerceIn(0, 23)
            val minute = (data[9].toInt() and 0xFF).coerceIn(0, 59)
            val second = (data[11].toInt() and 0xFF).coerceIn(0, 59)
            val buf = ByteBuffer.wrap(data, 12, 12).order(ByteOrder.BIG_ENDIAN)
            val eeaD    = buf.short.toInt() and 0xFFFF
            val rawDst  = buf.short.toInt() and 0xFFFF
            val rawTemp = buf.short.toInt()
            val step    = buf.short.toInt() and 0xFFFF
            val vca     = buf.short.toInt() and 0xFFFF
            val status  = buf.short.toInt() and 0xFFFF
            return try {
                TrendRecord(
                    dateTime = LocalDateTime.of(year, month, day, hour, minute, second),
                    eeaD = eeaD,
                    dst = rawDst.toDouble(),
                    temperature = rawTemp * 0.1,
                    step = step,
                    vca = vca,
                    status = status,
                )
            } catch (_: Exception) {
                null
            }
        }
    }
}
