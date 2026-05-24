package com.wws2.densitymeter.model

import kotlin.math.roundToLong

enum class DensityUnit(val label: String, val unitStr: String) {
    PCT("%", "%"),
    G_L("g/L", "g/L"),
    PPM("ppm", "ppm"),
    MG_L("mg/L", "mg/L"),
    KG_M3("kg/m³", "kg/m³"),
    G_CM3("g/cm³", "g/cm³");

    /** raw = 펌웨어 density U16 (0.01% 단위) */
    fun convert(raw: Double): Double = when (this) {
        PCT   -> raw / 100.0
        G_L   -> raw / 10.0
        PPM   -> raw * 100.0
        MG_L  -> raw * 100.0
        KG_M3 -> raw
        G_CM3 -> raw / 1000.0
    }

    fun format(raw: Double): String = formatValue(convert(raw))

    /** Format a value already in this unit (not raw) */
    fun formatValue(v: Double): String = when (this) {
        PCT   -> "%.2f".format(v)
        G_L   -> "%.1f".format(v)
        PPM   -> "%d".format(v.roundToLong())
        MG_L  -> "%d".format(v.roundToLong())
        KG_M3 -> "%d".format(v.roundToLong())
        G_CM3 -> "%.3f".format(v)
    }

    fun next(): DensityUnit {
        val vals = entries
        return vals[(ordinal + 1) % vals.size]
    }

    companion object {
        fun fromInt(i: Int) = entries.getOrElse(i) { PCT }
    }
}
