package com.wws2.densitymeter.ui.screen

import android.content.Intent
import android.net.Uri
import android.provider.OpenableColumns
import android.widget.Toast
import androidx.activity.compose.BackHandler
import androidx.activity.compose.rememberLauncherForActivityResult
import androidx.activity.result.contract.ActivityResultContracts
import androidx.compose.animation.core.animateDpAsState
import androidx.compose.animation.core.tween
import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.gestures.detectVerticalDragGestures
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.platform.LocalDensity
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import androidx.lifecycle.viewmodel.compose.viewModel
import com.wws2.densitymeter.ui.component.BottomNavBar
import com.wws2.densitymeter.ui.component.TopBar
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.ui.screen.ChatbotScreen
import com.wws2.densitymeter.ui.screen.ChatbotSheetContent
import com.wws2.densitymeter.viewmodel.MainViewModel
import kotlinx.coroutines.flow.collectLatest

@Composable
fun MainShellScreen(vm: MainViewModel = viewModel()) {
    val state by vm.state.collectAsStateWithLifecycle()
    val context = LocalContext.current
    val snackbarHostState = remember { SnackbarHostState() }
    val showPinForPairing by vm.showPinForPairing.collectAsStateWithLifecycle()
    val bleError by vm.bleError.collectAsStateWithLifecycle()

    // AI 커스텀 바텀시트 (화면 비율 기반)
    var showAiSheet by remember { mutableStateOf(false) }
    var sheetFraction by remember { mutableFloatStateOf(0.25f) } // 초기: 25%
    val density = LocalDensity.current

    // Snackbar display disabled — messages are collected but not shown.
    // Kept the collector to drain the SharedFlow (prevents buffer buildup).
    LaunchedEffect(Unit) {
        vm.snackbarMessage.collectLatest { /* suppressed */ }
    }

    val firmwareFilePicker = rememberLauncherForActivityResult(ActivityResultContracts.GetContent()) { uri: Uri? ->
        if (uri == null) return@rememberLauncherForActivityResult
        val cr = context.contentResolver
        val name = uri.lastPathSegment ?: "firmware.bin"
        val bytes = cr.openInputStream(uri)?.readBytes() ?: return@rememberLauncherForActivityResult
        vm.setPickedFile(name, bytes.size, bytes)
    }

    val csvFilePicker = rememberLauncherForActivityResult(ActivityResultContracts.OpenDocument()) { uri: Uri? ->
        if (uri == null) return@rememberLauncherForActivityResult
        val cr = context.contentResolver

        val name = run {
            var displayName: String? = null
            try {
                cr.query(uri, arrayOf(OpenableColumns.DISPLAY_NAME), null, null, null)?.use { cursor ->
                    if (cursor.moveToFirst()) {
                        val idx = cursor.getColumnIndex(OpenableColumns.DISPLAY_NAME)
                        if (idx >= 0) displayName = cursor.getString(idx)
                    }
                }
            } catch (_: Exception) {}
            displayName ?: uri.lastPathSegment?.substringAfterLast('/') ?: "data.csv"
        }

        if (!name.endsWith(".csv", ignoreCase = true)) {
            Toast.makeText(context, "CSV 파일만 선택할 수 있습니다: $name", Toast.LENGTH_SHORT).show()
            return@rememberLauncherForActivityResult
        }

        if (!name.contains("env130", ignoreCase = true) && !name.contains("env230", ignoreCase = true)) {
            Toast.makeText(context, "ENV130 또는 ENV230 파일만 사용할 수 있습니다: $name", Toast.LENGTH_SHORT).show()
            return@rememberLauncherForActivityResult
        }

        val size = try { cr.openInputStream(uri)?.available() ?: 0 } catch (_: Exception) { 0 }
        vm.importCsvFile(name, size)
    }

    val csvSaveLauncher = rememberLauncherForActivityResult(ActivityResultContracts.CreateDocument("text/csv")) { uri: Uri? ->
        if (uri == null) return@rememberLauncherForActivityResult
        val pair = vm.getCsvContentForSave() ?: return@rememberLauncherForActivityResult
        try {
            context.contentResolver.openOutputStream(uri)?.use { it.write(pair.second.toByteArray()) }
        } catch (_: Exception) {}
    }

    // Full-screen PIN for pairing
    if (showPinForPairing) {
        PinScreen(
            showBack = true,
            onPinEntered = { pin -> vm.onPairingPinResult(pin) },
            onBack = { vm.onPairingPinResult(-1) },
        )
        return
    }

    // BLE error dialog
    bleError?.let { err ->
        BleErrorDialog(
            message = err.message,
            onRetry = { vm.retryBleError() },
            onDismiss = { vm.dismissBleError() },
        )
    }

    val showTopBarBack = state.tabIndex == 4 && state.subPage != null

    Scaffold(
        // snackbarHost removed — no bottom snackbar shown anymore.
        containerColor = AppColors.Background,
    ) { padding ->
        Column(
            modifier = Modifier
                .fillMaxSize()
                .padding(padding),
        ) {
            TopBar(
                isConnected = vm.isConnected,
                statusLabel = vm.statusLabel,
                title = vm.currentTitle,
                showBack = showTopBarBack,
                rxBlink = state.rxBlink,
                aiActive = showAiSheet,
                onBackTap = { vm.handleTopBarBack() },
                onBleTap = { vm.openPairing() },
                onChatTap = {
                    if (showAiSheet) {
                        showAiSheet = false
                        sheetFraction = 0.25f
                    } else {
                        showAiSheet = true
                        sheetFraction = 0.25f
                    }
                },
            )

            Box(modifier = Modifier.weight(1f)) {
                when {
                    state.tabIndex == 4 && state.subPage == "calib" -> CalibScreen(vm)
                    state.tabIndex == 4 && state.subPage == "pairing" -> PairingScreen(vm)
                    state.tabIndex == 4 && state.subPage == "upload" -> UploadScreen(vm) { firmwareFilePicker.launch("application/octet-stream") }
                    state.tabIndex == 4 && state.subPage == "chatbot" -> ChatbotScreen(
                        onBack = { vm.handleTopBarBack() },
                        vm = vm,
                    )
                    state.tabIndex == 4 && state.subPage == "download" -> DataDownloadScreen(vm, onPickCsv = {
                        csvFilePicker.launch(arrayOf(
                            "text/csv",
                            "text/comma-separated-values",
                            "application/csv",
                            "application/vnd.ms-excel",
                        ))
                    }, onShare = {
                        val intent = vm.shareDataFile()
                        if (intent != null) {
                            context.startActivity(Intent.createChooser(intent, "Share CSV"))
                        }
                    }, onSave = {
                        val pair = vm.getCsvContentForSave()
                        if (pair != null) {
                            csvSaveLauncher.launch(pair.first)
                        }
                    })
                    state.tabIndex == 0 -> MainTabScreen(vm)
                    state.tabIndex == 1 -> EchoTabScreen(vm)
                    state.tabIndex == 2 -> TrendTabScreen(vm)
                    state.tabIndex == 3 -> DiagnosticsTabScreen(vm)
                    state.tabIndex == 4 -> MenuTabScreen(vm)
                }

                // AI 커스텀 바텀시트 — 콘텐츠 영역 내 하단 정렬 (BottomNavBar 침범 방지)
                if (showAiSheet) {
                    BoxWithConstraints(
                        modifier = Modifier
                            .align(Alignment.BottomCenter)
                            .fillMaxWidth(),
                    ) {
                        val maxH = maxHeight
                        val targetHeight = maxH * sheetFraction

                        Box(
                            modifier = Modifier
                                .fillMaxWidth()
                                .height(targetHeight)
                                .align(Alignment.BottomCenter)
                                .clip(RoundedCornerShape(topStart = 20.dp, topEnd = 20.dp))
                                .background(AppColors.Background)
                                .border(1.dp, AppColors.Border, RoundedCornerShape(topStart = 20.dp, topEnd = 20.dp)),
                        ) {
                            Column(modifier = Modifier.fillMaxSize()) {
                                // 드래그 핸들 + AI 타이틀
                                Column(
                                    modifier = Modifier
                                        .fillMaxWidth()
                                        .pointerInput(Unit) {
                                            detectVerticalDragGestures { _, dragAmount ->
                                                val maxPx = maxH.value
                                                val deltaFraction = dragAmount / (maxPx * density.density)
                                                sheetFraction = (sheetFraction - deltaFraction).coerceIn(0.10f, 0.95f)
                                            }
                                        }
                                        .padding(top = 10.dp, bottom = 4.dp),
                                    horizontalAlignment = Alignment.CenterHorizontally,
                                ) {
                                    Box(
                                        Modifier
                                            .width(40.dp)
                                            .height(4.dp)
                                            .background(AppColors.Border, RoundedCornerShape(2.dp))
                                    )
                                }
                                ChatbotSheetContent(vm = vm, modifier = Modifier.weight(1f))
                            }
                        }
                    }
                }
            }

            BottomNavBar(
                currentIndex = state.tabIndex,
                onTap = { vm.setTab(it) },
            )
        }
    }
}
