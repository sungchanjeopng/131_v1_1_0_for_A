package com.wws2.densitymeter.ui.component

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.*
import androidx.compose.ui.graphics.drawscope.DrawScope
import androidx.compose.ui.graphics.drawscope.Stroke
import androidx.compose.ui.text.*
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.compose.ui.tooling.preview.Preview
import com.wws2.densitymeter.model.EchoReading
import com.wws2.densitymeter.ui.theme.AppColors

// 토스 스타일 색상
private val TossBlue = Color(0xFF3182F6)
private val TossLightBlue = Color(0xFF3182F6)
private val TossGradientTop = Color(0xCC3182F6)    // 80% opacity
private val TossGradientMid = Color(0x883182F6)    // 53% opacity
private val TossGradientBottom = Color(0x223182F6)  // 13% opacity
private val TossGrid = Color(0xFFF2F4F6)
private val TossGray = Color(0xFF8B95A1)

@Composable
fun EchoChart(echoReading: EchoReading?, isInterface: Boolean = false, modifier: Modifier = Modifier) {
    val textMeasurer = rememberTextMeasurer()

    Box(
        modifier = modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .clip(RoundedCornerShape(16.dp))
            .background(Color.White)
            .padding(start = 12.dp, end = 12.dp, top = 16.dp, bottom = 36.dp)
    ) {
        Canvas(modifier = Modifier.fillMaxSize()) {
            drawEchoChart(this, echoReading, textMeasurer, isInterface)
        }
    }
}

private fun drawEchoChart(scope: DrawScope, reading: EchoReading?, textMeasurer: TextMeasurer, isInterface: Boolean = false) {
    val w = scope.size.width
    val h = scope.size.height
    val totalPoints = EchoReading.INTP_SIZE  // 816
    val yMax = 65535f

    // pipeBaseMm: pipeDia에 따른 mm 기준 (firmware PIPE_OD_*_BASE_MM)
    val pipeBaseMm = if (reading != null) when (reading.pipeDia) {
        1 -> 200; 2 -> 400; else -> 0
    } else 0

    // 토스 스타일 그리드 (얇고 부드러운 선)
    for (i in 1..3) {
        val y = h * i / 4
        scope.drawLine(TossGrid, Offset(0f, y), Offset(w, y), strokeWidth = 1f)
    }

    // X축 라벨 (mm 단위, pipeDia 기반)
    if (isInterface && reading != null) {
        // 계면계: Empty 기준 11등분 (LCD와 동일)
        val emptyVal = reading.detAreaHI
        for (i in 0..10) {
            val v = emptyVal - (emptyVal * i) / 10
            val dist = v * 0.01
            val label = if (dist >= 1.0) "%.1f".format(dist) else "%.2f".format(dist)
            val x = w * i / 10f
            val result = textMeasurer.measure(
                AnnotatedString(label),
                TextStyle(fontSize = 13.sp, color = TossGray)
            )
            scope.drawText(result, topLeft = Offset(
                (x - result.size.width / 2).coerceIn(0f, w - result.size.width),
                h + 8
            ))
        }
    } else {
        // 농도계: pipeDia 기반 mm 라벨 (300mm 범위, 7등분)
        for (i in 0..6) {
            val mm = pipeBaseMm + (EchoReading.MM_RANGE * i) / 6
            val x = w * i / 6f
            val result = textMeasurer.measure(
                AnnotatedString("$mm"),
                TextStyle(fontSize = 13.sp, color = TossGray)
            )
            scope.drawText(result, topLeft = Offset(
                (x - result.size.width / 2).coerceIn(0f, w - result.size.width),
                h + 8
            ))
        }
    }

    if (reading == null || reading.wave.isEmpty()) {
        val result = textMeasurer.measure(
            AnnotatedString("No Data"),
            TextStyle(fontSize = 16.sp, color = TossGray)
        )
        scope.drawText(result, topLeft = Offset((w - result.size.width) / 2, (h - result.size.height) / 2))
        return
    }

    val wave = reading.wave

    // 파형 라인 Path + 채우기 Path
    val linePath = Path()
    val fillPath = Path()
    var started = false

    // 농도계: sampleUs 기반 mm→screen 매핑 (firmware VwEchoGraph_MmToPixel 방식)
    // 계면계: 기존 intpIdx 선형 매핑 유지
    val mmPerInterp = reading.sampleUs * 1.48f / 8f  // mm per interpolation point
    val mmRange = EchoReading.MM_RANGE.toFloat()       // 300mm display window

    // Gate mm (pipeBase 기준)
    val emptyMm = (reading.detAreaHI - pipeBaseMm).coerceAtLeast(0).toFloat()
    val deadzoneMm = (reading.detAreaLO - pipeBaseMm).coerceAtLeast(0).toFloat()

    // 계면계용: intpIdx 기반 gate
    val mmToIdx = (totalPoints - 1).toFloat() / mmRange
    val emptyIdx = (emptyMm * mmToIdx).coerceAtLeast(1f)
    val deadzoneIdx = deadzoneMm * mmToIdx

    // Lo~Hi 구간만 파형 그리기
    for (i in wave.indices) {
        val x: Float
        if (isInterface) {
            if (i < deadzoneIdx || i > emptyIdx) continue
            x = w * i / (totalPoints - 1).toFloat()
        } else {
            val mm = i * mmPerInterp
            if (mm < deadzoneMm || mm > emptyMm) continue
            if (mm > mmRange) break
            x = w * mm / mmRange
        }
        val amplitude = (wave[i].toFloat() / yMax).coerceIn(0f, 1f)
        val y = h - amplitude * h

        if (!started) {
            linePath.moveTo(x, y)
            fillPath.moveTo(x, h)
            fillPath.lineTo(x, y)
            started = true
        } else {
            linePath.lineTo(x, y)
            fillPath.lineTo(x, y)
        }
    }

    if (started) {
        val lastX = if (isInterface) {
            w * emptyIdx.coerceAtMost((totalPoints - 1).toFloat()) / (totalPoints - 1).toFloat()
        } else {
            w * emptyMm.coerceAtMost(mmRange) / mmRange
        }
        fillPath.lineTo(lastX, h)
        fillPath.close()
        scope.drawPath(
            fillPath,
            Brush.verticalGradient(listOf(TossGradientTop, TossGradientMid, TossGradientBottom))
        )
        scope.drawPath(
            linePath,
            TossBlue,
            style = Stroke(width = 2.5f, cap = StrokeCap.Round, join = StrokeJoin.Round)
        )
    }

    // Lo / Hi 수직선
    if (isInterface) {
        if (deadzoneIdx > 0) {
            val dzX = w * deadzoneIdx / (totalPoints - 1).toFloat()
            scope.drawLine(TossBlue.copy(alpha = 0.6f), Offset(dzX, 0f), Offset(dzX, h), strokeWidth = 1.5f)
        }
        if (emptyIdx < totalPoints) {
            val emX = w * emptyIdx / (totalPoints - 1).toFloat()
            scope.drawLine(TossBlue.copy(alpha = 0.6f), Offset(emX, 0f), Offset(emX, h), strokeWidth = 1.5f)
        }
    } else {
        if (deadzoneMm > 0) {
            val dzX = w * deadzoneMm / mmRange
            scope.drawLine(TossBlue.copy(alpha = 0.6f), Offset(dzX, 0f), Offset(dzX, h), strokeWidth = 1.5f)
        }
        if (emptyMm < mmRange) {
            val emX = w * emptyMm / mmRange
            scope.drawLine(TossBlue.copy(alpha = 0.6f), Offset(emX, 0f), Offset(emX, h), strokeWidth = 1.5f)
        }
    }

    // L 마커
    val levelIdx = reading.level.toFloat()
    if (isInterface) {
        if (levelIdx in deadzoneIdx..emptyIdx) {
            val lx = w * levelIdx / (totalPoints - 1).toFloat()
            val amplitude = if (levelIdx.toInt() in wave.indices) {
                (wave[levelIdx.toInt()].toFloat() / yMax).coerceIn(0f, 1f)
            } else 0f
            val ly = h - amplitude * h
            scope.drawLine(TossBlue.copy(alpha = 0.2f), Offset(lx, 0f), Offset(lx, h), strokeWidth = 1f)
            scope.drawCircle(Color.White, 6f, Offset(lx, ly))
            scope.drawCircle(TossBlue, 6f, Offset(lx, ly), style = Stroke(width = 2.5f))
        }
    } else {
        val levelMm = levelIdx * mmPerInterp
        if (levelMm in deadzoneMm..emptyMm && levelMm <= mmRange) {
            val lx = w * levelMm / mmRange
            scope.drawLine(TossBlue.copy(alpha = 0.2f), Offset(lx, 0f), Offset(lx, h), strokeWidth = 1f)
        }
    }

    // THR 그리기 (계면계만)
    if (isInterface) {
        // THR Light 수평 점선 (흰색)
        if (reading.thrLightAmp > 0) {
            val thrLightY = h - (reading.thrLightAmp.toFloat() / yMax) * h
            scope.drawLine(
                Color.White, Offset(0f, thrLightY), Offset(w, thrLightY),
                strokeWidth = 1.5f, pathEffect = PathEffect.dashPathEffect(floatArrayOf(4f, 4f))
            )
        }

        // THR Heavy 수평 점선 (주황색)
        if (reading.thrHeavyAmp > 0) {
            val thrHeavyY = h - (reading.thrHeavyAmp.toFloat() / yMax) * h
            scope.drawLine(
                Color(0xFFFF8C00), Offset(0f, thrHeavyY), Offset(w, thrHeavyY),
                strokeWidth = 1.5f, pathEffect = PathEffect.dashPathEffect(floatArrayOf(4f, 4f))
            )
        }

        // L/H 세로선 + 라벨 (thrLightDist/thrHeavyDist는 x0.01m 단위, 미검출=0 무시)
        // 계면계 X축은 Empty 기준 11등분이므로 mm→screen 직접 변환
        val thrEmptyMm = emptyMm.coerceAtLeast(1f)

        val lDistX = if (reading.thrLightDist > 0) {
            val mm = (reading.thrLightDist - pipeBaseMm).coerceAtLeast(0).toFloat()
            w * mm / thrEmptyMm
        } else 0f

        val hDistX = if (reading.thrHeavyDist > 0) {
            val mm = (reading.thrHeavyDist - pipeBaseMm).coerceAtLeast(0).toFloat()
            w * mm / thrEmptyMm
        } else 0f

        val lhClose = kotlin.math.abs(lDistX - hDistX) < 20f

        // L 세로선 (흰색)
        if (reading.thrLightDist > 0 && lDistX in 0f..w) {
            scope.drawLine(Color.White, Offset(lDistX, 0f), Offset(lDistX, h), strokeWidth = 1.5f)
        }

        // H 세로선 (주황색)
        if (reading.thrHeavyDist > 0 && hDistX in 0f..w) {
            scope.drawLine(Color(0xFFFF8C00), Offset(hDistX, 0f), Offset(hDistX, h), strokeWidth = 1.5f)
        }

        // L/H 라벨
        val thrLabelStyle = TextStyle(fontSize = 12.sp, fontWeight = FontWeight.Bold)
        if (reading.thrLightDist > 0 && lDistX in 0f..w) {
            val lLabelResult = textMeasurer.measure(AnnotatedString("L"), thrLabelStyle)
            scope.drawText(
                lLabelResult,
                topLeft = Offset(lDistX - lLabelResult.size.width / 2f, if (lhClose) 22f else 12f)
            )
        }
        if (reading.thrHeavyDist > 0 && hDistX in 0f..w) {
            val hLabelResult = textMeasurer.measure(AnnotatedString("H"), thrLabelStyle)
            scope.drawText(
                hLabelResult,
                topLeft = Offset(hDistX - hLabelResult.size.width / 2f, if (lhClose) 38f else 12f)
            )
        }
    }
}

private fun drawDashedVerticalLine(scope: DrawScope, x: Float, height: Float, color: Color) {
    var y = 0f
    var draw = true
    while (y < height) {
        val next = (y + 5f).coerceAtMost(height)
        if (draw) scope.drawLine(color, Offset(x, y), Offset(x, next), strokeWidth = 1.5f)
        y = next
        draw = !draw
    }
}

// ─── Preview ───
@Preview
@Composable
private fun EchoChartPreview() {
    val dummyEcho = EchoReading(
        eeaR = 30000,
        eeaD = 5000,
        level = 1.42,       // 1.42m
        detAreaLO = 50,      // D.Z
        detAreaHI = 180,     // EMPTY
        pipeDia = 50,
        rawWave = List(103) { (it * 100).coerceIn(0, 65535) },
        wave = List(EchoReading.INTP_SIZE) { idx ->
            val base = kotlin.math.sin(idx * 0.05) * 20000 + 30000
            (base + (idx % 20) * 500).coerceIn(0.0, 65535.0)
        },
        sampleUs = 3.2f,
        thrLightDist = 142, // 1.42m
        thrHeavyDist = 165, // 1.65m
        thrLightAmp = 45000,
        thrHeavyAmp = 32000,
    )

    EchoChart(
        echoReading = dummyEcho,
        isInterface = true,
        modifier = Modifier
            .fillMaxWidth()
            .height(280.dp)
    )
}
