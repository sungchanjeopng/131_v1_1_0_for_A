package com.wws2.densitymeter.ui.screen

import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.rememberScrollState
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.foundation.verticalScroll
import androidx.compose.material3.HorizontalDivider
import androidx.compose.material3.Text
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.model.CalibrationPoint
import com.wws2.densitymeter.model.DensityUnit
import com.wws2.densitymeter.ui.theme.AppColors
import com.wws2.densitymeter.viewmodel.MainViewModel

private val TossBlue = Color(0xFF3182F6)
private val TossDark = Color(0xFF191F28)
private val TossGray = Color(0xFF8B95A1)
private val TossLightGray = Color(0xFFB0B8C1)
private val TossDivider = Color(0xFFF2F4F6)
private val TossCardBg = Color(0xFFFFFFFF)
private val TossHeaderBg = Color(0xFFF9FAFB)

@Composable
fun CalibScreen(vm: MainViewModel) {
    val state by vm.state.collectAsStateWithLifecycle()
    val points = state.calibrationPoints
    val densUnit = DensityUnit.fromInt(state.densUnit)

    Column(
        modifier = Modifier
            .fillMaxSize()
            .verticalScroll(rememberScrollState())
            .padding(12.dp),
    ) {
        // Table card
        Column(
            modifier = Modifier
                .fillMaxWidth()
                .shadow(6.dp, RoundedCornerShape(20.dp))
                .background(TossCardBg, RoundedCornerShape(20.dp)),
        ) {
            // Header
            Row(
                modifier = Modifier
                    .fillMaxWidth()
                    .background(TossHeaderBg, RoundedCornerShape(topStart = 20.dp, topEnd = 20.dp))
                    .padding(horizontal = 18.dp, vertical = 13.dp),
                verticalAlignment = Alignment.CenterVertically,
            ) {
                Text("No", modifier = Modifier.weight(0.4f), fontSize = 13.sp, fontWeight = FontWeight.W600, color = TossGray, textAlign = TextAlign.Center)
                Text("EEA", modifier = Modifier.weight(1.4f), fontSize = 13.sp, fontWeight = FontWeight.W600, color = TossGray, textAlign = TextAlign.End)
                Text("LV(${densUnit.unitStr})", modifier = Modifier.weight(1.4f), fontSize = 13.sp, fontWeight = FontWeight.W600, color = TossGray, textAlign = TextAlign.End)
                Text("Date", modifier = Modifier.weight(2.5f), fontSize = 13.sp, fontWeight = FontWeight.W600, color = TossGray, textAlign = TextAlign.Center)
            }

            HorizontalDivider(color = TossDivider, thickness = 1.dp)

            if (points.isEmpty()) {
                Box(
                    modifier = Modifier
                        .fillMaxWidth()
                        .padding(vertical = 48.dp),
                    contentAlignment = Alignment.Center,
                ) {
                    Text("No calibration data", fontSize = 15.sp, fontWeight = FontWeight.W500, color = TossLightGray)
                }
            } else {
                points.forEachIndexed { i, pt ->
                    val active = pt.fEEA || pt.fLV
                    Row(
                        modifier = Modifier
                            .fillMaxWidth()
                            .padding(horizontal = 18.dp, vertical = 15.dp),
                        verticalAlignment = Alignment.CenterVertically,
                    ) {
                        Text(
                            "${i + 1}",
                            modifier = Modifier.weight(0.4f),
                            fontSize = 15.sp,
                            fontWeight = FontWeight.W700,
                            color = if (active) TossBlue else TossLightGray,
                            textAlign = TextAlign.Center,
                        )
                        Text(
                            if (pt.fEEA) pt.eea.toString() else "--",
                            modifier = Modifier.weight(1.4f),
                            fontSize = 15.sp,
                            fontWeight = FontWeight.W600,
                            color = if (pt.fEEA) TossDark else TossLightGray,
                            textAlign = TextAlign.End,
                        )
                        Text(
                            if (pt.fLV) densUnit.format(pt.density) else "--",
                            modifier = Modifier.weight(1.4f),
                            fontSize = 15.sp,
                            fontWeight = FontWeight.W600,
                            color = if (pt.fLV) TossDark else TossLightGray,
                            textAlign = TextAlign.End,
                        )
                        Text(
                            if (active) "%02d.%02d.%02d %02d:%02d".format(pt.year % 100, pt.month, pt.day, pt.hour, pt.minute) else "--",
                            modifier = Modifier.weight(2.5f),
                            fontSize = 14.sp,
                            fontWeight = FontWeight.W500,
                            color = if (active) TossGray else TossLightGray,
                            textAlign = TextAlign.Center,
                        )
                    }
                    if (i < points.lastIndex) {
                        HorizontalDivider(
                            modifier = Modifier.padding(horizontal = 16.dp),
                            color = TossDivider,
                            thickness = 0.5.dp,
                        )
                    }
                }
            }
        }
    }
}
