package com.wws2.densitymeter

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat
import com.wws2.densitymeter.model.EchoReading
import com.wws2.densitymeter.ui.component.EchoChart
import com.wws2.densitymeter.ui.component.StatRow
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.ui.theme.DensityMeterTheme
import kotlin.math.sin

class DebugThrActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        enableEdgeToEdge()
        WindowCompat.setDecorFitsSystemWindows(window, false)
        val controller = WindowInsetsControllerCompat(window, window.decorView)
        controller.hide(WindowInsetsCompat.Type.statusBars())
        controller.systemBarsBehavior = WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE

        setContent {
            DensityMeterTheme {
                DebugThrScreen()
            }
        }
    }
}

@Composable
fun DebugThrScreen() {
    val dummyEcho = remember {
        EchoReading(
            eeaR = 30000,
            eeaD = 5000,
            level = 1.42,
            detAreaLO = 50,
            detAreaHI = 180,
            pipeDia = 50,
            rawWave = List(103) { (it * 100).coerceIn(0, 65535) },
            wave = List(EchoReading.INTP_SIZE) { idx ->
                val base = sin(idx * 0.05) * 20000 + 30000
                (base + (idx % 20) * 500).coerceIn(0.0, 65535.0)
            },
            sampleUs = 3.2f,
            thrLightDist = 142,
            thrHeavyDist = 165,
            thrLightAmp = 45000,
            thrHeavyAmp = 32000,
        )
    }

    Box(
        modifier = Modifier
            .fillMaxSize()
            .background(Color(0xFFF2F4F6))
            .systemBarsPadding()
    ) {
        Column(
            modifier = Modifier.fillMaxSize().padding(12.dp)
        ) {
            // Header
            Box(
                modifier = Modifier
                    .fillMaxWidth()
                    .shadow(4.dp, RoundedCornerShape(12.dp))
                    .background(AppColors.Primary, RoundedCornerShape(12.dp))
                    .padding(16.dp)
            ) {
                Text(
                    "THR Debug Preview",
                    fontSize = 20.sp,
                    fontWeight = FontWeight.W700,
                    color = Color.White
                )
            }

            Spacer(Modifier.height(12.dp))

            // THR Info Card
            Box(
                modifier = Modifier
                    .fillMaxWidth()
                    .shadow(2.dp, RoundedCornerShape(12.dp))
                    .background(Color.White, RoundedCornerShape(12.dp))
                    .padding(16.dp)
            ) {
                Column {
                    Text("THR Data (Dummy)", fontSize = 16.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
                    Spacer(Modifier.height(8.dp))
                    Row(modifier = Modifier.fillMaxWidth()) {
                        Column(modifier = Modifier.weight(1f)) {
                            ThrInfoRow("L Dist", "1.42m", Color.White)
                            ThrInfoRow("L AMP", "45000", Color.White)
                        }
                        Column(modifier = Modifier.weight(1f)) {
                            ThrInfoRow("H Dist", "1.65m", Color(0xFFFF8C00))
                            ThrInfoRow("H AMP", "32000", Color(0xFFFF8C00))
                        }
                    }
                }
            }

            Spacer(Modifier.height(12.dp))

            // Echo Chart
            EchoChart(
                echoReading = dummyEcho,
                isInterface = true,
                modifier = Modifier
                    .fillMaxWidth()
                    .weight(1f)
            )

            Spacer(Modifier.height(12.dp))

            // Stats
            StatRow(
                listOf(
                    Triple("EEA.R", "30000", AppColors.Primary),
                    Triple("EEA.D", "5000", AppColors.DarkText),
                    Triple("Level", "1.42m", AppColors.Primary),
                )
            )

            Spacer(Modifier.height(8.dp))

            // Legend
            Box(
                modifier = Modifier
                    .fillMaxWidth()
                    .shadow(2.dp, RoundedCornerShape(12.dp))
                    .background(Color.White, RoundedCornerShape(12.dp))
                    .padding(12.dp)
            ) {
                Row(
                    modifier = Modifier.fillMaxWidth(),
                    horizontalArrangement = Arrangement.SpaceEvenly
                ) {
                    LegendItem(color = Color.White, label = "THR Light (L)")
                    LegendItem(color = Color(0xFFFF8C00), label = "THR Heavy (H)")
                    LegendItem(color = AppColors.Primary, label = "L Marker")
                }
            }
        }
    }
}

@Composable
private fun ThrInfoRow(label: String, value: String, dotColor: Color) {
    Row(verticalAlignment = Alignment.CenterVertically) {
        Box(
            modifier = Modifier
                .size(8.dp)
                .background(dotColor, RoundedCornerShape(4.dp))
        )
        Spacer(Modifier.width(6.dp))
        Text("$label: $value", fontSize = 14.sp, color = AppColors.DarkText)
    }
}

@Composable
private fun LegendItem(color: Color, label: String) {
    Row(verticalAlignment = Alignment.CenterVertically) {
        Box(
            modifier = Modifier
                .size(12.dp)
                .background(color, RoundedCornerShape(2.dp))
        )
        Spacer(Modifier.width(4.dp))
        Text(label, fontSize = 12.sp, color = AppColors.GrayLabel)
    }
}
