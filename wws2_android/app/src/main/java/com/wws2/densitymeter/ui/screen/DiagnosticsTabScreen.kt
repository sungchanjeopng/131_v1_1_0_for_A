package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.outlined.Edit
import androidx.compose.material.icons.outlined.HealthAndSafety
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.foundation.text.KeyboardOptions
import androidx.compose.ui.text.TextRange
import androidx.compose.ui.text.input.KeyboardType
import androidx.compose.ui.text.input.TextFieldValue
import androidx.compose.ui.text.style.TextAlign
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
import com.wws2.densitymeter.viewmodel.MainUiState
import com.wws2.densitymeter.viewmodel.MainViewModel
import kotlin.math.roundToInt

private data class ConfigEdit(
    val title: String,
    val cmd: Int,
    val value: Int,
    val min: Int,
    val max: Int,
    val step: Int,
    val allowTextInput: Boolean = true,
    val decimalScale: Int = 1,
    val formatter: (Int) -> String,
)

@Composable
fun DiagnosticsTabScreen(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()
    val devices = state.connectedDevices
    var edit by remember { mutableStateOf<ConfigEdit?>(null) }

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
                InterfaceParametersPanel(state, onEdit = { edit = it })
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

    edit?.let { cfg ->
        ConfigEditDialog(
            config = cfg,
            onDismiss = { edit = null },
            onApply = { value ->
                vm.sendAppSetting(cfg.cmd, value)
                edit = null
            },
        )
    }
}

@Composable
private fun InterfaceParametersPanel(state: MainUiState, onEdit: (ConfigEdit) -> Unit) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
    ) {
        Text("CONFIGURATION", modifier = Modifier.padding(start = 16.dp, top = 14.dp, bottom = 6.dp),
            fontSize = 18.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        EditableDiagRow("Freq", "%d kHz".format((state.freqMHz * 1000).roundToInt())) {
            val current = when ((state.freqMHz * 1000).roundToInt()) { 380 -> 0; 270 -> 1; 160 -> 2; 130 -> 3; else -> 0 }
            onEdit(ConfigEdit("Frequency", 6, current, 0, 3, 1, allowTextInput = false) { v -> when (v) { 0 -> "380 kHz"; 1 -> "270 kHz"; 2 -> "160 kHz"; 3 -> "130 kHz"; else -> "--" } })
        }
        EditableDiagRow("Offset", "%.2f m".format(state.offset)) {
            onEdit(ConfigEdit("Offset", 7, (state.offset * 100).roundToInt(), -100, 100, 1, decimalScale = 100) { v -> "%.2f m".format(v / 100.0) })
        }
        EditableDiagRow("Empty", "%.2f m".format(state.emptyDistance)) {
            onEdit(ConfigEdit("Empty", 12, (state.emptyDistance * 100).roundToInt(), 1, 1000, 1, decimalScale = 100) { v -> "%.2f m".format(v / 100.0) })
        }
        EditableDiagRow("Dead Zone", "%.2f m".format(state.deadZone)) {
            onEdit(ConfigEdit("Dead Zone", 13, (state.deadZone * 100).roundToInt(), 35, 1000, 1, decimalScale = 100) { v -> "%.2f m".format(v / 100.0) })
        }
        EditableDiagRow("4mA Set", "%.2f".format(state.set4mA)) {
            onEdit(ConfigEdit("4mA Set", 8, (state.set4mA * 100).roundToInt(), 0, 1000, 1, decimalScale = 100) { v -> "%.2f".format(v / 100.0) })
        }
        EditableDiagRow("20mA Set", "%.2f".format(state.set20mA)) {
            onEdit(ConfigEdit("20mA Set", 9, (state.set20mA * 100).roundToInt(), 0, 1000, 1, decimalScale = 100) { v -> "%.2f".format(v / 100.0) })
        }
        EditableDiagRow("TVG", state.tvg.toString()) {
            onEdit(ConfigEdit("TVG", 10, state.tvg, 0, 7, 1, allowTextInput = false) { it.toString() })
        }
        EditableDiagRow("Damping", state.damping.toString()) {
            onEdit(ConfigEdit("Damping", 11, state.damping, 1, 100, 1) { it.toString() })
        }
    }
}

@Composable
private fun EditableDiagRow(label: String, value: String, onClick: () -> Unit) {
    Row(
        modifier = Modifier.fillMaxWidth().clickable(onClick = onClick).padding(horizontal = 16.dp, vertical = 12.dp),
        horizontalArrangement = Arrangement.SpaceBetween,
        verticalAlignment = Alignment.CenterVertically,
    ) {
        Text(label, fontSize = 19.sp, color = AppColors.GrayLabel)
        Row(verticalAlignment = Alignment.CenterVertically) {
            Text(value, fontSize = 20.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText)
            Spacer(Modifier.width(6.dp))
            Icon(
                imageVector = Icons.Outlined.Edit,
                contentDescription = "Edit",
                modifier = Modifier.size(15.dp),
                tint = AppColors.WeakText,
            )
        }
    }
}

@Composable
private fun ConfigEditDialog(config: ConfigEdit, onDismiss: () -> Unit, onApply: (Int) -> Unit) {
    fun integerText(raw: Int): String {
        if (config.decimalScale <= 1) return raw.toString()
        val absRaw = kotlin.math.abs(raw)
        val sign = if (raw < 0) "-" else ""
        return sign + (absRaw / config.decimalScale).toString()
    }
    fun fractionText(raw: Int): String {
        val absRaw = kotlin.math.abs(raw)
        return (absRaw % config.decimalScale).toString().padStart(2, '0')
    }
    fun parseRaw(intInput: String, fracInput: String): Int? {
        if (config.decimalScale <= 1) return intInput.toIntOrNull()
        val intPart = intInput.toIntOrNull() ?: return null
        val fracPart = fracInput.toIntOrNull() ?: return null
        if (fracPart !in 0 until config.decimalScale) return null
        val negative = intInput.trim().startsWith("-")
        val rawAbs = kotlin.math.abs(intPart) * config.decimalScale + fracPart
        return if (negative) -rawAbs else rawAbs
    }

    var value by remember(config) { mutableIntStateOf(config.value.coerceIn(config.min, config.max)) }
    var intText by remember(config) { mutableStateOf(TextFieldValue(integerText(config.value.coerceIn(config.min, config.max)), selection = TextRange(integerText(config.value.coerceIn(config.min, config.max)).length))) }
    var fracText by remember(config) { mutableStateOf(TextFieldValue(fractionText(config.value.coerceIn(config.min, config.max)), selection = TextRange(fractionText(config.value.coerceIn(config.min, config.max)).length))) }
    val parsed = if (config.allowTextInput) parseRaw(intText.text, fracText.text) else value
    val validValue = parsed?.takeIf { it in config.min..config.max }

    fun setValue(newValue: Int) {
        value = newValue.coerceIn(config.min, config.max)
        intText = TextFieldValue(integerText(value), selection = TextRange(integerText(value).length))
        fracText = TextFieldValue(fractionText(value), selection = TextRange(fractionText(value).length))
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
                if (config.allowTextInput) {
                    Spacer(Modifier.height(10.dp))
                    if (config.decimalScale > 1) {
                        Row(
                            modifier = Modifier.fillMaxWidth(),
                            horizontalArrangement = Arrangement.Center,
                            verticalAlignment = Alignment.Bottom,
                        ) {
                            OutlinedTextField(
                                value = intText,
                                onValueChange = { input ->
                                    val filtered = input.text.filterIndexed { index, ch -> ch.isDigit() || (ch == '-' && index == 0 && config.min < 0) }
                                    intText = TextFieldValue(filtered, selection = TextRange(filtered.length))
                                },
                                modifier = Modifier.width(92.dp),
                                singleLine = true,
                                keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                                textStyle = LocalTextStyle.current.copy(textAlign = TextAlign.End, fontSize = 20.sp),
                                colors = OutlinedTextFieldDefaults.colors(cursorColor = androidx.compose.ui.graphics.Color.Transparent),
                                isError = validValue == null,
                            )
                            Text(
                                ".",
                                modifier = Modifier.padding(start = 6.dp, end = 6.dp, bottom = 8.dp),
                                fontSize = 24.sp,
                                fontWeight = FontWeight.W700,
                            )
                            OutlinedTextField(
                                value = fracText,
                                onValueChange = { input ->
                                    val filtered = input.text.filter { it.isDigit() }.take(2)
                                    fracText = TextFieldValue(filtered, selection = TextRange(filtered.length))
                                },
                                modifier = Modifier.width(76.dp),
                                singleLine = true,
                                keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                                textStyle = LocalTextStyle.current.copy(textAlign = TextAlign.Start, fontSize = 20.sp),
                                colors = OutlinedTextFieldDefaults.colors(cursorColor = androidx.compose.ui.graphics.Color.Transparent),
                                isError = validValue == null,
                            )
                        }
                        Text("Range ${config.formatter(config.min)} ~ ${config.formatter(config.max)}", fontSize = 12.sp, color = AppColors.GrayLabel)
                    } else {
                        OutlinedTextField(
                            value = intText,
                            onValueChange = { input ->
                                val filtered = input.text.filterIndexed { index, ch -> ch.isDigit() || (ch == '-' && index == 0 && config.min < 0) }
                                intText = TextFieldValue(filtered, selection = TextRange(filtered.length))
                            },
                            modifier = Modifier.fillMaxWidth(),
                            singleLine = true,
                            keyboardOptions = KeyboardOptions(keyboardType = KeyboardType.Number),
                            label = { Text("Value") },
                            supportingText = { Text("Range ${config.formatter(config.min)} ~ ${config.formatter(config.max)}") },
                            colors = OutlinedTextFieldDefaults.colors(cursorColor = androidx.compose.ui.graphics.Color.Transparent),
                            isError = validValue == null,
                        )
                    }
                }
            }
        },
        confirmButton = { TextButton(enabled = validValue != null, onClick = { validValue?.let(onApply) }) { Text("Apply") } },
        dismissButton = { TextButton(onClick = onDismiss) { Text("Cancel") } },
    )
}

@Composable
private fun InterfaceStatusPanel(state: MainUiState) {
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
