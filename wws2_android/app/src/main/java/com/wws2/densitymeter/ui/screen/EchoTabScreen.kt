package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.verticalScroll
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ShowChart
import androidx.compose.material.icons.outlined.Edit
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.ui.text.TextRange
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.TextFieldValue
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
                InterfaceEchoInfoRow(ifReading, vm)
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
                    InterfaceEchoInfoRow(ifReading, vm)
                    Spacer(Modifier.height(4.dp))
                    InterfaceEchoChart(reading = ifReading, modifier = Modifier.fillMaxWidth().height(chartH))
                    Spacer(Modifier.height(8.dp))
                    InterfaceLevelCards(ifReading)
                }
            } else {
                // 세로: 기존 레이아웃
                EchoModeToggle(currentMode = state.echoMode, onModeChange = { vm.setEchoMode(it) })
                Spacer(Modifier.height(8.dp))
                InterfaceEchoInfoRow(ifReading, vm)
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
private fun InterfaceEchoInfoRow(ifReading: InterfaceEchoReading?, vm: MainViewModel) {
    var edit by remember { mutableStateOf<EchoEdit?>(null) }
    Row(
        modifier = Modifier.fillMaxWidth().padding(horizontal = 4.dp),
        horizontalArrangement = Arrangement.SpaceBetween,
        verticalAlignment = Alignment.CenterVertically,
    ) {
        EditableEchoInfo(
            text = "Thr.Light  ${ifReading?.let { if (it.thrLightMode == 1) "%.1fV".format(it.thrLightSet / 10.0) else "${it.thrLightSet}%" } ?: "--"}",
            color = AppColors.GrayLabel,
            textAlign = TextAlign.Start,
            modifier = Modifier.weight(1f),
            onClick = {
                if (ifReading != null) {
                    edit = if (ifReading.thrLightMode == 1) EchoEdit("Thr.Light Manual", 4, ifReading.thrLightSet, 0, 32, 1) { "%.1fV".format(it / 10.0) }
                    else EchoEdit("Thr.Light Auto", 2, ifReading.thrLightSet, 0, 95, 5) { "$it%" }
                }
            },
        )
        EditableEchoInfo(
            text = "Thr.Heavy  ${ifReading?.let { if (it.thrHeavyMode == 1) "%.1fV".format(it.thrHeavySet / 10.0) else "${it.thrHeavySet}%" } ?: "--"}",
            color = OrangeColor,
            textAlign = TextAlign.Center,
            modifier = Modifier.weight(1f),
            onClick = {
                if (ifReading != null) {
                    edit = if (ifReading.thrHeavyMode == 1) EchoEdit("Thr.Heavy Manual", 5, ifReading.thrHeavySet, 0, 32, 1) { "%.1fV".format(it / 10.0) }
                    else EchoEdit("Thr.Heavy Auto", 3, ifReading.thrHeavySet, 0, 95, 5) { "$it%" }
                }
            },
        )
        EditableEchoInfo(
            text = "Echo Amp  ${ifReading?.echoAmp?.toString() ?: "--"}",
            color = AppColors.Primary,
            textAlign = TextAlign.End,
            modifier = Modifier.weight(1f),
            onClick = {
                edit = EchoEdit("Echo Amp", 1, ifReading?.echoAmp ?: 15, 1, 50, 1) { it.toString() }
            },
        )
    }
    edit?.let { cfg ->
        EchoEditDialog(cfg, onDismiss = { edit = null }) { value ->
            vm.sendAppSetting(cfg.cmd, value)
            edit = null
        }
    }
}

@Composable
private fun EditableEchoInfo(
    text: String,
    color: androidx.compose.ui.graphics.Color,
    textAlign: TextAlign,
    modifier: Modifier = Modifier,
    onClick: () -> Unit,
) {
    Box(
        modifier = modifier.clickable(onClick = onClick),
        contentAlignment = when (textAlign) {
            TextAlign.Center -> Alignment.Center
            TextAlign.End -> Alignment.CenterEnd
            else -> Alignment.CenterStart
        },
    ) {
        Row(verticalAlignment = Alignment.CenterVertically) {
            Text(
                text,
                fontSize = 15.sp,
                fontWeight = FontWeight.W700,
                color = color,
                textAlign = textAlign,
            )
            Spacer(Modifier.width(3.dp))
            Icon(
                imageVector = Icons.Outlined.Edit,
                contentDescription = "Edit",
                modifier = Modifier.size(12.dp),
                tint = AppColors.WeakText,
            )
        }
    }
}

private data class EchoEdit(
    val title: String,
    val cmd: Int,
    val value: Int,
    val min: Int,
    val max: Int,
    val step: Int,
    val formatter: (Int) -> String,
)

@Composable
private fun EchoEditDialog(config: EchoEdit, onDismiss: () -> Unit, onApply: (Int) -> Unit) {
    var value by remember(config) { mutableIntStateOf(config.value.coerceIn(config.min, config.max)) }
    var text by remember(config) { mutableStateOf(TextFieldValue(config.value.coerceIn(config.min, config.max).toString(), selection = TextRange(config.value.coerceIn(config.min, config.max).toString().length))) }
    val parsed = text.text.toIntOrNull()
    val validValue = parsed?.takeIf { it in config.min..config.max }

    fun setValue(newValue: Int) {
        value = newValue.coerceIn(config.min, config.max)
        text = TextFieldValue(value.toString(), selection = TextRange(value.toString().length))
    }

    AlertDialog(
        onDismissRequest = onDismiss,
        title = { Text(config.title) },
        text = {
            Column(modifier = Modifier.fillMaxWidth(), horizontalAlignment = Alignment.CenterHorizontally) {
                Row(modifier = Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.SpaceBetween, verticalAlignment = Alignment.CenterVertically) {
                    Button(onClick = { setValue((validValue ?: value) - config.step) }) { Text("-") }
                    Text(config.formatter(validValue ?: value), fontSize = 24.sp, fontWeight = FontWeight.W700)
                    Button(onClick = { setValue((validValue ?: value) + config.step) }) { Text("+") }
                }
                Spacer(Modifier.height(10.dp))
                OutlinedTextField(
                    value = text,
                    onValueChange = { input ->
                        val filtered = input.text.filterIndexed { index, ch -> ch.isDigit() || (ch == '-' && index == 0 && config.min < 0) }
                        text = TextFieldValue(filtered, selection = TextRange(filtered.length))
                    },
                    modifier = Modifier.fillMaxWidth(),
                    singleLine = true,
                    keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                    label = { Text("Value") },
                    supportingText = { Text("Range ${config.min} ~ ${config.max} / ${validValue?.let(config.formatter) ?: "Invalid"}") },
                    colors = OutlinedTextFieldDefaults.colors(cursorColor = androidx.compose.ui.graphics.Color.Transparent),
                    isError = validValue == null,
                )
            }
        },
        confirmButton = { TextButton(enabled = validValue != null, onClick = { validValue?.let(onApply) }) { Text("Apply") } },
        dismissButton = { TextButton(onClick = onDismiss) { Text("Cancel") } },
    )
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
