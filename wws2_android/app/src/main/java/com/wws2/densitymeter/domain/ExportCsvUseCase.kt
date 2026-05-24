package com.wws2.densitymeter.domain

import android.content.Context
import android.content.Intent
import android.os.Environment
import androidx.core.content.FileProvider
import com.wws2.densitymeter.model.TrendRecord
import java.io.File
import java.time.LocalDateTime
import java.time.format.DateTimeFormatter

class ExportCsvUseCase(private val context: Context) {

    fun buildCsvContent(records: List<TrendRecord>, isInterface: Boolean): String {
        val sb = StringBuilder()
        if (isInterface) {
            sb.appendLine("Time,Light,Heavy,Temp")
            for (r in records) {
                val dt = r.dateTime.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"))
                sb.appendLine("$dt,%.2f,%.2f,%.1f".format(r.dst, r.eeaD * 0.01, r.temperature))
            }
        } else {
            sb.appendLine("Time,EEA,Density,Temp,Step,VCA,Status")
            for (r in records) {
                val dt = r.dateTime.format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"))
                sb.appendLine("$dt,%d,%.2f,%.1f,%d,%.2f,%d".format(
                    r.eeaD, r.dst, r.temperature, r.step, r.vca * 0.01, r.status
                ))
            }
        }
        return sb.toString()
    }

    fun saveCsvToDocuments(fileName: String, records: List<TrendRecord>, isInterface: Boolean): String? {
        return try {
            val csv = buildCsvContent(records, isInterface)
            val docsDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS)
            val appDir = File(docsDir, "WESSWARE")
            appDir.mkdirs()
            val csvFile = File(appDir, fileName)
            csvFile.writeText(csv)
            csvFile.absolutePath
        } catch (e: Exception) {
            null
        }
    }

    fun createShareIntent(fileName: String, csvContent: String): Intent? {
        return try {
            val cacheDir = File(context.cacheDir, "csv_export")
            cacheDir.mkdirs()
            val csvFile = File(cacheDir, fileName)
            csvFile.writeText(csvContent)
            val uri = FileProvider.getUriForFile(context, "${context.packageName}.fileprovider", csvFile)
            Intent(Intent.ACTION_SEND).apply {
                type = "application/octet-stream"
                putExtra(Intent.EXTRA_STREAM, uri)
                putExtra(Intent.EXTRA_SUBJECT, fileName)
                addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION)
            }
        } catch (e: Exception) {
            null
        }
    }

    fun formatDateStamp(dt: LocalDateTime): String =
        dt.format(DateTimeFormatter.ofPattern("yyyyMMdd_HHmmss"))

    fun loadSavedFiles(): List<CsvFileInfo> {
        return try {
            val docsDir = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOCUMENTS)
            val appDir = File(docsDir, "WESSWARE")
            if (!appDir.exists()) return emptyList()
            appDir.listFiles { f -> f.extension.equals("csv", ignoreCase = true) }
                ?.sortedByDescending { it.lastModified() }
                ?.map { f ->
                    val lines = f.readLines()
                    val recordCount = (lines.size - 1).coerceAtLeast(0)
                    CsvFileInfo(
                        name = f.name,
                        recordCount = recordCount,
                        rangeLabel = if (lines.size >= 3) {
                            val first = lines[1].split(",").firstOrNull() ?: "--"
                            val last = lines.last().split(",").firstOrNull() ?: "--"
                            "$first ~ $last"
                        } else "--",
                        sizeBytes = f.length().toInt(),
                        targetDevice = f.nameWithoutExtension.substringBefore("_20"),
                    )
                } ?: emptyList()
        } catch (e: Exception) {
            emptyList()
        }
    }
}

data class CsvFileInfo(
    val name: String,
    val recordCount: Int,
    val rangeLabel: String,
    val sizeBytes: Int,
    val targetDevice: String,
)
