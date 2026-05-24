package com.wws2.densitymeter.ui.theme

import android.content.res.Configuration
import androidx.compose.runtime.Composable
import androidx.compose.runtime.ReadOnlyComposable
import androidx.compose.ui.platform.LocalConfiguration

/** 가로 모드이거나 화면 너비 600dp 이상이면 true */
val isWideLayout: Boolean
    @Composable @ReadOnlyComposable
    get() {
        val config = LocalConfiguration.current
        return config.orientation == Configuration.ORIENTATION_LANDSCAPE ||
                config.screenWidthDp >= 600
    }

/** 태블릿 (최소 화면 너비 600dp 이상) */
val isTablet: Boolean
    @Composable @ReadOnlyComposable
    get() = LocalConfiguration.current.smallestScreenWidthDp >= 600
