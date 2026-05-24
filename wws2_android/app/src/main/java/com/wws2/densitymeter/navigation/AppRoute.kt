package com.wws2.densitymeter.navigation

/**
 * Type-safe navigation routes replacing string-based subPage/tabIndex navigation.
 */
sealed class AppRoute {

    // ── Bottom tabs ──
    data object MainTab : AppRoute()
    data object EchoTab : AppRoute()
    data object TrendTab : AppRoute()
    data object DiagnosticsTab : AppRoute()
    data object MenuTab : AppRoute()

    // ── Sub-pages (accessed from Menu tab) ──
    data object Pairing : AppRoute()
    data object DataDownload : AppRoute()
    data object FirmwareUpload : AppRoute()
    data object Chatbot : AppRoute()
}

// ── Extension properties ──

/**
 * The bottom-navigation tab index for this route.
 * All sub-pages belong to the Menu tab (index 4).
 */
val AppRoute.tabIndex: Int
    get() = when (this) {
        AppRoute.MainTab -> 0
        AppRoute.EchoTab -> 1
        AppRoute.TrendTab -> 2
        AppRoute.DiagnosticsTab -> 3
        AppRoute.MenuTab -> 4
        AppRoute.Pairing -> 4
        AppRoute.DataDownload -> 4
        AppRoute.FirmwareUpload -> 4
        AppRoute.Chatbot -> 4
    }

/**
 * Whether this route is a sub-page (pushed on top of the Menu tab)
 * rather than a top-level bottom tab.
 */
val AppRoute.isSubPage: Boolean
    get() = when (this) {
        AppRoute.Pairing,
        AppRoute.DataDownload,
        AppRoute.FirmwareUpload,
        AppRoute.Chatbot -> true
        else -> false
    }

/**
 * Human-readable screen title for the top/app bar.
 */
val AppRoute.title: String
    get() = when (this) {
        AppRoute.MainTab -> "Main"
        AppRoute.EchoTab -> "Echo"
        AppRoute.TrendTab -> "Trend"
        AppRoute.DiagnosticsTab -> "Parameter"
        AppRoute.MenuTab -> "Menu"
        AppRoute.Pairing -> "BLE Pairing"
        AppRoute.DataDownload -> "Data Files"
        AppRoute.FirmwareUpload -> "Firmware Update"
        AppRoute.Chatbot -> "AI Chatbot"
    }

// ── Helper function ──

/**
 * Maps a bottom-navigation tab index (0-4) to its corresponding [AppRoute].
 *
 * @throws IllegalArgumentException if [index] is not in 0..4.
 */
fun tabIndexToRoute(index: Int): AppRoute = when (index) {
    0 -> AppRoute.MainTab
    1 -> AppRoute.EchoTab
    2 -> AppRoute.TrendTab
    3 -> AppRoute.DiagnosticsTab
    4 -> AppRoute.MenuTab
    else -> throw IllegalArgumentException("Invalid tab index: $index (expected 0..4)")
}
