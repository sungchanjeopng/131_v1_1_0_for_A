package com.wws2.densitymeter.ui.component

import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.*
import androidx.compose.material.icons.outlined.*
import androidx.compose.material3.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.wws2.densitymeter.ui.theme.AppColors

@Composable
fun CardContainer(modifier: Modifier = Modifier, content: @Composable ColumnScope.() -> Unit) {
    Column(
        modifier = modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
            .padding(16.dp),
        content = content,
    )
}

@Composable
fun StatRow(items: List<Triple<String, String, androidx.compose.ui.graphics.Color>>) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp)),
    ) {
        items.forEachIndexed { i, (label, value, color) ->
            Column(
                modifier = Modifier
                    .weight(1f)
                    .padding(vertical = 16.dp, horizontal = 8.dp),
                horizontalAlignment = Alignment.CenterHorizontally,
            ) {
                Text(label, fontSize = 15.sp, fontWeight = FontWeight.W600, color = AppColors.GrayLabel, letterSpacing = (-0.2).sp)
                Spacer(Modifier.height(6.dp))
                Text(value, fontSize = 24.sp, fontWeight = FontWeight.W700, color = color, letterSpacing = (-0.8).sp)
            }
            if (i < items.lastIndex) {
                Box(
                    Modifier
                        .width(1.dp)
                        .height(52.dp)
                        .background(AppColors.Background)
                        .align(Alignment.CenterVertically)
                )
            }
        }
    }
}

@Composable
fun DeviceCard(
    name: String,
    signalLevel: Int,
    isConnected: Boolean = false,
    isConnecting: Boolean = false,
    isSelected: Boolean = false,
    onTap: () -> Unit = {},
    onDisconnectTap: (() -> Unit)? = null,
) {
    val bgColor = if (isSelected) AppColors.Primary.copy(alpha = 0.08f) else AppColors.White
    val borderColor = if (isSelected) AppColors.Primary else AppColors.White

    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(bottom = 8.dp)
            .background(bgColor, RoundedCornerShape(14.dp))
            .border(1.5.dp, borderColor, RoundedCornerShape(14.dp))
            .clickable(enabled = !isConnecting) { onTap() }
            .padding(horizontal = 14.dp, vertical = 12.dp),
        verticalAlignment = Alignment.CenterVertically,
    ) {
        Box(
            Modifier
                .size(36.dp)
                .clip(RoundedCornerShape(10.dp))
                .background(if (isConnected) AppColors.Success.copy(alpha = 0.08f) else AppColors.Background),
            contentAlignment = Alignment.Center,
        ) {
            Icon(Icons.Default.Bluetooth, contentDescription = null, modifier = Modifier.size(18.dp),
                tint = if (isConnected) AppColors.Success else AppColors.GrayLabel)
        }
        Spacer(Modifier.width(12.dp))
        Column(modifier = Modifier.weight(1f)) {
            Text(name, fontSize = 19.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText, maxLines = 1, overflow = TextOverflow.Ellipsis)
            Spacer(Modifier.height(6.dp))
            SignalBars(level = signalLevel)
        }
        Spacer(Modifier.width(10.dp))
        if (isConnecting) {
            CircularProgressIndicator(modifier = Modifier.size(18.dp), strokeWidth = 2.dp)
        } else {
            val badgeText = if (isConnected) "Connected" else "Disconnected"
            val badgeBg = if (isConnected) AppColors.Success.copy(alpha = 0.1f) else AppColors.Background
            val badgeFg = if (isConnected) AppColors.Success else AppColors.GrayLabel
            Box(
                Modifier
                    .clip(RoundedCornerShape(999.dp))
                    .background(badgeBg)
                    .padding(horizontal = 9.dp, vertical = 5.dp)
            ) {
                Text(badgeText, fontSize = 14.sp, fontWeight = FontWeight.W700, color = badgeFg)
            }
            if (isConnected && onDisconnectTap != null) {
                Spacer(Modifier.width(6.dp))
                Box(
                    Modifier
                        .size(26.dp)
                        .clip(CircleShape)
                        .background(AppColors.Background)
                        .clickable { onDisconnectTap() },
                    contentAlignment = Alignment.Center,
                ) {
                    Icon(Icons.Default.Close, contentDescription = "Disconnect", modifier = Modifier.size(14.dp), tint = AppColors.GrayLabel)
                }
            }
        }
    }
}

@Composable
fun SignalBars(level: Int) {
    Row(verticalAlignment = Alignment.Bottom) {
        val heights = listOf(3.dp, 5.dp, 7.dp)
        repeat(3) { i ->
            Box(
                Modifier
                    .width(10.dp)
                    .height(heights[i])
                    .padding(end = if (i < 2) 4.dp else 0.dp)
                    .clip(RoundedCornerShape(999.dp))
                    .background(if (i < level) AppColors.Primary else AppColors.Border)
            )
        }
    }
}

@Composable
fun FileSelectArea(onTap: () -> Unit) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(2.dp, RoundedCornerShape(14.dp))
            .background(AppColors.White, RoundedCornerShape(14.dp))
            .border(1.5.dp, AppColors.Border, RoundedCornerShape(14.dp))
            .clickable { onTap() }
            .padding(vertical = 22.dp, horizontal = 20.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Box(
            Modifier
                .size(40.dp)
                .clip(RoundedCornerShape(12.dp))
                .background(AppColors.Background),
            contentAlignment = Alignment.Center,
        ) {
            Icon(Icons.Outlined.FolderOpen, contentDescription = null, modifier = Modifier.size(22.dp), tint = AppColors.Primary)
        }
        Spacer(Modifier.height(10.dp))
        Row {
            Text("Open", fontSize = 16.sp, fontWeight = FontWeight.W700, color = AppColors.Primary)
        }
    }
}

@Composable
fun UploadProgressCard(
    fileName: String,
    fileSize: Int,
    progress: Double,
    isDone: Boolean,
    elapsed: Long? = null,
) {
    CardContainer {
        Text(fileName, fontSize = 20.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText, letterSpacing = (-0.5).sp)
        Spacer(Modifier.height(4.dp))
        Text(formatBytes(fileSize), fontSize = 16.sp, color = AppColors.GrayLabel)
        Spacer(Modifier.height(14.dp))
        LinearProgressIndicator(
            progress = { progress.toFloat() },
            modifier = Modifier
                .fillMaxWidth()
                .height(8.dp)
                .clip(RoundedCornerShape(4.dp)),
            color = if (isDone) AppColors.Success else AppColors.Primary,
            trackColor = AppColors.Background,
        )
        Spacer(Modifier.height(8.dp))
        Row(Modifier.fillMaxWidth(), horizontalArrangement = Arrangement.SpaceBetween) {
            Text(if (isDone) "Upload Complete" else "Uploading...", fontSize = 16.sp, color = AppColors.GrayLabel)
            Row(verticalAlignment = Alignment.CenterVertically) {
                if (elapsed != null) {
                    Icon(Icons.Outlined.Timer, contentDescription = null, modifier = Modifier.size(16.dp), tint = AppColors.GrayLabel)
                    Spacer(Modifier.width(3.dp))
                    val m = elapsed / 60000
                    val s = (elapsed / 1000) % 60
                    Text("${m.toString().padStart(2, '0')}:${s.toString().padStart(2, '0')}",
                        fontSize = 16.sp, fontWeight = FontWeight.W600, color = AppColors.GrayLabel)
                    Spacer(Modifier.width(10.dp))
                }
                Text("${"%.1f".format(progress * 100)}%",
                    fontSize = 16.sp, fontWeight = FontWeight.W700, color = if (isDone) AppColors.Success else AppColors.Primary)
            }
        }
    }
}

@Composable
fun SettingsPanel(deviceLabel: String, damping: Int, set4mA: Double, set20mA: Double, pipeDia: Int, freqMHz: Double, densUnit: Int = 0) {
    val dUnit = com.wws2.densitymeter.model.DensityUnit.fromInt(densUnit)
    val pipeDiaLabel = when (pipeDia) { 0 -> "0~200 mm"; 1 -> "200~400 mm"; 2 -> "400~600 mm"; else -> "--" }
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
    ) {
        Text("CONFIGURATION", modifier = Modifier.padding(start = 16.dp, top = 14.dp, bottom = 6.dp),
            fontSize = 18.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        DiagRow("Damping", "$damping")
        DiagRow("4mA Set (${dUnit.unitStr})", dUnit.format(set4mA))
        DiagRow("20mA Set (${dUnit.unitStr})", dUnit.format(set20mA))
        DiagRow("PipeDia", pipeDiaLabel)
        DiagRow("Freq (MHz)", "%.3f".format(freqMHz))
    }
}

@Composable
fun StatusInfoPanel(
    currentMA: Double,
    temperature: Double,
    tempUnit: Int = 0,
    relay: Int = 0,
    extIn1En: Int = 0,
    extIn1State: Int = 0,
    extIn2En: Int = 0,
    extIn2State: Int = 0,
) {
    val tUnit = com.wws2.densitymeter.model.TemperatureUnit.fromInt(tempUnit)
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
    ) {
        Text("Status", modifier = Modifier.padding(start = 16.dp, top = 14.dp, bottom = 6.dp),
            fontSize = 18.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        DiagRow("Current (mA)", "%.2f".format(currentMA))
        DiagRow("Temp (${tUnit.unitStr})", tUnit.format(temperature))
        DiagRow("Relay", if (relay == 1) "Act" else "Stop")
        ExtInputRow("Ext. IN 1", extIn1En, extIn1State)
        ExtInputRow("Ext. IN 2", extIn2En, extIn2State)
    }
}

/** LCD vw_param.c rule:
 *   en=0       -> "OFF" (gray, disabled)
 *   en=1,s=ON  -> "ON (HIGH)"
 *   en=1,else  -> "ON (LOW)"
 */
@Composable
private fun ExtInputRow(label: String, en: Int, state: Int) {
    val EXT_STATE_ON = 2
    if (en == 0) {
        Row(
            modifier = Modifier.fillMaxWidth().padding(horizontal = 16.dp, vertical = 12.dp),
            horizontalArrangement = Arrangement.SpaceBetween,
        ) {
            Text(label, fontSize = 19.sp, color = AppColors.WeakText)
            Text("OFF", fontSize = 20.sp, fontWeight = FontWeight.W600, color = AppColors.WeakText)
        }
    } else {
        val value = if (state == EXT_STATE_ON) "ON (HIGH)" else "ON (LOW)"
        DiagRow(label, value)
    }
}

@Composable
fun DiagRow(label: String, value: String) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(horizontal = 16.dp, vertical = 12.dp),
        horizontalArrangement = Arrangement.SpaceBetween,
    ) {
        Text(label, fontSize = 19.sp, color = AppColors.GrayLabel)
        Text(value, fontSize = 20.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText)
    }
}

fun formatBytes(bytes: Int): String {
    if (bytes < 1024) return "$bytes B"
    if (bytes < 1024 * 1024) return "${"%.1f".format(bytes / 1024.0)} KB"
    return "${"%.1f".format(bytes / (1024.0 * 1024.0))} MB"
}
