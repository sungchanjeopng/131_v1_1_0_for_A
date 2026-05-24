package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.BluetoothDisabled
import androidx.compose.material3.*
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.wws2.densitymeter.ui.theme.AppColors

@Composable
fun BleErrorDialog(
    message: String,
    onRetry: () -> Unit,
    onDismiss: () -> Unit,
) {
    AlertDialog(
        onDismissRequest = onDismiss,
        icon = {
            Box(
                Modifier.size(72.dp).clip(CircleShape).background(AppColors.Error.copy(alpha = 0.08f)),
                contentAlignment = Alignment.Center,
            ) {
                Icon(Icons.Default.BluetoothDisabled, contentDescription = null, modifier = Modifier.size(36.dp), tint = AppColors.Error)
            }
        },
        title = {
            Text("Connection Failed", fontSize = 26.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        },
        text = {
            Text(message, textAlign = TextAlign.Center, color = AppColors.GrayLabel, lineHeight = 22.sp)
        },
        confirmButton = {
            Button(
                onClick = onRetry,
                modifier = Modifier.fillMaxWidth(),
                colors = ButtonDefaults.buttonColors(containerColor = AppColors.Primary),
                shape = RoundedCornerShape(16.dp),
                contentPadding = PaddingValues(vertical = 16.dp),
            ) {
                Text("Retry", fontSize = 20.sp, fontWeight = FontWeight.W600)
            }
        },
        dismissButton = {
            TextButton(
                onClick = onDismiss,
                modifier = Modifier.fillMaxWidth(),
            ) {
                Text("Go to Pairing", fontSize = 20.sp, fontWeight = FontWeight.W600, color = AppColors.GrayLabel)
            }
        },
    )
}
