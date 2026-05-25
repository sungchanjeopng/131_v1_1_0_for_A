package com.wws2.densitymeter.data.parser

import com.wws2.densitymeter.ble.protocol.Crc
import com.wws2.densitymeter.model.*
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.time.LocalDateTime

/**
 * Stateless frame data parser.
 * Converts raw cmd+data bytes into domain model objects.
 *
 * Corresponds to firmware's msr_calc.c (signal processing output).
 * The ViewModel calls parse() and applies the result to state.
 */
object FrameParser {

    /** Sealed result type — each variant carries the parsed domain objects */
    sealed class ParseResult {
        /** Status 4B: minimal reading (distance + error code only) */
        data class Status4B(val reading: DeviceReading) : ParseResult()

        /** Status 34B: full density meter reading (relay + densUnit + per-channel Ext In) */
        data class DensityStatus(
            val reading: DeviceReading,
            val trendRecord: TrendRecord,
            val relay: Int,
            val densUnit: Int,
            val extIn1En: Int,
            val extIn1State: Int,
            val extIn2En: Int,
            val extIn2State: Int,
        ) : ParseResult()

        /** Status 26B: full interface meter reading */
        data class InterfaceStatus(
            val reading: DeviceReading,
            val temperature: Double,
            val currentMA: Double,
            val damping: Int,
            val set4mA: Double,
            val set20mA: Double,
            val freqMHz: Double,
            val tvg: Int,
            val offset: Double,
            val asf: Int,
            val relay: Int,
            val emptyDistance: Double = 0.0,
            val deadZone: Double = 0.0,
            val trendRecord: TrendRecord,
        ) : ParseResult()

        /** Echo 224B: density echo waveform + temperature */
        data class DensityEcho(
            val echo: EchoReading,
            val temperature: Double,
            val trendRecord: TrendRecord,
            val densUnit: Int,
        ) : ParseResult()

        /** Diag 16B: density diagnostics */
        data class DensityDiag(val diag: DiagReading) : ParseResult()

        /** Diag 22B: interface diagnostics */
        data class InterfaceDiag(val diag: InterfaceDiagReading) : ParseResult()
    }

    /** Expected data size for a given command. Returns -1 if variable/unknown. */
    fun expectedDataSize(cmd: Int, isInterface: Boolean): Int {
        return when (cmd) {
            0x0000, 0x0010 -> if (isInterface) 200 else 34
            0x0001 -> if (isInterface) -1 else 224
            0x0003 -> 30
            0x0004, 0x0014 -> if (isInterface) 22 else 16
            else -> -1
        }
    }

    /**
     * Parse a fully-extracted frame (cmd + data) into a domain result.
     * Returns null if the data doesn't match any known pattern.
     */
    fun parse(cmd: Int, data: ByteArray, isInterface: Boolean): ParseResult? {
        // Status: CMD=0x0000 / CMD=0x0010
        if (cmd == 0x0000 || cmd == 0x0010) {
            return parseStatus(data, isInterface)
        }

        // Density Echo: CMD=0x0001, 224B
        if (cmd == 0x0001 && data.size == 224) {
            return parseDensityEcho(data)
        }

        // Density Diag: CMD=0x0004, 16B
        if (cmd == 0x0004 && data.size == 16) {
            val diag = DiagReading.fromBytes(data) ?: return null
            return ParseResult.DensityDiag(diag)
        }

        // Interface Diag: CMD=0x0004/0x0014, 22B+
        if ((cmd == 0x0004 || cmd == 0x0014) && data.size >= 22) {
            val diag = InterfaceDiagReading.fromBytes(data) ?: return null
            return ParseResult.InterfaceDiag(diag)
        }

        return null
    }

    private fun parseStatus(data: ByteArray, isInterface: Boolean): ParseResult? {
        return when (data.size) {
            4 -> parseStatus4B(data)
            34 -> parseDensityStatus34B(data)
            26, 28, 30, 32, 200 -> parseInterfaceStatus26B(data)
            else -> null
        }
    }

    private fun parseStatus4B(data: ByteArray): ParseResult.Status4B {
        val dst = (((data[0].toInt() and 0xFF) shl 8) or (data[1].toInt() and 0xFF)) * 0.01
        val errorCode = ((data[2].toInt() and 0xFF) shl 8) or (data[3].toInt() and 0xFF)
        val reading = DeviceReading(
            level = dst,
            temperature = 0.0, currentMA = 0.0, damping = 0,
            set4mA = 0.0, set20mA = 0.0, pipeDia = 0, freqMHz = 0.0,
            errorCode = errorCode,
        )
        return ParseResult.Status4B(reading)
    }

    private fun parseDensityStatus34B(data: ByteArray): ParseResult.DensityStatus {
        val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)
        val dst = (buf.short.toInt() and 0xFFFF) * 0.01
        val eeaD = buf.short.toInt() and 0xFFFF
        val eeaR = buf.short.toInt() and 0xFFFF
        val temperature = buf.short.toInt() * 0.1
        val currentMA = (buf.short.toInt() and 0xFFFF) * 0.01
        val damping = buf.short.toInt() and 0xFFFF
        val set4mA = (buf.short.toInt() and 0xFFFF) * 0.01
        val set20mA = (buf.short.toInt() and 0xFFFF) * 0.01
        val pipeDia = buf.short.toInt() and 0xFFFF
        val freqMHz = (buf.short.toInt() and 0xFFFF) * 0.001
        val errorCode = buf.short.toInt() and 0xFFFF
        val relay = buf.short.toInt() and 0xFFFF
        val densUnit = buf.short.toInt() and 0xFFFF
        val extIn1En = buf.short.toInt() and 0xFFFF
        val extIn1State = buf.short.toInt() and 0xFFFF
        val extIn2En = buf.short.toInt() and 0xFFFF
        val extIn2State = buf.short.toInt() and 0xFFFF

        val reading = DeviceReading(
            level = dst, eeaR = eeaR, eeaD = eeaD, pipeDia = pipeDia, freqMHz = freqMHz,
            temperature = temperature, currentMA = currentMA, damping = damping,
            set4mA = set4mA, set20mA = set20mA, errorCode = errorCode,
        )
        val trendRecord = TrendRecord(
            dateTime = LocalDateTime.now(),
            eeaD = eeaD,
            dst = dst,
            temperature = temperature,
        )
        return ParseResult.DensityStatus(
            reading, trendRecord, relay, densUnit,
            extIn1En, extIn1State, extIn2En, extIn2State,
        )
    }

    private fun parseInterfaceStatus26B(data: ByteArray): ParseResult.InterfaceStatus {
        val buf = ByteBuffer.wrap(data).order(ByteOrder.BIG_ENDIAN)
        val light = (buf.short.toInt() and 0xFFFF) * 0.01
        val heavy = (buf.short.toInt() and 0xFFFF) * 0.01
        val temperature = buf.short.toInt() * 0.1
        val currentMA = (buf.short.toInt() and 0xFFFF) * 0.01
        // 계면계 FREQ: 인덱스 0/1/2/3 → 380/270/160/130 kHz
        val freqIdx = buf.short.toInt() and 0xFFFF
        val freq = when (freqIdx) { 0 -> 380; 1 -> 270; 2 -> 160; 3 -> 130; else -> 0 }
        val offset = buf.short.toInt()
        val set4mA = (buf.short.toInt() and 0xFFFF) * 0.01
        val set20mA = (buf.short.toInt() and 0xFFFF) * 0.01
        val tvg = buf.short.toInt() and 0xFFFF
        val damping = buf.short.toInt() and 0xFFFF
        val asf = buf.short.toInt() and 0xFFFF
        val relay = buf.short.toInt() and 0xFFFF
        val errorCode = buf.short.toInt() and 0xFFFF
        val echoAmpReserved = if (data.size >= 28) buf.short.toInt() and 0xFFFF else 0
        val emptyDistance = if (data.size >= 30) (buf.short.toInt() and 0xFFFF) * 0.01 else 0.0
        val deadZone = if (data.size >= 32) (buf.short.toInt() and 0xFFFF) * 0.01 else 0.0

        val reading = DeviceReading(
            level = light, heavyLevel = heavy,
            temperature = temperature, currentMA = currentMA,
            damping = damping, set4mA = set4mA, set20mA = set20mA,
            pipeDia = 0, freqMHz = freq * 0.001, errorCode = errorCode,
        )
        val trendRecord = TrendRecord(
            dateTime = LocalDateTime.now(),
            eeaD = (heavy / 0.01).toInt(),
            dst = light,
            temperature = temperature,
        )
        return ParseResult.InterfaceStatus(
            reading = reading,
            temperature = temperature, currentMA = currentMA, damping = damping,
            set4mA = set4mA, set20mA = set20mA, freqMHz = freq * 0.001,
            tvg = tvg, offset = offset * 0.01, asf = asf, relay = relay,
            emptyDistance = emptyDistance, deadZone = deadZone,
            trendRecord = trendRecord,
        )
    }

    private fun parseDensityEcho(data: ByteArray): ParseResult.DensityEcho? {
        // Layout: 14B header + 2B temp + 206B wave + 2B densUnit = 224B
        // Temperature is at offset 14-15 (after err, before wave)
        val echoData = data.copyOfRange(0, 14) + data.copyOfRange(16, 222)
        val echo = EchoReading.fromBytes(echoData) ?: return null
        val rawTemp = ((data[14].toInt() and 0xFF) shl 8) or (data[15].toInt() and 0xFF)
        val tempSigned = if (rawTemp > 32767) rawTemp - 65536 else rawTemp
        val temperature = tempSigned * 0.1
        val densUnit = ((data[222].toInt() and 0xFF) shl 8) or (data[223].toInt() and 0xFF)
        val trendRecord = TrendRecord(
            dateTime = LocalDateTime.now(),
            eeaD = echo.eeaD,
            dst = echo.level,
            temperature = temperature,
        )
        return ParseResult.DensityEcho(echo, temperature, trendRecord, densUnit)
    }
}
