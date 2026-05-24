package com.wws2.densitymeter.ble.protocol

import android.util.Log
import java.nio.ByteBuffer
import java.nio.ByteOrder

private const val TAG = "FrameCodec"

/**
 * BLE protocol frame assembly and disassembly.
 * Stateless — all methods are pure functions.
 *
 * Frame format: [SOF:0x02] [CMD_HI] [CMD_LO] [DATA...] [CRC16_LO] [CRC16_HI]
 */
object FrameCodec {

    const val SOF: Byte = 0x02

    fun buildDeviceInfoRequest(pin: Int = 0): ByteArray {
        val payload = byteArrayOf(
            SOF,
            0x00,
            Command.CMD_DEVICE_INFO.toByte(),
            ((pin shr 8) and 0xFF).toByte(),
            (pin and 0xFF).toByte(),
        )
        val crc = Crc.crc16Modbus(payload)
        return payload + byteArrayOf((crc and 0xFF).toByte(), ((crc shr 8) and 0xFF).toByte())
    }

    fun parsePairingResponse(frame: ByteArray): PairingResult? {
        if (frame.size < 7) return null
        if (frame[0] != SOF) return null

        val cmd = ((frame[1].toInt() and 0xFF) shl 8) or (frame[2].toInt() and 0xFF)
        if (cmd != Command.CMD_DEVICE_INFO) return null

        val crcExpected = Crc.crc16Modbus(frame.copyOfRange(0, 5))
        val crcReceived = (frame[5].toInt() and 0xFF) or ((frame[6].toInt() and 0xFF) shl 8)
        if (crcExpected != crcReceived) return null

        val result = ((frame[3].toInt() and 0xFF) shl 8) or (frame[4].toInt() and 0xFF)
        return if (result == 0x0000) {
            Log.d(TAG, "Pairing PIN OK")
            PairingResult.Success(DeviceInfo('?', 0, fwVersion = FwVersion(0, 0, 0)))
        } else {
            Log.w(TAG, "Pairing PIN failed")
            PairingResult.PinFailed
        }
    }

    fun buildFrame(len: Int, data: ByteArray = ByteArray(0)): ByteArray {
        val sof = byteArrayOf(SOF)
        val lenBytes = byteArrayOf(((len shr 8) and 0xFF).toByte(), (len and 0xFF).toByte())
        val payload = sof + lenBytes + data
        val crc = Crc.crc16Modbus(payload)
        return payload + byteArrayOf((crc and 0xFF).toByte(), ((crc shr 8) and 0xFF).toByte())
    }

    fun buildHeartbeat(pageIndex: Int, expectedLen: Int = 0): ByteArray {
        val sof = byteArrayOf(SOF)
        val cmdBytes = byteArrayOf(((pageIndex shr 8) and 0xFF).toByte(), (pageIndex and 0xFF).toByte())
        val dataBytes = byteArrayOf(((expectedLen shr 8) and 0xFF).toByte(), (expectedLen and 0xFF).toByte())
        val payload = sof + cmdBytes + dataBytes
        val crc = Crc.crc16Modbus(payload)
        return payload + byteArrayOf((crc and 0xFF).toByte(), ((crc shr 8) and 0xFF).toByte())
    }

    fun parseFrame(raw: ByteArray): ParsedFrame? {
        if (raw.size < 5) return null
        if (raw[0] != SOF) return null

        val cmd = ((raw[1].toInt() and 0xFF) shl 8) or (raw[2].toInt() and 0xFF)
        val payloadEnd = raw.size - 2
        val crcReceived = (raw[payloadEnd].toInt() and 0xFF) or ((raw[payloadEnd + 1].toInt() and 0xFF) shl 8)
        val crcCalc = Crc.crc16Modbus(raw.copyOfRange(0, payloadEnd))
        if (crcReceived != crcCalc) return null
        val dataSize = raw.size - 5
        val data = if (dataSize > 0) raw.copyOfRange(3, payloadEnd) else ByteArray(0)
        return ParsedFrame(cmd, data)
    }

    fun makeStartFrame(): ByteArray = buildHeartbeat(Command.CMD_OTA_START)
    fun makeEndFrame(): ByteArray = buildHeartbeat(Command.CMD_OTA_END)

    fun u32le(v: Int): ByteArray {
        val buf = ByteBuffer.allocate(4).order(ByteOrder.LITTLE_ENDIAN)
        buf.putInt(v)
        return buf.array()
    }

    fun indexOfSubsequence(data: ByteArray, pattern: ByteArray): Int {
        if (pattern.isEmpty() || data.size < pattern.size) return -1
        outer@ for (i in 0..data.size - pattern.size) {
            for (j in pattern.indices) {
                if (data[i + j] != pattern[j]) continue@outer
            }
            return i
        }
        return -1
    }
}
