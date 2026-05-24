package com.wws2.densitymeter.ui.theme

import androidx.compose.material3.*
import androidx.compose.runtime.Composable
import androidx.compose.runtime.CompositionLocalProvider
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.unit.Density

private val LightColorScheme = lightColorScheme(
    primary = AppColors.Primary,
    onPrimary = AppColors.White,
    surface = AppColors.Background,
    onSurface = AppColors.DarkText,
    background = AppColors.Background,
    onBackground = AppColors.DarkText,
    error = AppColors.Error,
    outline = AppColors.Border,
)

@Composable
fun DensityMeterTheme(content: @Composable () -> Unit) {
    val current = LocalDensity.current
    val fixedDensity = Density(density = current.density, fontScale = 0.85f)
    MaterialTheme(
        colorScheme = LightColorScheme,
        typography = Typography(),
    ) {
        CompositionLocalProvider(LocalDensity provides fixedDensity) {
            content()
        }
    }
}
