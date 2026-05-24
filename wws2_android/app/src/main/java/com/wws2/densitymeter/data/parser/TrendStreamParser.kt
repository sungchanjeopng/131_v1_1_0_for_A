package com.wws2.densitymeter.data.parser

import android.util.Log
import com.wws2.densitymeter.ble.protocol.Crc
import com.wws2.densitymeter.ble.protocol.FrameCodec
import com.wws2.densitymeter.model.TrendRecord

private const val TAG = "TrendParser"
private const val REC_SIZE = 24

/**
 * Stateful trend stream parser.
 * Manages the header → chunks → CRC → end state machine.
 *
 * Callbacks decouple this parser from ViewModel state updates.
 * Corresponds to firmware's trd.c (trend ring-buffer engine).
 */
class TrendStreamParser(
    private val onRecordsParsed: (List<TrendRecord>) -> Unit,
    private val onHeaderParsed: (totalRecords: Int) -> Unit,
    private val onComplete: () -> Unit,
    private val onCrcFail: (reason: String) -> Boolean, // returns true if retry handled
    private val onError: (msg: String) -> Unit,
) {
    /** 0=idle, 1=waiting_header, 2=receiving_chunks */
    var streamState: Int = 0
        private set

    var totalRecords: Int = 0
        private set

    var retryCount: Int = 0
    var firstVisit: Boolean = true

    private var runningCrc: Int = 0xFFFF

    val isActive: Boolean get() = streamState > 0

    fun startStream() {
        streamState = 1
        totalRecords = 0
        runningCrc = 0xFFFF
        retryCount = 0
    }

    fun reset() {
        streamState = 0
        totalRecords = 0
        runningCrc = 0xFFFF
        firstVisit = true
        retryCount = 0
    }

    /**
     * Main parse entry point. Called whenever new bytes arrive in rxBuf.
     * @param downloadedCount number of records already parsed (from ViewModel state)
     */
    fun tryParse(rxBuf: MutableList<Byte>, downloadedCount: Int) {
        if (streamState == 1) {
            tryParseHeader(rxBuf)
        }
        if (streamState == 2) {
            parseChunks(rxBuf, downloadedCount)
        }
    }

    private fun tryParseHeader(rxBuf: MutableList<Byte>) {
        while (rxBuf.size >= 7) {
            val data = rxBuf.toByteArray()
            val sofIdx = FrameCodec.indexOfSubsequence(data, byteArrayOf(0x02))
            if (sofIdx < 0) { rxBuf.clear(); return }
            if (sofIdx > 0) { rxBuf.subList(0, sofIdx).clear() }
            if (rxBuf.size < 7) return

            // Trend header: [SOF][CMD_HI][CMD_LO][records_HI][records_LO][CRC_L][CRC_H]
            val cmd = ((rxBuf[1].toInt() and 0xFF) shl 8) or (rxBuf[2].toInt() and 0xFF)
            if (cmd != 0x0002 && cmd != 0x0012 && cmd != 0x0007 && cmd != 0x0017) {
                rxBuf.removeAt(0)
                continue
            }

            // CRC verify (SOF+CMD+DATA = 5B)
            val hdrBytes = ByteArray(5) { rxBuf[it] }
            val hdrCrcCalc = Crc.crc16Modbus(hdrBytes)
            val hdrCrcRecv = (rxBuf[5].toInt() and 0xFF) or ((rxBuf[6].toInt() and 0xFF) shl 8)
            if (hdrCrcCalc != hdrCrcRecv) {
                Log.w(TAG, "header CRC FAIL: calc=%04X recv=%04X".format(hdrCrcCalc, hdrCrcRecv))
                if (onCrcFail("header CRC FAIL")) {
                    return
                }
                onError("Header CRC error. Transfer failed.")
                return
            }

            totalRecords = ((rxBuf[3].toInt() and 0xFF) shl 8) or (rxBuf[4].toInt() and 0xFF)
            onHeaderParsed(totalRecords)
            rxBuf.subList(0, 7).clear()
            runningCrc = 0xFFFF
            streamState = 2
            break
        }
    }

    private fun parseChunks(rxBuf: MutableList<Byte>, downloadedCount: Int) {
        val newRecords = mutableListOf<TrendRecord>()

        while (downloadedCount + newRecords.size < totalRecords && rxBuf.size >= REC_SIZE) {
            val recBytes = ByteArray(REC_SIZE) { rxBuf[it] }
            rxBuf.subList(0, REC_SIZE).clear()

            // Update running CRC
            for (b in recBytes) {
                runningCrc = Crc.crc16Update(runningCrc, b)
            }

            val rec = TrendRecord.fromBytes(recBytes)
            if (rec != null) newRecords.add(rec)
        }

        if (newRecords.isNotEmpty()) {
            Log.d(TAG, "parsed ${downloadedCount + newRecords.size} / $totalRecords, rxBuf=${rxBuf.size}")
            onRecordsParsed(newRecords)
        }

        // All records received — verify final CRC
        if (downloadedCount + newRecords.size >= totalRecords) {
            if (rxBuf.size >= 2) {
                val crcReceived = (rxBuf[0].toInt() and 0xFF) or ((rxBuf[1].toInt() and 0xFF) shl 8)
                rxBuf.subList(0, 2).clear()
                if (crcReceived != runningCrc) {
                    Log.w(TAG, "CRC FAIL: received=%04X calc=%04X".format(crcReceived, runningCrc))
                    if (onCrcFail("final CRC FAIL")) {
                        return
                    }
                    onError("CRC verification failed. Data corrupted.")
                    return
                } else {
                    Log.d(TAG, "CRC OK: %04X".format(crcReceived))
                }
            }
            streamState = 0
            onComplete()
        }
    }
}
