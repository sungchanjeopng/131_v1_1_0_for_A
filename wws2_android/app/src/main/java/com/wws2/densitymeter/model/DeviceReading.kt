package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder

data class DeviceReading(
    val level: Double,       // x0.01m (density: Level, interface: Light)
    val temperature: Double, // x0.1°C
    val currentMA: Double,   // x0.01mA
    val damping: Int,
    val set4mA: Double,      // x0.01m
    val set20mA: Double,     // x0.01m
    val pipeDia: Int,        // 0/1/2
    val freqMHz: Double,     // x0.001MHz
    val eeaR: Int = 0,              // Echo Amplitude (R)
    val eeaD: Int = 0,              // Echo Amplitude (D)
    val heavyLevel: Double? = null, // interface meter only: Heavy threshold x0.01m
    val errorCode: Int = 0,         // 0x00=정상, 0x01=ER01, 0x02=ER02
) {
    val pipeDiaLabel: String
        get() = when (pipeDia) {
            0 -> "0~200mm"
            1 -> "200~400mm"
            2 -> "400~600mm"
            else -> "--"
        }

    companion object {
        fun fromBytes(data: ByteArray): DeviceReading? {
            if (data.size != 16) return null
            val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)
            val rawLevel = buf.short.toInt() and 0xFFFF
            val rawTemp = buf.short.toInt()
            val rawCurrent = buf.short.toInt() and 0xFFFF
            val rawDamping = buf.short.toInt() and 0xFFFF
            val raw4mA = buf.short.toInt() and 0xFFFF
            val raw20mA = buf.short.toInt() and 0xFFFF
            val rawPipeDia = buf.short.toInt() and 0xFFFF
            val rawFreq = buf.short.toInt() and 0xFFFF
            return DeviceReading(
                level = rawLevel.toDouble(),
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
