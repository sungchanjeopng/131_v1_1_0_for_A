package com.wws2.densitymeter.ui.component

import androidx.compose.foundation.Canvas
import androidx.compose.foundation.background
import androidx.compose.foundation.gestures.awaitEachGesture
import androidx.compose.foundation.gestures.awaitFirstDown
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.runtime.*
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clipToBounds
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.*
import androidx.compose.ui.graphics.drawscope.DrawScope
import androidx.compose.ui.graphics.drawscope.Stroke
import androidx.compose.ui.graphics.drawscope.clipRect
import androidx.compose.ui.input.pointer.pointerInput
import androidx.compose.ui.text.*
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.wws2.densitymeter.model.DensityUnit
import com.wws2.densitymeter.model.TemperatureUnit
import com.wws2.densitymeter.model.TrendRecord
import com.wws2.densitymeter.ui.theme.AppColors
import kotlin.math.abs
import kotlin.math.min

@Composable
fun TrendChart(records: List<TrendRecord>, densUnit: Int = 0, tempUnit: Int = 0, modifier: Modifier = Modifier) {
    val textMeasurer = rememberTextMeasurer()
    var scaleX by remember { mutableFloatStateOf(1f) }
    var scaleY by remember { mutableFloatStateOf(1f) }
    var offsetX by remember { mutableFloatStateOf(0f) }
    var offsetY by remember { mutableFloatStateOf(0f) }
    var touchPos by remember { mutableStateOf<Offset?>(null) }

    // 줌/팬 중에는 리셋 안 함. 수동으로만 리셋 (더블탭 등)

    Box(
        modifier = modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
            .padding(start = 12.dp, end = 12.dp, top = 8.dp, bottom = 4.dp)
    ) {
        val dUnit = DensityUnit.fromInt(densUnit)
        val tUnit = TemperatureUnit.fromInt(tempUnit)
        Canvas(modifier = Modifier
            .fillMaxSize()
            .clipToBounds()
            .pointerInput(Unit) {
                awaitEachGesture {
                    val down = awaitFirstDown(requireUnconsumed = false)
                    var prevP1 = down.position
                    var prevP2: Offset? = null
                    var isLongPress = false
                    var dragDist = 0f
                    val longPressTime = 300L
                    val downTime = System.currentTimeMillis()

                    while (true) {
                        val event = awaitPointerEvent()
                        val pressed = event.changes.filter { it.pressed }
                        if (pressed.isEmpty()) break

                        if (pressed.size == 1) {
                            val pos = pressed[0].position
                            val elapsed = System.currentTimeMillis() - downTime
                            dragDist += abs(pos.x - prevP1.x) + abs(pos.y - prevP1.y)

                            if (prevP2 != null) {
                                // 두 손가락 → 한 손가락 전환: 팬 무시, 위치만 갱신
                                prevP1 = pos
                                prevP2 = null
                            } else if (isLongPress || (elapsed > longPressTime && dragDist < 30f)) {
                                // 길게 누르기: 크로스헤어
                                isLongPress = true
                                touchPos = pos
                                prevP1 = pos
                            } else if (dragDist >= 30f) {
                                // 드래그: 팬 이동
                                touchPos = null
                                val mt = (size.height * 0.1f).coerceIn(60f, 110f)
                                val bw = size.width - 70f - 70f
                                val bh = size.height - mt - mt
                                offsetX = (offsetX + pos.x - prevP1.x).coerceIn(-(bw * (scaleX - 1)), 0f)
                                offsetY = (offsetY + pos.y - prevP1.y).coerceIn(-(bh * (scaleY - 1)), 0f)
                                prevP1 = pos
                            } else {
                                prevP1 = pos
                            }
                        } else if (pressed.size >= 2) {
                            touchPos = null
                            val p1 = pressed[0].position
                            val p2 = pressed[1].position
                            val centroid = Offset((p1.x + p2.x) / 2, (p1.y + p2.y) / 2)

                            if (prevP2 != null) {
                                val prevDx = abs(prevP1.x - prevP2!!.x).coerceAtLeast(1f)
                                val prevDy = abs(prevP1.y - prevP2!!.y).coerceAtLeast(1f)
                                val curDx = abs(p1.x - p2.x).coerceAtLeast(1f)
                                val curDy = abs(p1.y - p2.y).coerceAtLeast(1f)

                                val zoomX = curDx / prevDx
                                val zoomY = curDy / prevDy
                                val xChange = abs(curDx - prevDx)
                                val yChange = abs(curDy - prevDy)

                                val oldSx = scaleX; val oldSy = scaleY

                                if (xChange > yChange * 1.5f) {
                                    scaleX = (scaleX * zoomX).coerceIn(1f, 10f)
                                } else if (yChange > xChange * 1.5f) {
                                    scaleY = (scaleY * zoomY).coerceIn(1f, 10f)
                                } else {
                                    scaleX = (scaleX * zoomX).coerceIn(1f, 10f)
                                    scaleY = (scaleY * zoomY).coerceIn(1f, 10f)
                                }

                                // 줌 중심점 보정: centroid를 차트 영역 기준으로 변환
                                val mL = 70f
                                val mT = (size.height * 0.1f).coerceIn(60f, 110f)
                                val cx = centroid.x - mL
                                val cy = centroid.y - mT

                                if (scaleX != oldSx) {
                                    offsetX = cx - (cx - offsetX) * scaleX / oldSx
                                }
                                if (scaleY != oldSy) {
                                    offsetY = cy - (cy - offsetY) * scaleY / oldSy
                                }
                                val baseW = size.width - mL - 70f
                                val baseH = size.height - mT - mT
                                offsetX = offsetX.coerceIn(-(baseW * (scaleX - 1)), 0f)
                                offsetY = offsetY.coerceIn(-(baseH * (scaleY - 1)), 0f)
                            }

                            prevP1 = p1; prevP2 = p2
                        }
                    }
                    touchPos = null
                }
            }
        ) {
            drawTrendChart(this, records, textMeasurer, scaleX, scaleY, offsetX, offsetY, touchPos, dUnit, tUnit)
        }
    }
}

private fun drawTrendChart(
    scope: DrawScope, records: List<TrendRecord>, textMeasurer: TextMeasurer,
    scaleX: Float, scaleY: Float, offsetX: Float, offsetY: Float, touchPos: Offset?,
    dUnit: DensityUnit = DensityUnit.fromInt(0), tUnit: TemperatureUnit = TemperatureUnit.fromInt(0)
) {
    val totalW = scope.size.width
    val totalH = scope.size.height

    val marginLeft = 70f
    val marginRight = 70f
    val marginTop = (totalH * 0.1f).coerceIn(60f, 110f)
    val marginBottom = marginTop

    // 고정 차트 영역 (라벨 기준)
    val baseW = totalW - marginLeft - marginRight
    val baseH = totalH - marginTop - marginBottom
    // 확대된 차트 영역 (데이터 기준)
    val chartW = baseW * scaleX
    val chartH = baseH * scaleY

    if (baseW <= 0 || baseH <= 0) return

    if (records.isEmpty()) {
        val result = textMeasurer.measure(AnnotatedString("No Data"), TextStyle(fontSize = 16.sp, color = AppColors.GrayLabel))
        scope.drawText(result, topLeft = Offset((totalW - result.size.width) / 2, (totalH - result.size.height) / 2))
        return
    }

    // 범위 계산 — raw 값 기준 min/max (표시만 단위 변환)
    var dstMax = records.first().dst
    var tempMin = records.first().temperature; var tempMax = records.first().temperature
    for (r in records) {
        if (r.dst > dstMax) dstMax = r.dst
        if (r.temperature < tempMin) tempMin = r.temperature; if (r.temperature > tempMax) tempMax = r.temperature
    }
    val dstMin = 0.0
    dstMax = if (dstMax < 1.0) 1.0 else dstMax * 1.2
    tempMin -= 5; tempMax += 5
    val dstSpan = if (abs(dstMax - dstMin) < 0.001) 1.0 else dstMax - dstMin
    val tempSpan = if (abs(tempMax - tempMin) < 0.001) 1.0 else tempMax - tempMin

    // ═══ 보이는 범위 계산 (줌/팬 반영) ═══
    val sorted = records.sortedBy { it.dateTime }
    val timeStart = sorted.first().dateTime.toEpochSecond(java.time.ZoneOffset.UTC)
    val timeEnd = sorted.last().dateTime.toEpochSecond(java.time.ZoneOffset.UTC)
    val timeSpan = if (timeEnd > timeStart) (timeEnd - timeStart).toFloat() else 1f

    // 보이는 Y 범위
    val visDstMax = dstMin + dstSpan * (offsetY + chartH) / chartH
    val visDstMin = dstMin + dstSpan * (offsetY + chartH - baseH) / chartH
    val visTempMax = tempMin + tempSpan * (offsetY + chartH) / chartH
    val visTempMin = tempMin + tempSpan * (offsetY + chartH - baseH) / chartH
    val visDstSpan = visDstMax - visDstMin
    val visTempSpan = visTempMax - visTempMin

    // 보이는 X 범위
    val visTimeStart = timeStart + (timeSpan * (-offsetX / chartW)).toLong()
    val visTimeEnd = timeStart + (timeSpan * (baseW - offsetX) / chartW).toLong()

    // ═══ 라벨 (고정 위치, 보이는 범위 값) ═══

    // Y축 제목
    val dstTitle = textMeasurer.measure(AnnotatedString("Density(${dUnit.unitStr})"), TextStyle(fontSize = 15.sp, color = AppColors.Primary, fontWeight = FontWeight.Bold))
    scope.drawText(dstTitle, topLeft = Offset(0f, marginTop - dstTitle.size.height - 30f))
    val tempTitle = textMeasurer.measure(AnnotatedString("Temp(${tUnit.unitStr})"), TextStyle(fontSize = 15.sp, color = AppColors.Temperature, fontWeight = FontWeight.Bold))
    scope.drawText(tempTitle, topLeft = Offset(totalW - tempTitle.size.width, marginTop - tempTitle.size.height - 30f))

    // Y축 라벨 - Density (보이는 범위, raw → 단위 변환 표시)
    for (i in 0..4) {
        val dVal = visDstMax - visDstSpan * i / 4
        val label = dUnit.format(dVal)
        val result = textMeasurer.measure(AnnotatedString(label), TextStyle(fontSize = 12.sp, color = AppColors.Primary))
        val y = marginTop + baseH * i / 4
        scope.drawText(result, topLeft = Offset(marginLeft - result.size.width - 4f, y - result.size.height / 2f))
    }

    // Y축 라벨 - Temperature (보이는 범위)
    for (i in 0..4) {
        val tVal = visTempMax - visTempSpan * i / 4
        val label = tUnit.format(tVal)
        val result = textMeasurer.measure(AnnotatedString(label), TextStyle(fontSize = 12.sp, color = AppColors.Temperature))
        val y = marginTop + baseH * i / 4
        scope.drawText(result, topLeft = Offset(marginLeft + baseW + 4f, y - result.size.height / 2f))
    }

    // Y축 가로 점선
    val dashEffect = PathEffect.dashPathEffect(floatArrayOf(8f, 6f), 0f)
    for (i in 0..4) {
        val y = marginTop + baseH * i / 4
        scope.drawLine(Color(0xFFCCCCCC), Offset(marginLeft, y), Offset(marginLeft + baseW, y),
            strokeWidth = 1f, pathEffect = dashEffect)
    }

    // X축 라벨 + 세로 점선 (보이는 범위)
    val labelCount = min(5, sorted.size)
    if (labelCount > 1) {
        val visSpan = visTimeEnd - visTimeStart
        val xInset = 20f
        for (i in 0 until labelCount) {
            val t = visTimeStart + (visSpan * i / (labelCount - 1))
            val dt = java.time.LocalDateTime.ofEpochSecond(t, 0, java.time.ZoneOffset.UTC)
            val text = "%02d:%02d:%02d\n%02d/%02d/%02d".format(dt.hour, dt.minute, dt.second, dt.year % 100, dt.monthValue, dt.dayOfMonth)
            val result = textMeasurer.measure(AnnotatedString(text), TextStyle(fontSize = 11.sp, color = AppColors.GrayLabel))
            val rawX = marginLeft + baseW * i / (labelCount - 1)
            val x = when (i) {
                0 -> rawX + xInset
                labelCount - 1 -> rawX - xInset
                else -> rawX
            }
            // 세로 점선
            scope.drawLine(Color(0xFFCCCCCC), Offset(x, marginTop), Offset(x, marginTop + baseH),
                strokeWidth = 1f, pathEffect = dashEffect)
            scope.drawText(result, topLeft = Offset(
                (x - result.size.width / 2).coerceIn(marginLeft, totalW - marginRight - result.size.width),
                marginTop + baseH + (marginBottom * 0.35f)
            ))
        }
    }

    // ═══ 데이터 영역 (줌/팬 적용, 클리핑) ═══
    val densityPoints = mutableListOf<Offset>()
    val tempPoints = mutableListOf<Offset>()

    for (r in sorted) {
        val t = r.dateTime.toEpochSecond(java.time.ZoneOffset.UTC)
        val x = marginLeft + offsetX + chartW * (t - timeStart) / timeSpan
        val dy = marginTop + offsetY + chartH - ((r.dst - dstMin) / dstSpan * chartH).toFloat()
        val ty = marginTop + offsetY + chartH - ((r.temperature - tempMin) / tempSpan * chartH).toFloat()
        densityPoints.add(Offset(x, dy))
        tempPoints.add(Offset(x, ty))
    }

    // 차트 영역만 클리핑해서 데이터 그리기
    scope.clipRect(marginLeft, marginTop, marginLeft + baseW, marginTop + baseH) {
        // Density 선
        if (densityPoints.size >= 2) {
            val path = Path()
            path.moveTo(densityPoints[0].x, densityPoints[0].y)
            for (i in 1 until densityPoints.size) {
                val cx = (densityPoints[i - 1].x + densityPoints[i].x) / 2
                path.cubicTo(cx, densityPoints[i - 1].y, cx, densityPoints[i].y, densityPoints[i].x, densityPoints[i].y)
            }
            drawPath(path, AppColors.Primary, style = Stroke(width = 5f, cap = StrokeCap.Round, join = StrokeJoin.Round))
        }

        // Temperature 선 (투명)
        if (tempPoints.size >= 2) {
            val path = Path()
            path.moveTo(tempPoints[0].x, tempPoints[0].y)
            for (i in 1 until tempPoints.size) {
                val cx = (tempPoints[i - 1].x + tempPoints[i].x) / 2
                path.cubicTo(cx, tempPoints[i - 1].y, cx, tempPoints[i].y, tempPoints[i].x, tempPoints[i].y)
            }
            drawPath(path, AppColors.Temperature.copy(alpha = 0.4f), style = Stroke(width = 5f, cap = StrokeCap.Round, join = StrokeJoin.Round))
        }

        // 터치 크로스헤어
        if (touchPos != null && sorted.isNotEmpty()) {
            var nearestIdx = 0; var nearestDist = Float.MAX_VALUE
            for (i in densityPoints.indices) {
                val dist = abs(densityPoints[i].x - touchPos.x)
                if (dist < nearestDist) { nearestDist = dist; nearestIdx = i }
            }
            val dp = densityPoints[nearestIdx]
            val tp = tempPoints[nearestIdx]

            drawLine(Color(0x66888888), Offset(dp.x, marginTop), Offset(dp.x, marginTop + baseH), strokeWidth = 1f)
            drawLine(Color(0x66888888), Offset(marginLeft, dp.y), Offset(marginLeft + baseW, dp.y), strokeWidth = 0.5f)
            drawCircle(AppColors.Primary, 6f, dp)
            drawCircle(Color.White, 3.5f, dp)
            drawCircle(AppColors.Temperature, 5f, tp)
            drawCircle(Color.White, 3f, tp)
        }
    }

    // 터치 툴팁 — 상단 여백에 표시
    if (touchPos != null && sorted.isNotEmpty()) {
        var nearestIdx = 0; var nearestDist = Float.MAX_VALUE
        for (i in densityPoints.indices) {
            val dist = abs(densityPoints[i].x - touchPos.x)
            if (dist < nearestDist) { nearestDist = dist; nearestIdx = i }
        }
        val rec = sorted[nearestIdx]
        val dt = rec.dateTime

        // 시간
        val timeTxt = textMeasurer.measure(
            AnnotatedString("%04d/%02d/%02d  %02d:%02d:%02d".format(dt.year, dt.monthValue, dt.dayOfMonth, dt.hour, dt.minute, dt.second)),
            TextStyle(fontSize = 12.sp, color = Color(0xFFAAAAAA), fontWeight = FontWeight.Medium)
        )
        // Density 값
        val dTxt = textMeasurer.measure(
            AnnotatedString("Density  ${dUnit.format(rec.dst)}"),
            TextStyle(fontSize = 13.sp, color = AppColors.Primary, fontWeight = FontWeight.Bold)
        )
        // Temp 값
        val tTxt = textMeasurer.measure(
            AnnotatedString("Temp  ${tUnit.format(rec.temperature)}"),
            TextStyle(fontSize = 13.sp, color = AppColors.Temperature, fontWeight = FontWeight.Bold)
        )

        val boxW = maxOf(timeTxt.size.width, dTxt.size.width + tTxt.size.width + 24).toFloat() + 24f
        val boxH = timeTxt.size.height + dTxt.size.height + 16f
        val bx = ((totalW - boxW) / 2).coerceAtLeast(0f)
        val by = 2f

        // 배경
        scope.drawRoundRect(Color(0xF0FFFFFF), topLeft = Offset(bx, by),
            size = androidx.compose.ui.geometry.Size(boxW, boxH),
            cornerRadius = androidx.compose.ui.geometry.CornerRadius(12f, 12f))
        scope.drawRoundRect(Color(0x22000000), topLeft = Offset(bx, by),
            size = androidx.compose.ui.geometry.Size(boxW, boxH),
            cornerRadius = androidx.compose.ui.geometry.CornerRadius(12f, 12f),
            style = Stroke(width = 1f))

        // 시간 (중앙)
        scope.drawText(timeTxt, topLeft = Offset(bx + (boxW - timeTxt.size.width) / 2, by + 4f))
        // Density (좌) + Temp (우)
        val valY = by + timeTxt.size.height + 8f
        scope.drawText(dTxt, topLeft = Offset(bx + 12f, valY))
        scope.drawText(tTxt, topLeft = Offset(bx + boxW - tTxt.size.width - 12f, valY))
    }
}
