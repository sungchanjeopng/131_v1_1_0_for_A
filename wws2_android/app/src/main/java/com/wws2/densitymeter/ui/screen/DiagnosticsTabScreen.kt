package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.outlined.HealthAndSafety
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.model.TemperatureUnit
import com.wws2.densitymeter.ui.component.DeviceStripBar
import com.wws2.densitymeter.ui.component.DiagRow
import com.wws2.densitymeter.ui.component.SettingsPanel
import com.wws2.densitymeter.ui.component.StatusInfoPanel
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.viewmodel.DeviceType
import com.wws2.densitymeter.viewmodel.MainViewModel
import kotlin.math.roundToInt

@Composable
fun DiagnosticsTabScreen(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()
    val devices = state.connectedDevices

    if (devices.isEmpty()) {
        EmptyTabState(
            icon = { Icon(Icons.Outlined.HealthAndSafety, contentDescription = null, modifier = Modifier.size(56.dp), tint = AppColors.WeakText) },
            title = "Parameter", desc = "", onOpenPairing = { vm.openPairing() },
        )
    } else {
        Column(
            modifier = Modifier
                .fillMaxSize()
                .verticalScroll(rememberScrollState())
                .padding(12.dp),
        ) {
            DeviceStripBar(devices = devices, selectedDeviceId = state.activeDeviceId,
                onDeviceTap = { vm.requestConnectDevice(it) }, onMoreTap = { vm.openPairing() })
            Spacer(Modifier.height(8.dp))

            if (state.deviceType == DeviceType.INTERFACE) {
                InterfaceParametersPanel(state)
                Spacer(Modifier.height(8.dp))
                InterfaceStatusPanel(state)
            } else {
                SettingsPanel(
                    deviceLabel = if (vm.isConnected) state.activeDeviceLabel else "--",
                    damping = state.damping, set4mA = state.set4mA, set20mA = state.set20mA,
                    pipeDia = state.pipeDia, freqMHz = state.freqMHz,
                    densUnit = state.densUnit,
                )
                Spacer(Modifier.height(8.dp))
                StatusInfoPanel(
                    currentMA = state.currentMA,
                    temperature = state.temperatureC,
                    tempUnit = state.tempUnit,
                    relay = state.relay,
                    extIn1En = state.extIn1En,
                    extIn1State = state.extIn1State,
                    extIn2En = state.extIn2En,
                    extIn2State = state.extIn2State,
                )
            }
        }
    }
}

@Composable
private fun InterfaceParametersPanel(state: com.wws2.densitymeter.viewmodel.MainUiState) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
    ) {
        Text("CONFIGURATION", modifier = Modifier.padding(start = 16.dp, top = 14.dp, bottom = 6.dp),
            fontSize = 18.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        DiagRow("Freq", "%d kHz".format((state.freqMHz * 1000).roundToInt()))
        DiagRow("Offset", "%.2f m".format(state.offset))
        DiagRow("4mA Set", "%.2f".format(state.set4mA))
        DiagRow("20mA Set", "%.2f".format(state.set20mA))
        DiagRow("TVG", state.tvg.toString())
        DiagRow("Damping", state.damping.toString())
    }
}

@Composable
private fun InterfaceStatusPanel(state: com.wws2.densitymeter.viewmodel.MainUiState) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
    ) {
        Text("Status", modifier = Modifier.padding(start = 16.dp, top = 14.dp, bottom = 6.dp),
            fontSize = 18.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        val tUnit = TemperatureUnit.fromInt(state.tempUnit)
        DiagRow("Temperature", "${tUnit.format(state.temperatureC)} ${tUnit.unitStr}")
        DiagRow("Current", "%.2f mA".format(state.currentMA))
        DiagRow("Relay", if (state.relay == 1) "Act" else "Stop")
    }
}
