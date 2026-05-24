package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.Bluetooth
import androidx.compose.material.icons.filled.ChevronRight
import androidx.compose.material.icons.filled.CloudUpload
import androidx.compose.material.icons.filled.Description
import androidx.compose.material.icons.filled.Tune
import androidx.compose.ui.res.painterResource
import com.wws2.densitymeter.R
import android.content.Intent
import android.net.Uri
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.vector.ImageVector
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.ui.component.DeviceStripBar
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.viewmodel.DeviceType
import com.wws2.densitymeter.viewmodel.MainViewModel

@Composable
fun MenuTabScreen(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()
    val context = LocalContext.current
    val devices = state.connectedDevices
    val isInterface = state.deviceType == DeviceType.INTERFACE

    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
            .padding(horizontal = 16.dp, vertical = 12.dp),
    ) {
        if (devices.isNotEmpty()) {
            DeviceStripBar(
                devices = devices,
                selectedDeviceId = state.activeDeviceId,
                onDeviceTap = { vm.requestConnectDevice(it) },
                onMoreTap = { vm.openPairing() },
            )
            Spacer(Modifier.height(12.dp))
        }
        MenuCard(
            icon = Icons.Default.Bluetooth,
            iconBg = Color(0xFFE8F3FF),
            iconColor = AppColors.Primary,
            title = "Pairing",
            trailing = if (vm.isConnected) {
                { ConnectedBadge() }
            } else null,
            onTap = { vm.openPairing() },
        )
        Spacer(Modifier.height(10.dp))
        MenuCard(
            icon = Icons.Default.Description,
            iconBg = Color(0xFFE8F3FF),
            iconColor = AppColors.Primary,
            title = "Data Files",
            onTap = { vm.openDataFilesList() },
        )
        Spacer(Modifier.height(10.dp))
        MenuCard(
            icon = Icons.Default.CloudUpload,
            iconBg = Color(0xFFE6F9F1),
            iconColor = AppColors.Success,
            title = "Firmware Upload",
            onTap = { vm.openFirmwareFlow() },
        )
        if (!isInterface) {
            Spacer(Modifier.height(10.dp))
            MenuCard(
                icon = Icons.Default.Tune,
                iconBg = Color(0xFFFFF3E0),
                iconColor = Color(0xFFF57C00),
                title = "Calibration",
                onTap = { vm.openCalib() },
            )
        }
        Spacer(Modifier.height(20.dp))
        Text("App Version 1.0.0", fontSize = 13.sp, color = AppColors.WeakText,
            modifier = Modifier.align(Alignment.CenterHorizontally))
    }
}

@Composable
private fun MenuCard(
    icon: ImageVector,
    iconBg: Color,
    iconColor: Color,
    title: String,
    trailing: (@Composable () -> Unit)? = null,
    onTap: () -> Unit,
) {
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(2.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
            .clickable { onTap() }
            .padding(horizontal = 16.dp, vertical = 14.dp),
        verticalAlignment = Alignment.CenterVertically,
    ) {
        Box(
            Modifier
                .size(40.dp)
                .clip(RoundedCornerShape(12.dp))
                .background(iconBg),
            contentAlignment = Alignment.Center,
        ) {
            Icon(icon, contentDescription = null, modifier = Modifier.size(20.dp), tint = iconColor)
        }
        Spacer(Modifier.width(12.dp))
        Text(title, fontSize = 16.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText,
            modifier = Modifier.weight(1f))
        if (trailing != null) {
            Spacer(Modifier.width(8.dp))
            trailing()
        }
        Spacer(Modifier.width(6.dp))
        Icon(Icons.Default.ChevronRight, contentDescription = null, modifier = Modifier.size(18.dp), tint = AppColors.GrayLabel)
    }
}

@Composable
private fun ConnectedBadge() {
    Box(
        Modifier
            .clip(RoundedCornerShape(999.dp))
            .background(Color(0xFFE6F9F1))
            .padding(horizontal = 9.dp, vertical = 5.dp)
    ) {
        Text("Connected", fontSize = 12.sp, fontWeight = FontWeight.W700, color = AppColors.Success)
    }
}
