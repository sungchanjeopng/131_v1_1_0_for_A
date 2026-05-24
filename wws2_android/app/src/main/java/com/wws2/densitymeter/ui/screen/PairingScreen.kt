package com.wws2.densitymeter.ui.screen

import android.Manifest
import android.content.Context
import android.content.pm.PackageManager
import android.location.LocationManager
import android.os.Build
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.BluetoothSearching
import androidx.compose.material.icons.filled.Info
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.core.content.ContextCompat
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.ui.component.DeviceCard
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.viewmodel.MainViewModel

@Composable
fun PairingScreen(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()
    val scanned by vm.connectionService.scannedDevices.collectAsStateWithLifecycle()
    val isScanning by vm.connectionService.isScanning.collectAsStateWithLifecycle()
    val context = LocalContext.current
    var showLocationDialog by remember { mutableStateOf(false) }

    // Permission launcher
    val permissionLauncher = rememberLauncherForActivityResult(
        ActivityResultContracts.RequestMultiplePermissions()
    ) { results ->
        val allGranted = results.values.all { it }
        if (allGranted) {
            // Check location service
            val lm = context.getSystemService(Context.LOCATION_SERVICE) as LocationManager
            val locationEnabled = lm.isProviderEnabled(LocationManager.GPS_PROVIDER) ||
                    lm.isProviderEnabled(LocationManager.NETWORK_PROVIDER)
            if (!locationEnabled && Build.VERSION.SDK_INT < Build.VERSION_CODES.S) {
                showLocationDialog = true
            } else {
                vm.connectionService.startScan()
            }
        }
    }

    fun requestPermissionsAndScan() {
        val permissions = mutableListOf<String>()
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            permissions.add(Manifest.permission.BLUETOOTH_SCAN)
            permissions.add(Manifest.permission.BLUETOOTH_CONNECT)
        }
        permissions.add(Manifest.permission.ACCESS_FINE_LOCATION)

        val allGranted = permissions.all {
            ContextCompat.checkSelfPermission(context, it) == PackageManager.PERMISSION_GRANTED
        }

        if (allGranted) {
            val lm = context.getSystemService(Context.LOCATION_SERVICE) as LocationManager
            val locationEnabled = lm.isProviderEnabled(LocationManager.GPS_PROVIDER) ||
                    lm.isProviderEnabled(LocationManager.NETWORK_PROVIDER)
            if (!locationEnabled && Build.VERSION.SDK_INT < Build.VERSION_CODES.S) {
                showLocationDialog = true
            } else {
                vm.connectionService.startScan()
            }
        } else {
            permissionLauncher.launch(permissions.toTypedArray())
        }
    }

    // Location dialog
    if (showLocationDialog) {
        AlertDialog(
            onDismissRequest = { showLocationDialog = false },
            title = { Text("Location Required") },
            text = { Text("BLE scanning requires Location services.\nPlease enable Location (GPS) and try again.") },
            confirmButton = {
                TextButton(onClick = { showLocationDialog = false }) { Text("OK") }
            },
        )
    }

    // 연결된 기기의 원본 MAC 주소 추출 (_CH1/_CH2 제거)
    val connectedAddrs = state.connectedDevices.map { it.id.substringBefore("_CH") }.toSet()
    val unconnected = scanned.values
        .filter { it.address !in connectedAddrs }
        .sortedByDescending { it.rssi }
    // 타입별 분리 — 계면계(ENV130)와 농도계(ENV230)를 별도 섹션으로 표시
    val interfaceDevices = unconnected.filter {
        it.rawName.uppercase().startsWith("W3") ||
            it.rawName.uppercase().contains("ENV130") ||
            it.name.uppercase().startsWith("ENV130")
    }
    val densityDevices = unconnected.filter { it !in interfaceDevices }
    val hasMaxConnections = state.connectedDevices.size >= 4

    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
            .padding(horizontal = 16.dp, vertical = 12.dp),
    ) {
        // Scan panel
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .shadow(2.dp, RoundedCornerShape(18.dp))
                .background(AppColors.White, RoundedCornerShape(18.dp))
                .padding(18.dp),
            horizontalAlignment = Alignment.CenterHorizontally,
        ) {
            Box(
                Modifier.size(48.dp).clip(CircleShape).background(AppColors.Primary.copy(alpha = 0.08f)),
                contentAlignment = Alignment.Center,
            ) {
                if (isScanning) {
                    CircularProgressIndicator(
                        modifier = Modifier.size(48.dp),
                        color = AppColors.Primary,
                        strokeWidth = 2.dp,
                    )
                }
                Icon(Icons.Default.BluetoothSearching, contentDescription = null, modifier = Modifier.size(24.dp), tint = AppColors.Primary)
            }
            Spacer(Modifier.height(12.dp))
            Text(
                if (isScanning) "Scanning nearby devices" else "Pair BLE devices",
                fontSize = 22.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText,
            )
            Spacer(Modifier.height(6.dp))
            Text(
                if (isScanning) "Tap a device card to connect after PIN entry." else "Use Scan Devices to find nearby BLE devices.",
                fontSize = 16.sp, color = AppColors.GrayLabel, textAlign = TextAlign.Center,
            )
            Spacer(Modifier.height(12.dp))
            Row(horizontalArrangement = Arrangement.Center) {
                Box(
                    Modifier.clip(RoundedCornerShape(999.dp))
                        .background(if (isScanning) AppColors.Primary.copy(alpha = 0.1f) else AppColors.Background)
                        .padding(horizontal = 12.dp, vertical = 6.dp)
                ) {
                    Text(
                        if (isScanning) "Scanning..." else "Ready to scan",
                        fontSize = 12.sp, fontWeight = FontWeight.W700,
                        color = if (isScanning) AppColors.Primary else AppColors.GrayLabel,
                    )
                }
                Spacer(Modifier.width(8.dp))
                Box(
                    Modifier.clip(RoundedCornerShape(999.dp)).background(AppColors.Background).padding(horizontal = 12.dp, vertical = 6.dp)
                ) {
                    Text("${state.connectedDevices.size}/4 Connected", fontSize = 12.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
                }
            }
        }

        Spacer(Modifier.height(12.dp))

        if (hasMaxConnections) {
            Row(
                modifier = Modifier.fillMaxWidth()
                    .background(AppColors.White, RoundedCornerShape(14.dp))
                    .padding(horizontal = 14.dp, vertical = 12.dp),
                verticalAlignment = Alignment.CenterVertically,
            ) {
                Icon(Icons.Default.Info, contentDescription = null, modifier = Modifier.size(16.dp), tint = AppColors.Primary)
                Spacer(Modifier.width(8.dp))
                Text("4 devices connected. Scanning continues for nearby devices.", fontSize = 13.sp, color = AppColors.GrayLabel)
            }
            Spacer(Modifier.height(10.dp))
        }

        Column(
            modifier = Modifier.fillMaxWidth(),
        ) {
            val connectedInterface = state.connectedDevices.filter {
                it.label.uppercase().startsWith("ENV130") || it.deviceType == 1
            }
            val connectedDensity = state.connectedDevices.filter { it !in connectedInterface }

            // ─── ENV130 대섹션 ───
            DeviceGroupSection(title = "ENV130") {
                DeviceSubSection(
                    label = "Connected",
                    count = connectedInterface.size,
                    countSuffix = "active",
                    emptyText = "No connected devices.",
                ) {
                    connectedInterface.forEach { device ->
                        val scan = scanned[device.id]
                        DeviceCard(
                            name = device.label,
                            signalLevel = vm.connectionService.signalLevel(scan?.rssi ?: -70),
                            isConnected = true,
                            isSelected = device.id == state.activeDeviceId,
                            onTap = { vm.requestConnectDevice(device.id) },
                            onDisconnectTap = { vm.disconnectDevice(device.id) },
                        )
                    }
                }
                Spacer(Modifier.height(8.dp))
                DeviceSubSection(
                    label = "Scanned",
                    count = interfaceDevices.size,
                    countSuffix = "found",
                    emptyText = if (isScanning) "Searching for ENV130 devices..." else "No ENV130 devices found.",
                ) {
                    interfaceDevices.forEach { device ->
                        DeviceCard(
                            name = device.name,
                            signalLevel = vm.connectionService.signalLevel(device.rssi),
                            isConnecting = state.connectingIds.contains(device.address),
                            onTap = { vm.requestConnectDevice(device.address) },
                        )
                    }
                }
            }

            Spacer(Modifier.height(14.dp))

            // ─── ENV230 대섹션 ───
            DeviceGroupSection(title = "ENV230") {
                DeviceSubSection(
                    label = "Connected",
                    count = connectedDensity.size,
                    countSuffix = "active",
                    emptyText = "No connected devices.",
                ) {
                    connectedDensity.forEach { device ->
                        val scan = scanned[device.id]
                        DeviceCard(
                            name = device.label,
                            signalLevel = vm.connectionService.signalLevel(scan?.rssi ?: -70),
                            isConnected = true,
                            isSelected = device.id == state.activeDeviceId,
                            onTap = { vm.requestConnectDevice(device.id) },
                            onDisconnectTap = { vm.disconnectDevice(device.id) },
                        )
                    }
                }
                Spacer(Modifier.height(8.dp))
                DeviceSubSection(
                    label = "Scanned",
                    count = densityDevices.size,
                    countSuffix = "found",
                    emptyText = if (isScanning) "Searching for ENV230 devices..." else "No ENV230 devices found.",
                ) {
                    densityDevices.forEach { device ->
                        DeviceCard(
                            name = device.name,
                            signalLevel = vm.connectionService.signalLevel(device.rssi),
                            isConnecting = state.connectingIds.contains(device.address),
                            onTap = { vm.requestConnectDevice(device.address) },
                        )
                    }
                }
            }
        }

        Spacer(Modifier.height(10.dp))

        if (!isScanning) {
            Button(
                onClick = { requestPermissionsAndScan() },
                modifier = Modifier.fillMaxWidth(),
                colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary),
                shape = RoundedCornerShape(12.dp),
                contentPadding = PaddingValues(vertical = 14.dp),
            ) {
                Text("Scan Devices", fontSize = 22.sp, fontWeight = FontWeight.W700)
            }
        } else {
            Text(
                "Scanning continues while this page is open.",
                fontSize = 13.sp, color = AppColors.GrayLabel,
                modifier = Modifier.align(Alignment.CenterHorizontally),
            )
        }
    }
}

// "WESS_V0.1_ENV230_A01" → "ENV230_A01"
private fun extractDisplayName(name: String): String {
    if (name.isBlank()) return "Unknown Device"
    val regex = Regex("(ENV\\d+_A\\d+)", RegexOption.IGNORE_CASE)
    return regex.find(name)?.value ?: name
}

@Composable
private fun SectionTitle(text: String, helper: String) {
    Row(
        modifier = Modifier.fillMaxWidth().padding(start = 2.dp, end = 2.dp, top = 6.dp, bottom = 8.dp),
        horizontalArrangement = Arrangement.SpaceBetween,
    ) {
        Text(text, fontSize = 14.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
        Text(helper, fontSize = 12.sp, fontWeight = FontWeight.W600, color = AppColors.WeakText)
    }
}

/** Device type 대섹션 (ENV130 / ENV230) — 외곽 박스 + 큰 타이틀 + 내부 하위 섹션 */
@Composable
private fun DeviceGroupSection(title: String, content: @Composable () -> Unit) {
    Column(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(3.dp, RoundedCornerShape(18.dp))
            .background(AppColors.White, RoundedCornerShape(18.dp))
            .padding(14.dp),
    ) {
        Text(title, fontSize = 18.sp, fontWeight = FontWeight.W800, color = AppColors.DarkText,
            modifier = Modifier.padding(bottom = 8.dp, start = 2.dp))
        content()
    }
}

/** Group 안의 하위 섹션 (Connected / Scanned) */
@Composable
private fun DeviceSubSection(
    label: String,
    count: Int,
    countSuffix: String,
    emptyText: String,
    content: @Composable () -> Unit,
) {
    Column {
        Row(
            modifier = Modifier.fillMaxWidth().padding(start = 2.dp, end = 2.dp, bottom = 6.dp),
            horizontalArrangement = Arrangement.SpaceBetween,
        ) {
            Text(label, fontSize = 13.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
            Text("$count $countSuffix", fontSize = 11.sp, fontWeight = FontWeight.W600, color = AppColors.WeakText)
        }
        if (count == 0) {
            Box(
                Modifier.fillMaxWidth()
                    .background(AppColors.LightGray, RoundedCornerShape(12.dp))
                    .padding(12.dp),
            ) {
                Text(emptyText, fontSize = 13.sp, color = AppColors.GrayLabel)
            }
        } else {
            content()
        }
    }
}
