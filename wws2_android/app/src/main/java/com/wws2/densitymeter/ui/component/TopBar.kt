package com.wws2.densitymeter.ui.component

import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ArrowBackIos
import androidx.compose.material.icons.automirrored.filled.Chat
import androidx.compose.material3.Icon
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.ui.theme.isWideLayout

@Composable
fun TopBar(
    isConnected: Boolean,
    statusLabel: String,
    title: String,
    showBack: Boolean = false,
    rxBlink: Boolean = false,
    aiActive: Boolean = false,
    onBackTap: () -> Unit = {},
    onBleTap: () -> Unit = {},
    onChatTap: () -> Unit = {},
) {
    val topPad = if (isWideLayout) 12.dp else 40.dp
    Row(
        modifier = Modifier
            .fillMaxWidth()
            .background(AppColors.White)
            .padding(horizontal = 20.dp)
            .padding(top = topPad, bottom = 8.dp),
        verticalAlignment = Alignment.CenterVertically,
    ) {
        Row(modifier = Modifier.weight(1f), verticalAlignment = Alignment.CenterVertically) {
            if (showBack) {
                Icon(
                    Icons.AutoMirrored.Filled.ArrowBackIos,
                    contentDescription = "Back",
                    modifier = Modifier
                        .size(20.dp)
                        .clickable { onBackTap() }
                        .padding(end = 8.dp),
                    tint = AppColors.DarkText,
                )
            }
            Text(
                text = title,
                fontSize = 24.sp,
                fontWeight = FontWeight.W700,
                color = AppColors.DarkText,
                letterSpacing = (-0.8).sp,
            )
        }
        Spacer(Modifier.width(8.dp))
        AiSparkleButton(active = aiActive, onTap = onChatTap)
        Spacer(Modifier.width(8.dp))
        BlePillButton(isConnected = isConnected, label = statusLabel, rxBlink = rxBlink, onTap = onBleTap)
    }
}

@Composable
fun AiSparkleButton(active: Boolean = false, onTap: () -> Unit = {}) {
    val activeBg = Brush.linearGradient(
        colors = listOf(Color(0xFF7C3AED), Color(0xFF3B82F6)),
        start = Offset(0f, 0f),
        end = Offset(200f, 0f),
    )
    val inactiveBg = Brush.linearGradient(
        listOf(AppColors.PillDisconnected, AppColors.PillDisconnected),
    )
    val textColor = if (active) Color.White else AppColors.GrayLabel

    Box(
        modifier = Modifier
            .shadow(if (active) 6.dp else 0.dp, RoundedCornerShape(999.dp),
                ambientColor = Color(0xFF7C3AED), spotColor = Color(0xFF3B82F6))
            .clip(RoundedCornerShape(999.dp))
            .background(if (active) activeBg else inactiveBg)
            .clickable { onTap() }
            .padding(horizontal = 12.dp, vertical = 7.dp),
        contentAlignment = Alignment.Center,
    ) {
        Row(verticalAlignment = Alignment.CenterVertically) {
            Text(
                text = "✨",
                fontSize = 12.sp,
                color = textColor,
            )
            Spacer(Modifier.width(3.dp))
            Text(
                text = "AI",
                fontSize = 16.sp,
                fontWeight = FontWeight.W700,
                color = textColor,
                letterSpacing = (-0.2).sp,
            )
        }
    }
}

@Composable
fun BlePillButton(
    isConnected: Boolean,
    label: String,
    rxBlink: Boolean = false,
    onTap: () -> Unit = {},
) {
    val bgColor = if (!isConnected) AppColors.PillDisconnected
    else if (rxBlink) AppColors.Success.copy(alpha = 0.7f)
    else AppColors.Success

    val textColor = if (isConnected) AppColors.White else AppColors.GrayLabel
    val dotColor = if (isConnected) AppColors.White else AppColors.GrayLabel

    Row(
        modifier = Modifier
            .clip(RoundedCornerShape(999.dp))
            .background(bgColor)
            .clickable { onTap() }
            .padding(horizontal = 12.dp, vertical = 7.dp),
        verticalAlignment = Alignment.CenterVertically,
    ) {
        Box(
            Modifier
                .size(8.dp)
                .clip(CircleShape)
                .background(dotColor)
        )
        Spacer(Modifier.width(6.dp))
        Text(
            text = label,
            fontSize = 16.sp,
            fontWeight = FontWeight.W700,
            color = textColor,
            letterSpacing = (-0.2).sp,
        )
    }
}
