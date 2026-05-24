package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.verticalScroll
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ShowChart
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.platform.LocalConfiguration
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.compose.foundation.border
import com.wws2.densitymeter.model.InterfaceEchoReading
import com.wws2.densitymeter.ui.component.DeviceStripBar
import com.wws2.densitymeter.ui.component.EchoChart
import com.wws2.densitymeter.ui.component.InterfaceEchoChart
import com.wws2.densitymeter.ui.component.StatRow
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.ui.theme.isTablet
import com.wws2.densitymeter.ui.theme.isWideLayout
import com.wws2.densitymeter.viewmodel.DeviceType
import com.wws2.densitymeter.viewmodel.EchoMode
import com.wws2.densitymeter.model.DensityUnit
import com.wws2.densitymeter.viewmodel.MainViewModel

private val OrangeColor = androidx.compose.ui.graphics.Color(0xFFFFA500)

@Composable
fun EchoTabScreen(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()
    val densUnit = DensityUnit.fromInt(state.densUnit)
    val devices = state.connectedDevices
    val isInterface = state.deviceType == DeviceType.INTERFACE

    if (devices.isEmpty()) {
        EmptyTabState(
            icon = { Icon(Icons.AutoMirrored.Filled.ShowChart, contentDescription = null, modifier = Modifier.size(56.dp), tint = AppColors.WeakText) },
            title = "Echo", desc = "", onOpenPairing = { vm.openPairing() }
        )
    } else if (isInterface) {
        // ─── 계면계 Echo 화면 ───
        val ifReading = state.interfaceEchoReading
        val wide = isWideLayout
        val tablet = isTablet
        Column(modifier = Modifier.fillMaxSize().padding(12.dp)) {
            DeviceStripBar(devices = devices, selectedDeviceId = state.activeDeviceId,
                onDeviceTap = { vm.requestConnectDevice(it) }, onMoreTap = { vm.openPairing() })
            Spacer(Modifier.height(8.dp))

            if (tablet) {
                // 태블릿: 차트 위 + 컨트롤/카드 아래, 스크롤 없이 한 화면
                EchoModeToggle(currentMode = state.echoMode, onModeChange = { vm.setEchoMode(it) })
                Spacer(Modifier.height(8.dp))
                Row(modifier = Modifier.fillMaxWidth().padding(horizontal = 4.dp), horizontalArrangement = Arrangement.SpaceAround) {
                    Text("Thr.Light  ${ifReading?.thrLightSet?.let { "${it}%" } ?: "--"}", fontSize = 16.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
                    Text("Thr.Heavy  ${ifReading?.thrHeavySet?.let { "${it}%" } ?: "--"}", fontSize = 16.sp, fontWeight = FontWeight.W700, color = OrangeColor)
                }
                Spacer(Modifier.height(4.dp))
                InterfaceEchoChart(reading = ifReading, modifier = Modifier.weight(1f))
                Spacer(Modifier.height(8.dp))
                InterfaceLevelCards(ifReading)
            } else if (wide) {
                // 폰 가로: 차트 크게 → 스크롤하면 정보
                val chartH = (LocalConfiguration.current.screenHeightDp * 0.65f).dp
                Column(modifier = Modifier.weight(1f).verticalScroll(rememberScrollState())) {
                    EchoModeToggle(currentMode = state.echoMode, onModeChange = { vm.setEchoMode(it) })
                    Spacer(Modifier.height(8.dp))
                    Row(modifier = Modifier.fillMaxWidth().padding(horizontal = 4.dp), horizontalArrangement = Arrangement.SpaceAround) {
                        Text("Thr.Light  ${ifReading?.thrLightSet?.let { "${it}%" } ?: "--"}", fontSize = 16.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
                        Text("Thr.Heavy  ${ifReading?.thrHeavySet?.let { "${it}%" } ?: "--"}", fontSize = 16.sp, fontWeight = FontWeight.W700, color = OrangeColor)
                    }
                    Spacer(Modifier.height(4.dp))
                    InterfaceEchoChart(reading = ifReading, modifier = Modifier.fillMaxWidth().height(chartH))
                    Spacer(Modifier.height(8.dp))
                    InterfaceLevelCards(ifReading)
                }
            } else {
                // 세로: 기존 레이아웃
                EchoModeToggle(currentMode = state.echoMode, onModeChange = { vm.setEchoMode(it) })
                Spacer(Modifier.height(8.dp))
                Row(modifier = Modifier.fillMaxWidth().padding(horizontal = 4.dp), horizontalArrangement = Arrangement.SpaceAround) {
                    Text("Thr.Light  ${ifReading?.thrLightSet?.let { "${it}%" } ?: "--"}", fontSize = 16.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
                    Text("Thr.Heavy  ${ifReading?.thrHeavySet?.let { "${it}%" } ?: "--"}", fontSize = 16.sp, fontWeight = FontWeight.W700, color = OrangeColor)
                }
                Spacer(Modifier.height(4.dp))
                InterfaceEchoChart(reading = ifReading, modifier = Modifier.weight(1f))
                Spacer(Modifier.height(8.dp))
                InterfaceLevelCards(ifReading)
            }
        }
    } else {
        // ─── 농도계 Echo 화면 ───
        val reading = state.echoReading
        val wide = isWideLayout
        val tablet = isTablet
        Column(modifier = Modifier.fillMaxSize().padding(12.dp)) {
            DeviceStripBar(devices = devices, selectedDeviceId = state.activeDeviceId,
                onDeviceTap = { vm.requestConnectDevice(it) }, onMoreTap = { vm.openPairing() })
            Spacer(Modifier.height(8.dp))

            if (tablet) {
                EchoChart(echoReading = reading, isInterface = false, modifier = Modifier.weight(1f))
                Spacer(Modifier.height(8.dp))
                StatRow(listOf(
                    Triple("EEA.R", reading?.eeaR?.toString() ?: "--", AppColors.Primary),
                    Triple("EEA.D", reading?.eeaD?.toString() ?: "--", AppColors.DarkText),
                    Triple("Density(${densUnit.unitStr})", reading?.let { densUnit.format(it.level) } ?: "--", AppColors.Primary),
                ))
            } else if (wide) {
                val chartH = (LocalConfiguration.current.screenHeightDp * 0.65f).dp
                Column(modifier = Modifier.weight(1f).verticalScroll(rememberScrollState())) {
                    EchoChart(echoReading = reading, isInterface = false, modifier = Modifier.fillMaxWidth().height(chartH))
                    Spacer(Modifier.height(8.dp))
                    StatRow(listOf(
                        Triple("EEA.R", reading?.eeaR?.toString() ?: "--", AppColors.Primary),
                        Triple("EEA.D", reading?.eeaD?.toString() ?: "--", AppColors.DarkText),
                        Triple("Density(${densUnit.unitStr})", reading?.let { densUnit.format(it.level) } ?: "--", AppColors.Primary),
                    ))
                }
            } else {
                EchoChart(echoReading = reading, isInterface = false, modifier = Modifier.weight(1f))
                Spacer(Modifier.height(8.dp))
                StatRow(listOf(
                    Triple("EEA.R", reading?.eeaR?.toString() ?: "--", AppColors.Primary),
                    Triple("EEA.D", reading?.eeaD?.toString() ?: "--", AppColors.DarkText),
                    Triple("Density(${densUnit.unitStr})", reading?.let { densUnit.format(it.level) } ?: "--", AppColors.Primary),
                ))
            }
        }
    }
}

@Composable
private fun EchoModeToggle(currentMode: EchoMode, onModeChange: (EchoMode) -> Unit) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(2.dp, RoundedCornerShape(12.dp))
            .background(AppColors.White, RoundedCornerShape(12.dp))
            .padding(4.dp),
    ) {
        val modes = listOf(EchoMode.REAL to "Real", EchoMode.AVG to "Avg")
        modes.forEach { (mode, label) ->
            val isSelected = currentMode == mode
            Box(
                modifier = Modifier
                    .weight(1f)
                    .clip(RoundedCornerShape(10.dp))
                    .background(if (isSelected) AppColors.Primary else AppColors.White)
                    .clickable { onModeChange(mode) }
                    .padding(vertical = 10.dp),
                contentAlignment = Alignment.Center,
            ) {
                Text(
                    label,
                    fontSize = 16.sp,
                    fontWeight = FontWeight.W700,
                    color = if (isSelected) AppColors.White else AppColors.GrayLabel,
                )
            }
        }
    }
}

@Composable
private fun InterfaceLevelCards(ifReading: InterfaceEchoReading?) {
    Row(modifier = Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.spacedBy(6.dp)) {
        Column(
            modifier = Modifier.weight(1f)
                .shadow(2.dp, RoundedCornerShape(12.dp))
                .background(AppColors.White, RoundedCornerShape(12.dp))
                .padding(10.dp),
            horizontalAlignment = Alignment.CenterHorizontally,
        ) {
            Text("Light Level", fontSize = 14.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
            Spacer(Modifier.height(2.dp))
            Text(ifReading?.let { "%.2f m".format(it.lightLevel) } ?: "--", fontSize = 22.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        }
        Column(
            modifier = Modifier.weight(1f)
                .shadow(2.dp, RoundedCornerShape(12.dp))
                .background(AppColors.White, RoundedCornerShape(12.dp))
                .padding(10.dp),
            horizontalAlignment = Alignment.CenterHorizontally,
        ) {
            Text("Heavy Level", fontSize = 14.sp, fontWeight = FontWeight.W700, color = OrangeColor)
            Spacer(Modifier.height(2.dp))
            Text(ifReading?.let { "%.2f m".format(it.heavyLevel) } ?: "--", fontSize = 22.sp, fontWeight = FontWeight.W700, color = OrangeColor)
        }
    }
}

@Composable
fun EmptyTabState(icon: @Composable () -> Unit, title: String, desc: String, onOpenPairing: (() -> Unit)? = null) {
    // 페어링 미연결 상태: "No device connected" + Open Pairing 버튼
    Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
        if (onOpenPairing != null) {
            Column(
                modifier = Modifier.fillMaxWidth().padding(horizontal = 28.dp),
                horizontalAlignment = Alignment.CenterHorizontally,
            ) {
                Text(
                    "No device connected",
                    fontSize = 16.sp,
                    fontWeight = FontWeight.W600,
                    color = AppColors.GrayLabel,
                )
                Spacer(Modifier.height(14.dp))
                androidx.compose.material3.Button(
                    onClick = onOpenPairing,
                    modifier = Modifier.fillMaxWidth(),
                    colors = androidx.compose.material3.ButtonDefaults.buttonColors(containerColor = AppColors.Primary),
                    shape = RoundedCornerShape(14.dp),
                    contentPadding = androidx.compose.foundation.layout.PaddingValues(vertical = 16.dp),
                ) {
                    Text("Open Pairing", fontSize = 18.sp, fontWeight = FontWeight.W700)
                }
            }
        }
    }
}
