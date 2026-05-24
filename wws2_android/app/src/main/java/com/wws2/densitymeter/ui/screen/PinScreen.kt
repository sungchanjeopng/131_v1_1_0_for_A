package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ArrowBackIos
import androidx.compose.material.icons.automirrored.outlined.Backspace
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.ui.theme.isWideLayout

@Composable
fun PinScreen(
    showBack: Boolean = false,
    onPinEntered: (Int) -> Unit = {},
    onBack: () -> Unit = {},
) {
    var input by remember { mutableStateOf("") }

    fun onKey(key: String) {
        if (input.length >= 4) return
        input += key
        if (input.length == 4) {
            val pin = input.toIntOrNull() ?: 0
            onPinEntered(pin)
        }
    }

    fun onDelete() {
        if (input.isEmpty()) return
        input = input.dropLast(1)
    }

    val wide = isWideLayout

    if (wide) {
        // 가로: 왼쪽 타이틀+도트 | 오른쪽 키패드
        Column(
            modifier = Modifier
                .fillMaxSize()
                .background(AppColors.White)
                .navigationBarsPadding(),
        ) {
            if (showBack) {
                Icon(
                    Icons.AutoMirrored.Filled.ArrowBackIos,
                    contentDescription = "Back",
                    modifier = Modifier
                        .padding(16.dp)
                        .size(22.dp)
                        .clickable { onBack() },
                    tint = AppColors.DarkText,
                )
            }

            Row(
                modifier = Modifier.fillMaxSize(),
                verticalAlignment = Alignment.CenterVertically,
            ) {
                // 왼쪽: 타이틀 + 도트
                Column(
                    modifier = Modifier.weight(1f),
                    horizontalAlignment = Alignment.CenterHorizontally,
                ) {
                    Text("Enter Password", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText, letterSpacing = (-0.8).sp)
                    Spacer(Modifier.height(32.dp))
                    Row {
                        repeat(4) { i ->
                            val filled = i < input.length
                            Box(
                                modifier = Modifier
                                    .padding(horizontal = 12.dp)
                                    .size(16.dp)
                                    .clip(CircleShape)
                                    .background(if (filled) AppColors.DarkText else AppColors.White)
                                    .border(2.dp, if (filled) AppColors.DarkText else AppColors.Border, CircleShape),
                            )
                        }
                    }
                }

                // 오른쪽: 키패드
                PinKeypad(
                    onKey = ::onKey,
                    onDelete = ::onDelete,
                    modifier = Modifier.weight(1f),
                )
            }
        }
    } else {
        // 세로: 기존 레이아웃
        Column(
            modifier = Modifier
                .fillMaxSize()
                .background(AppColors.White)
                .navigationBarsPadding(),
        ) {
            if (showBack) {
                Icon(
                    Icons.AutoMirrored.Filled.ArrowBackIos,
                    contentDescription = "Back",
                    modifier = Modifier
                        .padding(16.dp)
                        .size(22.dp)
                        .clickable { onBack() },
                    tint = AppColors.DarkText,
                )
            } else {
                Spacer(Modifier.height(16.dp))
            }

            Column(
                modifier = Modifier.fillMaxWidth().padding(vertical = 24.dp),
                horizontalAlignment = Alignment.CenterHorizontally,
            ) {
                Text("Enter Password", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText, letterSpacing = (-0.8).sp)
                Spacer(Modifier.height(32.dp))
                Row {
                    repeat(4) { i ->
                        val filled = i < input.length
                        Box(
                            modifier = Modifier
                                .padding(horizontal = 12.dp)
                                .size(16.dp)
                                .clip(CircleShape)
                                .background(if (filled) AppColors.DarkText else AppColors.White)
                                .border(2.dp, if (filled) AppColors.DarkText else AppColors.Border, CircleShape),
                        )
                    }
                }
                Spacer(Modifier.height(16.dp))
            }

            PinKeypad(
                onKey = ::onKey,
                onDelete = ::onDelete,
                modifier = Modifier.fillMaxWidth(),
            )
        }
    }
}

@Composable
private fun PinKeypad(
    onKey: (String) -> Unit,
    onDelete: () -> Unit,
    modifier: Modifier = Modifier,
) {
    val keys = listOf("1", "2", "3", "4", "5", "6", "7", "8", "9", "", "0", "del")
    Column(modifier = modifier) {
        HorizontalDivider(color = AppColors.Background)
        for (row in 0 until 4) {
            Row(modifier = Modifier.fillMaxWidth()) {
                for (col in 0 until 3) {
                    val key = keys[row * 3 + col]
                    Box(
                        modifier = Modifier
                            .weight(1f)
                            .aspectRatio(1.5f)
                            .clickable(enabled = key.isNotEmpty()) {
                                if (key == "del") onDelete() else onKey(key)
                            },
                        contentAlignment = Alignment.Center,
                    ) {
                        when {
                            key.isEmpty() -> {}
                            key == "del" -> Icon(Icons.AutoMirrored.Outlined.Backspace, contentDescription = "Delete",
                                modifier = Modifier.size(24.dp), tint = AppColors.DarkText)
                            else -> Text(key, fontSize = 34.sp, fontWeight = FontWeight.W300, color = AppColors.DarkText)
                        }
                    }
                }
            }
        }
    }
}
