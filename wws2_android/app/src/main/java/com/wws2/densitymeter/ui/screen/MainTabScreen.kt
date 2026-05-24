package com.wws2.densitymeter.ui.screen

import android.content.res.Configuration
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.platform.LocalConfiguration
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.model.ConnectedBleDevice
import com.wws2.densitymeter.model.DensityUnit
import com.wws2.densitymeter.model.DeviceReading
import com.wws2.densitymeter.ui.component.DeviceStripBar
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.ui.theme.isTablet
import com.wws2.densitymeter.viewmodel.MainViewModel

@Composable
fun MainTabScreen(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()
    val devices = state.connectedDevices
    val readings = state.deviceReadings

    val densUnit = DensityUnit.fromInt(state.densUnit)

    if (devices.isEmpty()) {
        EmptyMainState(densUnit = densUnit, onOpenPairing = { vm.openPairing() })
    } else {
        val activeDevice = devices.find { it.id == state.activeDeviceId } ?: devices.first()
        Column(modifier = Modifier.fillMaxSize().padding(12.dp)) {
            DeviceStripBar(
                devices = devices,
                selectedDeviceId = state.activeDeviceId,
                onDeviceTap = { vm.requestConnectDevice(it) },
                onMoreTap = { vm.openPairing() },
            )
            Spacer(Modifier.height(8.dp))
            DeviceCard(
                device = activeDevice,
                reading = readings[activeDevice.id],
                isSelected = true,
                isCompact = false,
                densUnit = densUnit,
                onTap = {},
                modifier = Modifier.weight(1f).fillMaxWidth(),
            )
        }
    }
}

@Composable
private fun EmptyMainState(densUnit: DensityUnit, onOpenPairing: () -> Unit) {
    // 페어링 미연결 상태: "No device connected" + Open Pairing 버튼
    Box(modifier = Modifier.fillMaxSize(), contentAlignment = Alignment.Center) {
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
            Button(
                onClick = onOpenPairing,
                modifier = Modifier.fillMaxWidth(),
                colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary),
                shape = RoundedCornerShape(14.dp),
                contentPadding = PaddingValues(vertical = 16.dp),
            ) {
                Text("Open Pairing", fontSize = 18.sp, fontWeight = FontWeight.W700)
            }
        }
    }
}

/** Renders different card layout based on device type (ENV230 = density, ENV130 = interface) */
@Composable
private fun DeviceCard(
    device: ConnectedBleDevice,
    reading: DeviceReading?,
    isSelected: Boolean,
    isCompact: Boolean,
    densUnit: DensityUnit,
    onTap: () -> Unit,
    modifier: Modifier = Modifier,
) {
    val isInterface = device.label.startsWith("ENV130")
    val radius = if (isCompact) 24.dp else 30.dp

    Box(
        modifier = modifier
            .shadow(4.dp, RoundedCornerShape(radius))
            .background(AppColors.White, RoundedCornerShape(radius))
            .then(if (isSelected) Modifier.border(1.5.dp, AppColors.Primary, RoundedCornerShape(radius)) else Modifier)
            .clickable { onTap() }
            .padding(horizontal = if (isCompact) 18.dp else 28.dp, vertical = if (isCompact) 18.dp else 24.dp),
    ) {
        // Device label top-left
        Row(modifier = Modifier.align(Alignment.TopStart), verticalAlignment = Alignment.CenterVertically) {
            Box(Modifier.size(8.dp).clip(CircleShape).background(AppColors.Success))
            Spacer(Modifier.width(8.dp))
            Text(device.label, fontSize = if (isCompact) 13.sp else 16.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText, maxLines = 1, overflow = TextOverflow.Ellipsis)
        }

        if (isInterface) {
            // ─── Interface meter card: single channel Light/Heavy ───
            InterfaceCardContent(reading, isCompact, Modifier.align(Alignment.Center))
        } else {
            // ─── Density meter card: single Level value ───
            DensityCardContent(reading, isCompact, densUnit, Modifier.align(Alignment.Center))
        }
    }
}

@Composable
private fun DensityCardContent(
    reading: DeviceReading?,
    isCompact: Boolean,
    densUnit: DensityUnit,
    modifier: Modifier,
) {
    val value = reading?.level
    val valueText = if (value != null) densUnit.format(value) else "--"
    val tablet = isTablet
    val fontSize = if (isCompact) { if (tablet) 112.sp else 56.sp } else { if (tablet) 240.sp else 120.sp }
    val labelSize = if (isCompact) { if (tablet) 36.sp else 18.sp } else { if (tablet) 56.sp else 28.sp }

    Column(modifier = modifier, horizontalAlignment = Alignment.CenterHorizontally) {
        Text(
            "Density(${densUnit.unitStr})",
            fontSize = labelSize,
            fontWeight = FontWeight.W600,
            color = AppColors.GrayLabel,
        )
        Spacer(Modifier.height(if (isCompact) 4.dp else 8.dp))
        if (value == null) {
            Text("--", fontSize = fontSize, fontWeight = FontWeight.W800, color = AppColors.WeakText)
        } else {
            Text(valueText, fontSize = fontSize, fontWeight = FontWeight.W800, color = AppColors.Primary, letterSpacing = if (isCompact) (-3).sp else (-5).sp)
        }
    }
}


@Composable
private fun InterfaceCardContent(reading: DeviceReading?, isCompact: Boolean, modifier: Modifier) {
    val light = reading?.level
    val heavy = reading?.heavyLevel
    val lightText = if (light != null) "%.2f".format(light * 0.01) else "--"
    val heavyText = if (heavy != null) "%.2f".format(heavy * 0.01) else "--"
    val tablet = isTablet
    val landscape = LocalConfiguration.current.orientation == Configuration.ORIENTATION_LANDSCAPE
    val useRow = landscape && !isCompact

    // Row 배치는 각 셀이 화면 폭 절반만 쓰므로 폰트를 줄여 Light/Heavy 둘 다 잘리지 않게 한다.
    val valueFontSize = when {
        isCompact -> if (tablet) 112.sp else 56.sp
        useRow    -> if (tablet) 180.sp else 80.sp
        else      -> if (tablet) 260.sp else 130.sp
    }
    val labelSize = when {
        isCompact -> if (tablet) 34.sp else 17.sp
        useRow    -> if (tablet) 52.sp else 24.sp
        else      -> if (tablet) 64.sp else 32.sp
    }
    val mSize = when {
        isCompact -> if (tablet) 48.sp else 24.sp
        useRow    -> if (tablet) 72.sp else 32.sp
        else      -> if (tablet) 96.sp else 48.sp
    }

    val orangeColor = androidx.compose.ui.graphics.Color(0xFFFFA500)

    if (useRow) {
        Row(
            modifier = modifier.fillMaxWidth(),
            verticalAlignment = Alignment.CenterVertically,
        ) {
            LevelBlock(
                label = "Light Level",
                valueText = lightText,
                labelColor = AppColors.GrayLabel,
                valueColor = AppColors.DarkText,
                mColor = AppColors.GrayLabel,
                labelSize = labelSize,
                valueSize = valueFontSize,
                mSize = mSize,
                modifier = Modifier.weight(1f),
            )
            LevelBlock(
                label = "Heavy Level",
                valueText = heavyText,
                labelColor = orangeColor,
                valueColor = orangeColor,
                mColor = orangeColor.copy(alpha = 0.6f),
                labelSize = labelSize,
                valueSize = valueFontSize,
                mSize = mSize,
                modifier = Modifier.weight(1f),
            )
        }
    } else {
        Column(modifier = modifier, horizontalAlignment = Alignment.CenterHorizontally) {
            LevelBlock(
                label = "Light Level",
                valueText = lightText,
                labelColor = AppColors.GrayLabel,
                valueColor = AppColors.DarkText,
                mColor = AppColors.GrayLabel,
                labelSize = labelSize,
                valueSize = valueFontSize,
                mSize = mSize,
            )
            Spacer(Modifier.height(if (isCompact) 8.dp else 16.dp))
            LevelBlock(
                label = "Heavy Level",
                valueText = heavyText,
                labelColor = orangeColor,
                valueColor = orangeColor,
                mColor = orangeColor.copy(alpha = 0.6f),
                labelSize = labelSize,
                valueSize = valueFontSize,
                mSize = mSize,
            )
        }
    }
}

@Composable
private fun LevelBlock(
    label: String,
    valueText: String,
    labelColor: androidx.compose.ui.graphics.Color,
    valueColor: androidx.compose.ui.graphics.Color,
    mColor: androidx.compose.ui.graphics.Color,
    labelSize: androidx.compose.ui.unit.TextUnit,
    valueSize: androidx.compose.ui.unit.TextUnit,
    mSize: androidx.compose.ui.unit.TextUnit,
    modifier: Modifier = Modifier,
) {
    Column(modifier = modifier, horizontalAlignment = Alignment.CenterHorizontally) {
        Text(label, fontSize = labelSize, fontWeight = FontWeight.W700, color = labelColor)
        Spacer(Modifier.height(2.dp))
        Row(verticalAlignment = Alignment.Bottom) {
            Text(valueText, fontSize = valueSize, fontWeight = FontWeight.W800, color = valueColor, letterSpacing = (-2).sp, modifier = Modifier.alignByBaseline())
            Spacer(Modifier.width(2.dp))
            Text("m", fontSize = mSize, fontWeight = FontWeight.W700, color = mColor, modifier = Modifier.alignByBaseline())
        }
    }
}
