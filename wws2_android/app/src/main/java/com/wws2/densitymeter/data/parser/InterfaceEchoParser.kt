package com.wws2.densitymeter.data.parser

import android.util.Log
import com.wws2.densitymeter.ble.protocol.Crc
import com.wws2.densitymeter.model.InterfaceEchoReading

private const val TAG = "IfEchoParser"

/**
 * Stateful parser for multi-chunk interface echo waveforms.
 * Encapsulates all ifEcho* state that was previously in MainViewModel.
 *
 * Usage:
 *   1. ViewModel detects interface echo header in rxBuf
 *   2. Calls beginCollection(headerPkt, cmd)
 *   3. Repeatedly calls tryParseChunks(rxBuf) until it returns non-null
 *   4. On tab switch or error, calls reset()
 */
class InterfaceEchoParser {

    /** 0=idle, 1=collecting_chunks */
    var state: Int = 0
        private set

    var cmd: Int = 0
        private set

    private var echoN: Int = 0
    private var fullChunks: Int = 0
    private var chunksDone: Int = 0
    var headerData: ByteArray = ByteArray(0)
        private set
    private val wave: MutableList<Int> = mutableListOf()
    private var runningCrc: Int = 0xFFFF

    val isCollecting: Boolean get() = state == 1

    /**
     * Initialize collection from the 33-byte header packet already extracted from rxBuf.
     * headerPkt includes SOF(1) + CMD(2) + headerData(30).
     */
    fun beginCollection(headerPkt: ByteArray, parsedCmd: Int) {
        // Extract 30B header data (skip SOF+CMD = 3 bytes)
        headerData = headerPkt.copyOfRange(3, 33)

        // N = empty * 1.1, capped at 1100 (ADC_BUFF_MAX)
        val emptyVal = ((headerData[6].toInt() and 0xFF) shl 8) or
                (headerData[7].toInt() and 0xFF)
        echoN = minOf((emptyVal * 1.1).toInt(), 1100)
        if (echoN == 0) echoN = 1

        fullChunks = echoN / 98
        chunksDone = 0
        wave.clear()
        cmd = parsedCmd

        // Initialize running CRC with the entire 33-byte header
        runningCrc = 0xFFFF
        for (i in 0 until 33) {
            runningCrc = Crc.crc16Update(runningCrc, headerPkt[i])
        }

        state = 1
    }

    /**
     * Attempt to parse chunks from rxBuf.
     * Returns non-null InterfaceEchoReading when all chunks + CRC are received.
     * Consumes bytes from rxBuf directly.
     */
    fun tryParseChunks(rxBuf: MutableList<Byte>): InterfaceEchoReading? {
        // Full chunks (98 samples = 196 bytes each)
        while (chunksDone < fullChunks) {
            if (rxBuf.size < 196) return null
            for (i in 0 until 196) {
                runningCrc = Crc.crc16Update(runningCrc, rxBuf[i])
            }
            for (j in 0 until 98) {
                val hi = rxBuf[j * 2].toInt() and 0xFF
                val lo = rxBuf[j * 2 + 1].toInt() and 0xFF
                wave.add((hi shl 8) or lo)
            }
            rxBuf.subList(0, 196).clear()
            chunksDone++
        }

        // Last partial chunk: lastSamples samples (2B each) + CRC (2B)
        val lastSamples = echoN % 98
        val lastSize = lastSamples * 2 + 2

        if (rxBuf.size < lastSize) return null

        // Parse last samples + update CRC
        for (j in 0 until lastSamples) {
            val b0 = rxBuf[j * 2]
            val b1 = rxBuf[j * 2 + 1]
            runningCrc = Crc.crc16Update(runningCrc, b0)
            runningCrc = Crc.crc16Update(runningCrc, b1)
            wave.add(((b0.toInt() and 0xFF) shl 8) or (b1.toInt() and 0xFF))
        }

        // Verify CRC
        val crcOff = lastSamples * 2
        val recvCrc = (rxBuf[crcOff].toInt() and 0xFF) or ((rxBuf[crcOff + 1].toInt() and 0xFF) shl 8)
        rxBuf.subList(0, lastSize).clear()
        state = 0

        if (runningCrc != recvCrc) {
            Log.w(TAG, "CRC FAIL: calc=%04X recv=%04X".format(runningCrc, recvCrc))
            return null
        }

        // Reconstruct: headerData(30B) + wave bytes → InterfaceEchoReading
        val waveBytes = ByteArray(wave.size * 2)
        for (i in wave.indices) {
            waveBytes[i * 2] = ((wave[i] shr 8) and 0xFF).toByte()
            waveBytes[i * 2 + 1] = (wave[i] and 0xFF).toByte()
        }
        val result = InterfaceEchoReading.fromBytes(headerData + waveBytes)
        Log.d(TAG, "OK cmd=0x%04X samples=%d".format(cmd, wave.size))
        return result
    }

    fun reset() {
        state = 0
        wave.clear()
        headerData = ByteArray(0)
    }
}
