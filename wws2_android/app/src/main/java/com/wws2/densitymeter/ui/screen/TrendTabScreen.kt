package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ErrorOutline
import androidx.compose.material.icons.filled.Insights
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.platform.LocalConfiguration
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.model.DensityUnit
import com.wws2.densitymeter.model.TrendRecord
import com.wws2.densitymeter.ui.component.DeviceStripBar
import com.wws2.densitymeter.ui.component.InterfaceTrendChart
import com.wws2.densitymeter.ui.component.StatRow
import com.wws2.densitymeter.ui.component.TrendChart
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.ui.theme.isTablet
import com.wws2.densitymeter.ui.theme.isWideLayout
import com.wws2.densitymeter.viewmodel.DeviceType
import com.wws2.densitymeter.viewmodel.MainViewModel

@Composable
fun TrendTabScreen(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()
    val devices = state.connectedDevices
    val isInterface = state.deviceType == DeviceType.INTERFACE

    // 계면계는 a01(_CH1)/a02(_CH2) 두 가상 디바이스를 쓰므로 activeDeviceId로 필터링
    // 농도계는 단일 디바이스라 필터링해도 동일 결과 (저장 시 deviceId=address)
    val records = state.trendRecords.filter { it.deviceId == state.activeDeviceId }

    val valueLabel = if (isInterface) "Light" else "Density"

    if (devices.isEmpty()) {
        EmptyTabState(
            icon = { Icon(Icons.Default.Insights, contentDescription = null, modifier = Modifier.size(56.dp), tint = AppColors.WeakText) },
            title = "Trend", desc = "", onOpenPairing = { vm.openPairing() }
        )
    } else {
        val wide = isWideLayout
        val tablet = isTablet
        Column(modifier = Modifier.fillMaxSize().padding(12.dp)) {
            DeviceStripBar(devices = devices, selectedDeviceId = state.activeDeviceId,
                onDeviceTap = { vm.requestConnectDevice(it) }, onMoreTap = { vm.openPairing() })
            Spacer(Modifier.height(8.dp))

            // 차트/로딩/에러 영역 + 통계 영역
            val chartContent: @Composable (Modifier) -> Unit = { mod ->
                if (state.trendError != null) {
                    Box(modifier = mod.fillMaxWidth(), contentAlignment = Alignment.Center) {
                        Column(horizontalAlignment = Alignment.CenterHorizontally, modifier = Modifier.padding(horizontal = 32.dp)) {
                            Icon(Icons.Default.ErrorOutline, contentDescription = null, modifier = Modifier.size(52.dp), tint = androidx.compose.ui.graphics.Color(0xFFE53935))
                            Spacer(Modifier.height(16.dp))
                            Text("Transfer Failed", fontSize = 20.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
                            Spacer(Modifier.height(8.dp))
                            Text(state.trendError ?: "", fontSize = 14.sp, color = AppColors.GrayLabel, textAlign = androidx.compose.ui.text.style.TextAlign.Center)
                        }
                    }
                } else if (state.isTrendStreaming) {
                    val total = state.trendExpectedRecords
                    val progress = if (total > 0) records.size.toFloat() / total else 0f
                    val percent = (progress * 100).toInt().coerceAtMost(100)
                    Box(modifier = mod.fillMaxWidth(), contentAlignment = Alignment.Center) {
                        Column(modifier = Modifier.fillMaxWidth().padding(horizontal = 32.dp), horizontalAlignment = Alignment.CenterHorizontally) {
                            Text("Loading trend data...", fontSize = 22.sp, fontWeight = FontWeight.W500, color = AppColors.GrayLabel)
                            Spacer(Modifier.height(24.dp))
                            LinearProgressIndicator(
                                progress = { progress.coerceIn(0f, 1f) },
                                modifier = Modifier.fillMaxWidth().height(12.dp).clip(RoundedCornerShape(6.dp)),
                                color = AppColors.Primary,
                                trackColor = AppColors.Primary.copy(alpha = 0.15f),
                            )
                            Spacer(Modifier.height(12.dp))
                            Text("$percent%  (${records.size} / $total)", fontSize = 16.sp, color = AppColors.Primary)
                        }
                    }
                } else {
                    if (isInterface) InterfaceTrendChart(records = records, tempUnit = state.tempUnit, modifier = mod)
                    else TrendChart(records = records, densUnit = state.densUnit, tempUnit = state.tempUnit, modifier = mod)
                }
            }

            val statsContent: @Composable () -> Unit = {
                if (isInterface) {
                    val lightStats = interfaceStats(records, isLight = true)
                    val heavyStats = interfaceStats(records, isLight = false)
                    InterfaceStatCard(lightStats, heavyStats)
                } else {
                    val dUnit = DensityUnit.fromInt(state.densUnit)
                    val stats = trendStats(records, dUnit)
                    StatRow(listOf(
                        Triple("$valueLabel Min", stats.first, AppColors.Primary),
                        Triple("$valueLabel Avg", stats.second, AppColors.DarkText),
                        Triple("$valueLabel Max", stats.third, AppColors.Temperature),
                    ))
                }
            }

            if (tablet) {
                // 태블릿: 차트 위 + 통계 아래, 스크롤 없이 한 화면
                chartContent(Modifier.weight(1f))
                Spacer(Modifier.height(8.dp))
                statsContent()
            } else if (wide) {
                // 폰 가로: 차트 크게 → 스크롤하면 통계
                val chartH = (LocalConfiguration.current.screenHeightDp * 0.65f).dp
                Column(modifier = Modifier.weight(1f).verticalScroll(rememberScrollState())) {
                    chartContent(Modifier.fillMaxWidth().height(chartH))
                    Spacer(Modifier.height(8.dp))
                    statsContent()
                }
            } else {
                chartContent(Modifier.weight(1f))
                Spacer(Modifier.height(8.dp))
                statsContent()
            }
        }
    }
}

private val OrangeColor = androidx.compose.ui.graphics.Color(0xFFFFA500)
private val GrayColor = androidx.compose.ui.graphics.Color(0xFF666666)

// 계면계: Light(dst*0.01) 또는 Heavy(eeaD*0.01) 통계
private fun interfaceStats(records: List<TrendRecord>, isLight: Boolean): Triple<String, String, String> {
    if (records.isEmpty()) return Triple("--", "--", "--")
    val values = if (isLight) records.map { it.dst * 0.01 } else records.map { it.eeaD * 0.01 }
    val min = values.min()
    val max = values.max()
    val avg = values.average()
    return Triple("%.2f".format(min), "%.2f".format(max), "%.2f".format(avg))
}

@Composable
internal fun InterfaceStatCard(
    lightStats: Triple<String, String, String>,
    heavyStats: Triple<String, String, String>,
) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
            .padding(vertical = 8.dp),
    ) {
        // Light row
        Row(modifier = Modifier.fillMaxWidth()) {
            StatCell("Light Level (Min)", lightStats.first, GrayColor, Modifier.weight(1f))
            StatCell("Light Level (Max)", lightStats.second, GrayColor, Modifier.weight(1f))
            StatCell("Light Level (Avg)", lightStats.third, GrayColor, Modifier.weight(1f))
        }
        // Divider
        Box(Modifier.fillMaxWidth().padding(horizontal = 12.dp).height(1.dp).background(AppColors.Background))
        // Heavy row
        Row(modifier = Modifier.fillMaxWidth()) {
            StatCell("Heavy Level (Min)", heavyStats.first, OrangeColor, Modifier.weight(1f))
            StatCell("Heavy Level (Max)", heavyStats.second, OrangeColor, Modifier.weight(1f))
            StatCell("Heavy Level (Avg)", heavyStats.third, OrangeColor, Modifier.weight(1f))
        }
    }
}

@Composable
private fun StatCell(label: String, value: String, color: androidx.compose.ui.graphics.Color, modifier: Modifier) {
    Column(
        modifier = modifier.padding(vertical = 8.dp, horizontal = 4.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Text(label, fontSize = 13.sp, fontWeight = FontWeight.W600, color = AppColors.GrayLabel, textAlign = androidx.compose.ui.text.style.TextAlign.Center)
        Spacer(Modifier.height(4.dp))
        Text(value, fontSize = 20.sp, fontWeight = FontWeight.W700, color = color, letterSpacing = (-0.5).sp)
    }
}

private fun trendStats(records: List<TrendRecord>, dUnit: DensityUnit = DensityUnit.PCT): Triple<String, String, String> {
    if (records.isEmpty()) return Triple("--", "--", "--")
    var min = records.first().dst
    var max = records.first().dst
    var sum = 0.0
    for (r in records) {
        if (r.dst < min) min = r.dst
        if (r.dst > max) max = r.dst
        sum += r.dst
    }
    val avg = sum / records.size
    return Triple(dUnit.format(min), dUnit.format(avg), dUnit.format(max))
}
