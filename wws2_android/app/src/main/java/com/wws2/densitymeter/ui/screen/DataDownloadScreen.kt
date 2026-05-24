package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.CheckCircle
import androidx.compose.material.icons.filled.ChevronRight
import androidx.compose.material.icons.filled.Downloading
import androidx.compose.material.icons.filled.ErrorOutline
import androidx.compose.material.icons.outlined.Description
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.platform.LocalConfiguration
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.model.DensityUnit
import com.wws2.densitymeter.ui.component.*
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.viewmodel.DataFileItem
import com.wws2.densitymeter.viewmodel.DataFilesStage
import com.wws2.densitymeter.viewmodel.DeviceType
import com.wws2.densitymeter.viewmodel.MainViewModel

@Composable
fun DataDownloadScreen(vm: MainViewModel, onPickCsv: () -> Unit = {}, onShare: () -> Unit = {}, onSave: () -> Unit = {}) {
    val state by vm.state.collectAsStateWithLifecycle()

    when (state.dataFilesStage) {
        DataFilesStage.LIST -> ListStage(vm, onPickCsv)
        DataFilesStage.DOWNLOADING -> DownloadingStage(state, vm)
        DataFilesStage.COMPLETE -> CompleteStage(state, vm, onShare, onSave)
        DataFilesStage.VIEW -> ViewStage(state, vm, onShare, onSave)
        DataFilesStage.ERROR -> ErrorStage(state, vm)
    }
}

@Composable
private fun ErrorStage(state: com.wws2.densitymeter.viewmodel.MainUiState, vm: MainViewModel) {
    Column(
        modifier = Modifier.fillMaxSize().verticalScroll(rememberScrollState()).padding(horizontal = 16.dp, vertical = 20.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Spacer(Modifier.height(32.dp))
        Box(Modifier.size(72.dp).clip(CircleShape).background(androidx.compose.ui.graphics.Color(0xFFE53935).copy(alpha = 0.08f)), contentAlignment = Alignment.Center) {
            Icon(Icons.Default.ErrorOutline, contentDescription = null, modifier = Modifier.size(38.dp), tint = androidx.compose.ui.graphics.Color(0xFFE53935))
        }
        Spacer(Modifier.height(20.dp))
        Text("Download Failed", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        Spacer(Modifier.height(8.dp))
        Text(state.trendError ?: "Unknown error", fontSize = 15.sp, color = AppColors.GrayLabel, textAlign = TextAlign.Center)
        Spacer(Modifier.height(28.dp))
        Button(
            onClick = { vm.openDataFilesList() },
            modifier = Modifier.fillMaxWidth(),
            colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary),
            shape = RoundedCornerShape(16.dp),
            contentPadding = PaddingValues(vertical = 14.dp),
        ) { Text("Back", fontSize = 18.sp, fontWeight = FontWeight.W700) }
        Spacer(Modifier.height(32.dp))
    }
}

@Composable
private fun ListStage(vm: MainViewModel, onPickCsv: () -> Unit) {
    val state by vm.state.collectAsStateWithLifecycle()

    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
            .padding(horizontal = 16.dp, vertical = 12.dp),
    ) {
        Text("Download", fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel, letterSpacing = 0.3.sp)
        Spacer(Modifier.height(10.dp))

        CardContainer {
            Text("Target Device", fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
            Spacer(Modifier.height(10.dp))

            if (state.connectedDevices.isNotEmpty()) {
                state.connectedDevices.forEachIndexed { idx, dev ->
                    Row(verticalAlignment = Alignment.CenterVertically) {
                        Box(Modifier.size(9.dp).clip(CircleShape).background(AppColors.Success))
                        Spacer(Modifier.width(8.dp))
                        Text(dev.label, fontSize = 16.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText)
                    }
                    Spacer(Modifier.height(10.dp))
                    Button(
                        onClick = { vm.activateAndDownload(dev.id) },
                        modifier = Modifier.fillMaxWidth(),
                        colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary),
                        shape = RoundedCornerShape(14.dp),
                        contentPadding = PaddingValues(vertical = 13.dp),
                    ) {
                        Text("Download", fontSize = 18.sp, fontWeight = FontWeight.W700)
                    }
                    if (idx < state.connectedDevices.size - 1) {
                        Spacer(Modifier.height(16.dp))
                    }
                }
            } else {
                Row(verticalAlignment = Alignment.CenterVertically) {
                    Box(Modifier.size(9.dp).clip(CircleShape).background(AppColors.WeakText))
                    Spacer(Modifier.width(8.dp))
                    Text("No device connected", fontSize = 16.sp, fontWeight = FontWeight.W600, color = AppColors.GrayLabel)
                }
                Spacer(Modifier.height(14.dp))
                Button(
                    onClick = {},
                    enabled = false,
                    modifier = Modifier.fillMaxWidth(),
                    colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary, disabledContainerColor = AppColors.Border),
                    shape = RoundedCornerShape(14.dp),
                    contentPadding = PaddingValues(vertical = 13.dp),
                ) {
                    Text("Download", fontSize = 18.sp, fontWeight = FontWeight.W700)
                }
            }
        }

        Spacer(Modifier.height(18.dp))
        Text("Open", fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel, letterSpacing = 0.3.sp)
        Spacer(Modifier.height(10.dp))
        FileSelectArea(onTap = onPickCsv)
        Spacer(Modifier.height(20.dp))
        Text("SAVED FILES", fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel, letterSpacing = 0.3.sp)
        Spacer(Modifier.height(10.dp))

        if (state.savedDataFiles.isEmpty()) {
            CardContainer { Text("No saved files yet.", fontSize = 16.sp, color = AppColors.GrayLabel) }
        } else {
            state.savedDataFiles.forEach { file ->
                FileCard(file) { vm.viewDataFile(file) }
            }
        }
    }
}

@Composable
private fun DownloadingStage(state: com.wws2.densitymeter.viewmodel.MainUiState, vm: MainViewModel) {
    val file = state.activeDataFile
    val progress = state.dataDownloadProgress.coerceIn(0.0, 1.0)
    val receivedRecords = state.downloadRecords.size
    val totalRecords = state.trendExpectedRecords

    Column(
        modifier = Modifier.fillMaxSize().verticalScroll(rememberScrollState()).padding(horizontal = 16.dp, vertical = 20.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Spacer(Modifier.height(32.dp))
        Box(Modifier.size(72.dp).clip(CircleShape).background(AppColors.Primary.copy(alpha = 0.08f)), contentAlignment = Alignment.Center) {
            Icon(Icons.Default.Downloading, contentDescription = null, modifier = Modifier.size(38.dp), tint = AppColors.Primary)
        }
        Spacer(Modifier.height(20.dp))
        Text("Downloading...", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        Spacer(Modifier.height(6.dp))
        Text("Receiving log data from the device.", fontSize = 16.sp, color = AppColors.GrayLabel, textAlign = TextAlign.Center)
        Spacer(Modifier.height(24.dp))
        TargetDeviceCard(file?.targetDevice ?: vm.deviceLabelOrDefault)
        Spacer(Modifier.height(14.dp))
        ProgressCard(
            file?.name ?: "--",
            if (totalRecords > 0) "$receivedRecords / $totalRecords records received"
            else "$receivedRecords records received",
            progress,
        )
        Spacer(Modifier.height(18.dp))
        Button(
            onClick = { vm.cancelDataDownload() },
            modifier = Modifier.fillMaxWidth(),
            colors = ButtonDefaults.buttonColors(containerColor = androidx.compose.ui.graphics.Color(0xFFE53935)),
            shape = RoundedCornerShape(16.dp),
            contentPadding = PaddingValues(vertical = 14.dp),
        ) { Text("Cancel", fontSize = 18.sp, fontWeight = FontWeight.W700) }
        Spacer(Modifier.height(32.dp))
    }
}

@Composable
private fun CompleteStage(state: com.wws2.densitymeter.viewmodel.MainUiState, vm: MainViewModel, onShare: () -> Unit = {}, onSave: () -> Unit = {}) {
    val file = state.activeDataFile

    Column(
        modifier = Modifier.fillMaxSize().verticalScroll(rememberScrollState()).padding(horizontal = 16.dp, vertical = 20.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Spacer(Modifier.height(32.dp))
        Box(Modifier.size(72.dp).clip(CircleShape).background(AppColors.Success.copy(alpha = 0.08f)), contentAlignment = Alignment.Center) {
            Icon(Icons.Default.CheckCircle, contentDescription = null, modifier = Modifier.size(38.dp), tint = AppColors.Success)
        }
        Spacer(Modifier.height(20.dp))
        Text("Download Complete", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        Spacer(Modifier.height(6.dp))
        Text("The CSV file is ready to view or share.", fontSize = 16.sp, color = AppColors.GrayLabel, textAlign = TextAlign.Center)
        Spacer(Modifier.height(6.dp))
        Text("Auto-saved: Documents/WESSWARE/${file?.name ?: ""}", fontSize = 12.sp, color = AppColors.WeakText, textAlign = TextAlign.Center)
        Spacer(Modifier.height(24.dp))
        TargetDeviceCard(file?.targetDevice ?: vm.deviceLabelOrDefault)
        Spacer(Modifier.height(14.dp))
        ProgressCard(file?.name ?: "--", "${file?.recordCount ?: 0} records / ${formatBytes(file?.sizeBytes ?: 0)}", 1.0)
        Spacer(Modifier.height(18.dp))
        Button(
            onClick = { file?.let { vm.viewDataFile(it) } },
            modifier = Modifier.fillMaxWidth(),
            colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary),
            shape = RoundedCornerShape(16.dp),
            contentPadding = PaddingValues(vertical = 14.dp),
        ) { Text("View Data", fontSize = 18.sp, fontWeight = FontWeight.W700) }
        Spacer(Modifier.height(10.dp))
        Button(
            onClick = onShare,
            modifier = Modifier.fillMaxWidth(),
            colors = ButtonDefaults.buttonColors(containerColor = AppColors.Success),
            shape = RoundedCornerShape(16.dp),
            contentPadding = PaddingValues(vertical = 14.dp),
        ) { Text("Share", fontSize = 18.sp, fontWeight = FontWeight.W700) }
        Spacer(Modifier.height(32.dp))
    }
}

@Composable
private fun ViewStage(state: com.wws2.densitymeter.viewmodel.MainUiState, vm: MainViewModel, onShare: () -> Unit = {}, onSave: () -> Unit = {}) {
    val file = state.activeDataFile
    val isInterface = file?.targetDevice?.uppercase()?.contains("ENV130") == true
    if (isInterface) {
        InterfaceViewStage(file, state.tempUnit, onShare, onSave)
    } else {
        DensityViewStage(file, state.densUnit, state.tempUnit, onShare, onSave)
    }
}

@Composable
private fun DensityViewStage(file: com.wws2.densitymeter.viewmodel.DataFileItem?, densUnit: Int = 0, tempUnit: Int = 0, onShare: () -> Unit, onSave: () -> Unit) {
    val records = file?.chartRecords ?: emptyList()
    val dUnit = DensityUnit.fromInt(densUnit)
    var minDst = 0.0; var avgDst = 0.0; var maxDst = 0.0
    if (records.isNotEmpty()) {
        minDst = records.minOf { it.dst }; maxDst = records.maxOf { it.dst }
        avgDst = records.sumOf { it.dst } / records.size
    }
    val chartH = (LocalConfiguration.current.screenHeightDp * 0.7f).dp

    Column(
        modifier = Modifier.fillMaxSize().verticalScroll(rememberScrollState()).padding(horizontal = 16.dp, vertical = 12.dp),
    ) {
        FileInfoCard(file)
        Spacer(Modifier.height(8.dp))
        TrendChart(records = records, densUnit = densUnit, tempUnit = tempUnit, modifier = Modifier.fillMaxWidth().height(chartH))
        Spacer(Modifier.height(6.dp))
        StatRow(listOf(
            Triple("Min", if (records.isNotEmpty()) dUnit.format(minDst) else "--", AppColors.DarkText),
            Triple("Avg", if (records.isNotEmpty()) dUnit.format(avgDst) else "--", AppColors.Primary),
            Triple("Max", if (records.isNotEmpty()) dUnit.format(maxDst) else "--", AppColors.DarkText),
        ))
        Spacer(Modifier.height(8.dp))
        ShareButton(onShare)
    }
}

private val OrangeColor = androidx.compose.ui.graphics.Color(0xFFFFA500)
private val GrayColor = androidx.compose.ui.graphics.Color(0xFF666666)

@Composable
private fun InterfaceViewStage(file: com.wws2.densitymeter.viewmodel.DataFileItem?, tempUnit: Int = 0, onShare: () -> Unit, onSave: () -> Unit) {
    val records = file?.chartRecords ?: emptyList()

    val lightValues = records.map { it.dst * 0.01 }
    val heavyValues = records.map { it.eeaD * 0.01 }
    val chartH = (LocalConfiguration.current.screenHeightDp * 0.7f).dp

    Column(
        modifier = Modifier.fillMaxSize().verticalScroll(rememberScrollState()).padding(horizontal = 16.dp, vertical = 12.dp),
    ) {
        FileInfoCard(file)
        Spacer(Modifier.height(8.dp))
        InterfaceTrendChart(records = records, tempUnit = tempUnit, modifier = Modifier.fillMaxWidth().height(chartH))
        Spacer(Modifier.height(6.dp))
        if (records.isNotEmpty()) {
            val lightStats = Triple("%.2f".format(lightValues.min()), "%.2f".format(lightValues.max()), "%.2f".format(lightValues.average()))
            val heavyStats = Triple("%.2f".format(heavyValues.min()), "%.2f".format(heavyValues.max()), "%.2f".format(heavyValues.average()))
            InterfaceStatCard(lightStats, heavyStats)
        } else {
            InterfaceStatCard(Triple("--", "--", "--"), Triple("--", "--", "--"))
        }
        Spacer(Modifier.height(8.dp))
        ShareButton(onShare)
    }
}

@Composable
private fun FileInfoCard(file: com.wws2.densitymeter.viewmodel.DataFileItem?) {
    CardContainer {
        Text(file?.name ?: "--", fontSize = 18.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        Spacer(Modifier.height(8.dp))
        Row(horizontalArrangement = Arrangement.spacedBy(12.dp)) {
            Text("${file?.recordCount ?: 0} records", fontSize = 13.sp, fontWeight = FontWeight.W600, color = AppColors.GrayLabel)
            Text(file?.rangeLabel ?: "--", fontSize = 13.sp, fontWeight = FontWeight.W600, color = AppColors.GrayLabel)
            Text(formatBytes(file?.sizeBytes ?: 0), fontSize = 13.sp, fontWeight = FontWeight.W600, color = AppColors.GrayLabel)
        }
    }
}

@Composable
private fun ShareButton(onShare: () -> Unit, modifier: Modifier = Modifier.fillMaxWidth()) {
    Button(
        onClick = onShare,
        modifier = modifier,
        colors = ButtonDefaults.buttonColors(containerColor = AppColors.Success),
        shape = RoundedCornerShape(16.dp),
        contentPadding = PaddingValues(vertical = 14.dp),
    ) { Text("Share", fontSize = 18.sp, fontWeight = FontWeight.W700) }
}

@Composable
private fun FileCard(file: DataFileItem, onTap: () -> Unit) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .padding(bottom = 10.dp)
            .shadow(2.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
            .clickable { onTap() }
            .padding(horizontal = 16.dp, vertical = 14.dp),
        verticalAlignment = Alignment.CenterVertically,
    ) {
        Box(Modifier.size(40.dp).clip(RoundedCornerShape(12.dp)).background(AppColors.Background), contentAlignment = Alignment.Center) {
            Icon(Icons.Outlined.Description, contentDescription = null, modifier = Modifier.size(20.dp), tint = AppColors.Primary)
        }
        Spacer(Modifier.width(12.dp))
        Column(modifier = Modifier.weight(1f)) {
            Text(file.name, fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText, maxLines = 1, overflow = TextOverflow.Ellipsis)
            Spacer(Modifier.height(4.dp))
            Text("${file.recordCount} records / ${file.rangeLabel}", fontSize = 12.sp, color = AppColors.GrayLabel)
            Spacer(Modifier.height(2.dp))
            Text(formatBytes(file.sizeBytes), fontSize = 12.sp, color = AppColors.WeakText)
        }
        Spacer(Modifier.width(8.dp))
        Icon(Icons.Default.ChevronRight, contentDescription = null, modifier = Modifier.size(20.dp), tint = AppColors.GrayLabel)
    }
}

@Composable
private fun ProgressCard(fileName: String, subtitle: String, progress: Double) {
    CardContainer {
        Text(fileName, fontSize = 16.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        Spacer(Modifier.height(6.dp))
        Text(subtitle, fontSize = 13.sp, color = AppColors.GrayLabel)
        Spacer(Modifier.height(14.dp))
        if (progress > 0.0) {
            LinearProgressIndicator(
                progress = { progress.toFloat() },
                modifier = Modifier.fillMaxWidth().height(10.dp).clip(RoundedCornerShape(999.dp)),
                color = AppColors.Primary,
                trackColor = AppColors.Background,
            )
        } else {
            LinearProgressIndicator(
                modifier = Modifier.fillMaxWidth().height(10.dp).clip(RoundedCornerShape(999.dp)),
                color = AppColors.Primary,
                trackColor = AppColors.Background,
            )
        }
        Spacer(Modifier.height(8.dp))
        Text(
            "${(progress * 100).toInt()}%",
            fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.Primary,
            modifier = Modifier.align(Alignment.End),
        )
    }
}

@Composable
private fun TargetDeviceCard(targetDevice: String) {
    CardContainer {
        Text("Target Device", fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
        Spacer(Modifier.height(10.dp))
        Text(targetDevice, fontSize = 16.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText)
    }
}
