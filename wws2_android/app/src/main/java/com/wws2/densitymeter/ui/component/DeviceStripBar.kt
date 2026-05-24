package com.wws2.densitymeter.ui.component

import androidx.compose.foundation.background
import androidx.compose.foundation.border
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.text.style.TextOverflow
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.wws2.densitymeter.model.ConnectedBleDevice
import com.wws2.densitymeter.ui.theme.AppColors

@Composable
fun DeviceStripBar(
    devices: List<ConnectedBleDevice>,
    selectedDeviceId: String,
    visibleDeviceIds: Set<String> = emptySet(),
    onDeviceTap: (String) -> Unit,
    onMoreTap: () -> Unit = {},
) {
    // visibleDeviceIds가 비어있으면 기존 selectedDeviceId 방식 사용
    val useVisibilityMode = visibleDeviceIds.isNotEmpty()

    Row(
        modifier = Modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(18.dp))
            .background(AppColors.White, RoundedCornerShape(18.dp))
            .padding(6.dp),
        verticalAlignment = Alignment.CenterVertically,
    ) {
        devices.forEach { device ->
            val isActive = if (useVisibilityMode) {
                device.id in visibleDeviceIds
            } else {
                device.id == selectedDeviceId
            }
            Row(
                modifier = Modifier
                    .weight(1f)
                    .padding(end = 6.dp)
                    .clip(RoundedCornerShape(14.dp))
                    .background(
                        if (isActive) AppColors.Primary.copy(alpha = 0.12f) else AppColors.Background
                    )
                    .then(
                        if (isActive) Modifier.border(1.dp, AppColors.Primary, RoundedCornerShape(14.dp))
                        else Modifier
                    )
                    .clickable { onDeviceTap(device.id) }
                    .padding(horizontal = 12.dp, vertical = 8.dp),
                horizontalArrangement = Arrangement.Center,
                verticalAlignment = Alignment.CenterVertically,
            ) {
                Box(
                    Modifier
                        .size(6.dp)
                        .clip(CircleShape)
                        .background(if (isActive) AppColors.Primary else AppColors.GrayLabel)
                )
                Spacer(Modifier.width(6.dp))
                Text(
                    text = device.label,
                    textAlign = TextAlign.Center,
                    maxLines = 1,
                    overflow = TextOverflow.Ellipsis,
                    fontSize = 14.sp,
                    fontWeight = FontWeight.W700,
                    color = if (isActive) AppColors.Primary else AppColors.GrayLabel,
                    letterSpacing = (-0.2).sp,
                )
            }
        }
        Box(
            modifier = Modifier
                .size(38.dp, 36.dp)
                .clip(RoundedCornerShape(14.dp))
                .background(AppColors.Background)
                .clickable { onMoreTap() },
            contentAlignment = Alignment.Center,
        ) {
            Text("+", fontSize = 18.sp, fontWeight = FontWeight.W700, color = AppColors.GrayLabel)
        }
    }
}
