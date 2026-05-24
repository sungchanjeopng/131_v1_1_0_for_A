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
import androidx.compose.material.icons.filled.CloudUpload
import androidx.compose.material.icons.filled.UploadFile
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
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.ui.component.*
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.viewmodel.MainViewModel

@Composable
fun UploadScreen(vm: MainViewModel, onPickFile: () -> Unit) {
    val state by vm.state.collectAsStateWithLifecycle()

    when {
        state.firmwareTargetDeviceId.isEmpty() -> SelectDeviceState(vm)
        state.isUploading -> UploadingState(state, vm)
        state.uploadDone -> CompleteState(state, vm)
        else -> ReadyState(state, vm, onPickFile)
    }
}

@Composable
private fun SelectDeviceState(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()

    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
            .padding(horizontal = 16.dp, vertical = 12.dp),
    ) {
        Text("SELECT DEVICE", fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel, letterSpacing = 0.3.sp)
        Spacer(Modifier.height(10.dp))
        if (state.connectedDevices.isEmpty()) {
            CardContainer {
                Text("No connected devices available for firmware update.", fontSize = 15.sp, color = AppColors.GrayLabel)
            }
        } else {
            state.connectedDevices.forEach { device ->
                Row(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(bottom = 12.dp)
                        .shadow(2.dp, RoundedCornerShape(14.dp))
                        .background(AppColors.White, RoundedCornerShape(14.dp))
                        .padding(16.dp),
                    verticalAlignment = Alignment.CenterVertically,
                ) {
                    Box(Modifier.size(10.dp).clip(CircleShape).background(AppColors.Success))
                    Spacer(Modifier.width(10.dp))
                    Text(device.label, modifier = Modifier.weight(1f), fontSize = 16.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText)
                    Button(
                        onClick = { vm.selectFirmwareTarget(device.id) },
                        colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary),
                        shape = RoundedCornerShape(12.dp),
                        contentPadding = PaddingValues(horizontal = 16.dp, vertical = 10.dp),
                    ) {
                        Text("Update", fontSize = 15.sp, fontWeight = FontWeight.W700)
                    }
                }
            }
        }
    }
}

@Composable
private fun ReadyState(state: com.wws2.densitymeter.viewmodel.MainUiState, vm: MainViewModel, onPickFile: () -> Unit) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
            .padding(horizontal = 16.dp, vertical = 12.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Spacer(Modifier.height(8.dp))
        Box(Modifier.size(72.dp).clip(CircleShape).background(AppColors.Primary.copy(alpha = 0.08f)), contentAlignment = Alignment.Center) {
            Icon(Icons.Default.UploadFile, contentDescription = null, modifier = Modifier.size(38.dp), tint = AppColors.Primary)
        }
        Spacer(Modifier.height(16.dp))
        Text("Firmware Update", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        Spacer(Modifier.height(6.dp))
        Text("Select a firmware file to upload.", fontSize = 15.sp, color = AppColors.GrayLabel, textAlign = TextAlign.Center)
        Spacer(Modifier.height(20.dp))
        TargetCard(vm.firmwareTargetLabel ?: "--")
        Spacer(Modifier.height(14.dp))
        FileSelectArea(onTap = onPickFile)

        if (state.pickedFileName != null) {
            Spacer(Modifier.height(14.dp))
            SelectedFileCard(state.pickedFileName, state.pickedFileSize ?: 0)
        }

        Spacer(Modifier.height(18.dp))
        Button(
            onClick = { vm.startUpload() },
            enabled = state.pickedFileName != null,
            modifier = Modifier.fillMaxWidth(),
            colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary, disabledContainerColor = AppColors.Border),
            shape = RoundedCornerShape(14.dp),
            contentPadding = PaddingValues(vertical = 14.dp),
        ) {
            Text("Start Upload", fontSize = 16.sp, fontWeight = FontWeight.W700)
        }
    }
}

@Composable
private fun UploadingState(state: com.wws2.densitymeter.viewmodel.MainUiState, vm: MainViewModel) {
    Column(
        modifier = Modifier.fillMaxSize().padding(horizontal = 16.dp, vertical = 20.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Spacer(Modifier.weight(1f))
        Box(Modifier.size(72.dp).clip(CircleShape).background(AppColors.Primary.copy(alpha = 0.08f)), contentAlignment = Alignment.Center) {
            Icon(Icons.Default.CloudUpload, contentDescription = null, modifier = Modifier.size(36.dp), tint = AppColors.Primary)
        }
        Spacer(Modifier.height(20.dp))
        Text("Uploading...", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        Spacer(Modifier.height(6.dp))
        Text("Do not disconnect the device during firmware transfer.", fontSize = 15.sp, color = AppColors.GrayLabel, textAlign = TextAlign.Center)
        Spacer(Modifier.height(24.dp))
        UploadProgressCard(
            fileName = state.pickedFileName ?: "",
            fileSize = state.pickedFileSize ?: 0,
            progress = state.uploadProgress,
            isDone = false,
            elapsed = state.uploadElapsed,
        )
        Spacer(Modifier.height(14.dp))
        TargetCard(vm.firmwareTargetLabel ?: "--")
        Spacer(Modifier.height(20.dp))
        OutlinedButton(
            onClick = { vm.cancelUpload() },
            modifier = Modifier.fillMaxWidth(),
            shape = RoundedCornerShape(14.dp),
            colors = ButtonDefaults.outlinedButtonColors(contentColor = AppColors.Error),
            border = androidx.compose.foundation.BorderStroke(1.dp, AppColors.Error),
            contentPadding = PaddingValues(vertical = 14.dp),
        ) {
            Text("Cancel", fontSize = 16.sp, fontWeight = FontWeight.W700)
        }
        Spacer(Modifier.weight(1f))
    }
}

@Composable
private fun CompleteState(state: com.wws2.densitymeter.viewmodel.MainUiState, vm: MainViewModel) {
    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
            .padding(horizontal = 16.dp, vertical = 12.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
    ) {
        Spacer(Modifier.height(8.dp))
        Box(Modifier.size(72.dp).clip(CircleShape).background(AppColors.Success.copy(alpha = 0.08f)), contentAlignment = Alignment.Center) {
            Icon(Icons.Default.CheckCircle, contentDescription = null, modifier = Modifier.size(38.dp), tint = AppColors.Success)
        }
        Spacer(Modifier.height(16.dp))
        Text("Upload Complete", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        Spacer(Modifier.height(6.dp))
        Text("Firmware updated successfully.", fontSize = 15.sp, color = AppColors.GrayLabel, textAlign = TextAlign.Center)
        Spacer(Modifier.height(24.dp))
        UploadProgressCard(
            fileName = state.pickedFileName ?: "",
            fileSize = state.pickedFileSize ?: 0,
            progress = 1.0,
            isDone = true,
            elapsed = state.uploadElapsed,
        )
        Spacer(Modifier.height(14.dp))
        TargetCard(vm.firmwareTargetLabel ?: "--")
    }
}

@Composable
private fun TargetCard(targetDevice: String) {
    CardContainer {
        Text("Target Device", fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
        Spacer(Modifier.height(10.dp))
        Text(targetDevice, fontSize = 16.sp, fontWeight = FontWeight.W600, color = AppColors.DarkText)
    }
}

@Composable
private fun SelectedFileCard(name: String?, size: Int) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(2.dp, RoundedCornerShape(14.dp))
            .background(AppColors.White, RoundedCornerShape(14.dp))
            .padding(16.dp),
        verticalAlignment = Alignment.CenterVertically,
    ) {
        Box(
            Modifier.size(42.dp).clip(RoundedCornerShape(12.dp)).background(AppColors.Background),
            contentAlignment = Alignment.Center,
        ) {
            Icon(Icons.Outlined.Description, contentDescription = null, modifier = Modifier.size(22.dp), tint = AppColors.Primary)
        }
        Spacer(Modifier.width(12.dp))
        Column(modifier = Modifier.weight(1f)) {
            Text(name ?: "--", fontSize = 16.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText, maxLines = 1, overflow = TextOverflow.Ellipsis)
            Spacer(Modifier.height(4.dp))
            Text("${formatBytes(size)} / Selected", fontSize = 13.sp, color = AppColors.GrayLabel)
        }
    }
}
