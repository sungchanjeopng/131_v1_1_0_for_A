package com.wws2.densitymeter.ui.component

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Text
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
import com.wws2.densitymeter.model.InterfaceEchoReading

// 색상 정의
private val ColMain = Color(0xFF02F1AB)      // DZ~Empty 파형
private val ColOut = Color(0xFF1B4050)        // DZ 왼쪽 / Empty 오른쪽 파형
private val ColThrLight = Color(0xFF666666)   // Light THR + L 수직선 (진한 회색)
private val ColThrHeavy = Color(0xFFFF8C00)   // Heavy THR + H 수직선 (진한 주황)
private val ColDzEmpty = Color(0xFF3182F6)    // DZ/Empty 수직선 (진하게)
private val ColGrid = Color(0xFFE0E0E0)       // 그리드 (진하게)
private val ColLabel = Color(0xFF8B95A1)

private const val ADC_MAX = 4095f

@Composable
fun InterfaceEchoChart(
    reading: InterfaceEchoReading?,
    modifier: Modifier = Modifier,
) {
    val textMeasurer = rememberTextMeasurer()

    Box(
        modifier = modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .clip(RoundedCornerShape(16.dp))
            .background(Color.White)
            .padding(start = 12.dp, end = 12.dp, top = 12.dp, bottom = 28.dp)
    ) {
        Canvas(modifier = Modifier.fillMaxSize()) {
            drawInterfaceEcho(this, reading, textMeasurer)
        }
    }
}

private fun drawInterfaceEcho(scope: DrawScope, reading: InterfaceEchoReading?, textMeasurer: TextMeasurer) {
    val w = scope.size.width
    val h = scope.size.height


    if (reading == null || reading.wave.isEmpty()) {
        val result = textMeasurer.measure(
            AnnotatedString("No Data"),
            TextStyle(fontSize = 16.sp, color = ColLabel)
        )
        scope.drawText(result, topLeft = Offset((w - result.size.width) / 2, (h - result.size.height) / 2))
        return
    }

    val wave = reading.wave
    val N = wave.size
    if (N < 2) return
    val deadzone = reading.deadzone
    val empty = reading.empty

    fun xOf(idx: Int) = w * idx / (N - 1).toFloat()
    fun xOfF(idx: Float) = w * idx / (N - 1).toFloat()
    fun yOf(v: Int) = h - (v.toFloat() / ADC_MAX).coerceIn(0f, 1f) * h

    // ③ 파형 3구간 (불투명 채움)
    fun drawSegment(start: Int, end: Int, color: Color) {
        val linePath = Path()
        val fillPath = Path()
        var started = false
        var lastX = 0f
        val s = start.coerceAtLeast(0)
        val e = end.coerceAtMost(N - 1)
        for (i in s..e) {
            val x = xOf(i)
            val y = yOf(wave[i])
            if (!started) {
                linePath.moveTo(x, y)
                fillPath.moveTo(x, h)
                fillPath.lineTo(x, y)
                started = true
            } else {
                linePath.lineTo(x, y)
                fillPath.lineTo(x, y)
            }
            lastX = x
        }
        if (!started) return
        fillPath.lineTo(lastX, h)
        fillPath.close()
        scope.drawPath(fillPath, color)
        scope.drawPath(linePath, color, style = Stroke(width = 2f, cap = StrokeCap.Round, join = StrokeJoin.Round))
    }

    drawSegment(0, deadzone, ColOut)
    drawSegment(deadzone, empty, ColMain)
    drawSegment(empty, N - 1, ColOut)

    // ⑤ Deadzone 수직선 (라벨 없음)
    if (deadzone > 0) {
        val dzX = xOf(deadzone)
        scope.drawLine(ColDzEmpty, Offset(dzX, 0f), Offset(dzX, h), strokeWidth = 2.5f)
    }

    // Empty 수직선 (라벨 없음)
    if (empty in 1 until N) {
        val emX = xOf(empty)
        scope.drawLine(ColDzEmpty, Offset(emX, 0f), Offset(emX, h), strokeWidth = 2.5f)
    }

    // ⑦ THR Light 수평 점선 (진한 회색)
    if (reading.thrLightReal > 0) {
        val y = yOf(reading.thrLightReal)
        scope.drawLine(ColThrLight, Offset(0f, y), Offset(w, y), strokeWidth = 2.5f,
            pathEffect = PathEffect.dashPathEffect(floatArrayOf(6f, 4f)))
    }

    // ⑧ THR Heavy 수평 점선 (진한 주황)
    if (reading.thrHeavyReal > 0) {
        val y = yOf(reading.thrHeavyReal)
        scope.drawLine(ColThrHeavy, Offset(0f, y), Offset(w, y), strokeWidth = 2.5f,
            pathEffect = PathEffect.dashPathEffect(floatArrayOf(6f, 4f)))
    }

    // ⑨ L 수직선 (라벨 없음)
    if (reading.thrLightDist > 0) {
        val lX = xOfF(reading.thrLightDist.toFloat())
        scope.drawLine(ColThrLight, Offset(lX, 0f), Offset(lX, h), strokeWidth = 2.5f)
    }

    // ⑩ H 수직선 (라벨 없음)
    if (reading.thrHeavyDist > 0) {
        val hX = xOfF(reading.thrHeavyDist.toFloat())
        scope.drawLine(ColThrHeavy, Offset(hX, 0f), Offset(hX, h), strokeWidth = 2.5f)
    }

    // ⑪ X축 라벨 10등분 (왼쪽=Empty, 오른쪽=0.00) — 파형과는 방향 반대(의도된 불일치)
    //    x = w * (emptyM - v) / totalRangeM, totalRangeM = (N-1)*0.01 (파형 전체 거리)
    //    v = emptyM → x=0 (왼쪽), v=0 → x ≈ w*emptyM/totalRangeM (오른쪽 근처)
    //    그 이후 오른쪽 여백은 -방향 (표시 안 함)
    val emptyM = empty * 0.01f
    val totalRangeM = (N - 1) * 0.01f
    if (emptyM > 0 && totalRangeM > 0) {
        for (i in 0..10) {
            val v = emptyM - (emptyM / 10f) * i
            val x = w * (emptyM - v) / totalRangeM
            if (x < 0f || x > w) continue
            val label = "%.2f".format(v)
            val r = textMeasurer.measure(AnnotatedString(label), TextStyle(fontSize = 11.sp, fontWeight = FontWeight.W500, color = ColLabel))
            scope.drawText(r, topLeft = Offset((x - r.size.width / 2f).coerceIn(0f, w - r.size.width), h + 4f))
        }
    }
}
