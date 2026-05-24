package com.wws2.densitymeter.model

enum class TemperatureUnit(val unitStr: String) {
    CELSIUS("°C"),
    FAHRENHEIT("°F");

    fun convert(celsius: Double): Double = when (this) {
        CELSIUS    -> celsius
        FAHRENHEIT -> celsius * 9.0 / 5.0 + 32.0
    }

    fun format(celsius: Double): String {
        val v = convert(celsius)
        return "%.1f".format(v)
    }

    fun next(): TemperatureUnit = if (this == CELSIUS) FAHRENHEIT else CELSIUS

    companion object {
        fun fromInt(i: Int) = entries.getOrElse(i) { CELSIUS }
    }
}
