package com.wws2.densitymeter.model

import java.nio.ByteBuffer
import java.nio.ByteOrder

/**
 * Interface meter (계면계) status reading - 26 bytes payload (LEN=0x1A)
 * Contains 2 channels (CH1/CH2), each with Light/Heavy thresholds
 */
data class InterfaceReading(
    val ch1Light: Double,      // x0.01m
    val ch1Heavy: Double,      // x0.01m
    val ch1Temperature: Double, // x0.1°C
    val ch1CurrentMA: Double,   // x0.01mA
    val ch2Light: Double,      // x0.01m
    val ch2Heavy: Double,      // x0.01m
    val ch2Temperature: Double, // x0.1°C
    val ch2CurrentMA: Double,   // x0.01mA
    val damping: Int,
    val set4mA: Double,        // x0.01m
    val set20mA: Double,       // x0.01m
    val emptyDist: Double,     // x0.01m
    val status: Int,
) {
    /** Convert CH1 data to a DeviceReading for unified display */
    fun toCh1Reading(): DeviceReading = DeviceReading(
        level = ch1Light,
        temperature = ch1Temperature,
        currentMA = ch1CurrentMA,
        damping = damping,
        set4mA = set4mA,
        set20mA = set20mA,
        pipeDia = 0,
        freqMHz = 0.0,
        heavyLevel = ch1Heavy,
    )

    /** Convert CH2 data to a DeviceReading for unified display */
    fun toCh2Reading(): DeviceReading = DeviceReading(
        level = ch2Light,
        temperature = ch2Temperature,
        currentMA = ch2CurrentMA,
        damping = damping,
        set4mA = set4mA,
        set20mA = set20mA,
        pipeDia = 0,
        freqMHz = 0.0,
        heavyLevel = ch2Heavy,
    )

    companion object {
        fun fromBytes(data: ByteArray): InterfaceReading? {
            if (data.size != 26) return null
            val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)
            val ch1Light = (buf.short.toInt() and 0xFFFF) * 0.01
            val ch1Heavy = (buf.short.toInt() and 0xFFFF) * 0.01
            val ch1Temp = buf.short.toInt() * 0.1
            val ch1Cur = (buf.short.toInt() and 0xFFFF) * 0.01
            val ch2Light = (buf.short.toInt() and 0xFFFF) * 0.01
            val ch2Heavy = (buf.short.toInt() and 0xFFFF) * 0.01
            val ch2Temp = buf.short.toInt() * 0.1
            val ch2Cur = (buf.short.toInt() and 0xFFFF) * 0.01
            val damping = buf.short.toInt() and 0xFFFF
            val set4mA = (buf.short.toInt() and 0xFFFF) * 0.01
            val set20mA = (buf.short.toInt() and 0xFFFF) * 0.01
            val emptyDist = (buf.short.toInt() and 0xFFFF) * 0.01
            val status = buf.short.toInt() and 0xFFFF
            return InterfaceReading(
                ch1Light, ch1Heavy, ch1Temp, ch1Cur,
                ch2Light, ch2Heavy, ch2Temp, ch2Cur,
                damping, set4mA, set20mA, emptyDist, status,
            )
        }
    }
}
