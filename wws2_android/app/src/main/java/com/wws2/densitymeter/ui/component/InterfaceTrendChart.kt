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
import com.wws2.densitymeter.model.TemperatureUnit
import com.wws2.densitymeter.model.TrendRecord
import com.wws2.densitymeter.ui.theme.AppColors
import kotlin.math.abs
import kotlin.math.min

private val ColLight = Color(0xFF666666)   // Light 선 (회색)
private val ColHeavy = Color(0xFFFFA500)   // Heavy 선 (주황)
private val ColTemp = Color(0xFFFF4444)    // 온도 (빨강)
private const val ML = 70f   // marginLeft
private const val MR = 70f   // marginRight

@Composable
fun InterfaceTrendChart(records: List<TrendRecord>, tempUnit: Int = 0, modifier: Modifier = Modifier) {
    val textMeasurer = rememberTextMeasurer()
    var scaleX by remember { mutableFloatStateOf(1f) }
    var scaleY by remember { mutableFloatStateOf(1f) }
    var offsetX by remember { mutableFloatStateOf(0f) }
    var offsetY by remember { mutableFloatStateOf(0f) }
    var touchPos by remember { mutableStateOf<Offset?>(null) }

    LaunchedEffect(records.size) { if (scaleX == 1f && scaleY == 1f) { offsetX = 0f; offsetY = 0f }; touchPos = null }

    Box(
        modifier = modifier
            .fillMaxWidth()
            .shadow(4.dp, RoundedCornerShape(16.dp))
            .background(AppColors.White, RoundedCornerShape(16.dp))
            .padding(start = 12.dp, end = 12.dp, top = 8.dp, bottom = 4.dp)
    ) {
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
                            dragDist += kotlin.math.abs(pos.x - prevP1.x) + kotlin.math.abs(pos.y - prevP1.y)

                            if (prevP2 != null) {
                                // Pinch → single finger transition: swallow this frame so the
                                // remaining finger's position does not cause a jump-pan.
                                prevP1 = pos
                                prevP2 = null
                            } else if (isLongPress || (elapsed > longPressTime && dragDist < 30f)) {
                                isLongPress = true
                                touchPos = pos
                                prevP1 = pos
                            } else if (dragDist >= 30f) {
                                touchPos = null
                                val mt = (size.height * 0.1f).coerceIn(60f, 110f)
                                val bw = size.width - ML - MR
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
                                val prevDx = kotlin.math.abs(prevP1.x - prevP2!!.x).coerceAtLeast(1f)
                                val prevDy = kotlin.math.abs(prevP1.y - prevP2!!.y).coerceAtLeast(1f)
                                val curDx = kotlin.math.abs(p1.x - p2.x).coerceAtLeast(1f)
                                val curDy = kotlin.math.abs(p1.y - p2.y).coerceAtLeast(1f)

                                val zoomX = curDx / prevDx
                                val zoomY = curDy / prevDy
                                val xChange = kotlin.math.abs(curDx - prevDx)
                                val yChange = kotlin.math.abs(curDy - prevDy)

                                val oldSx = scaleX; val oldSy = scaleY

                                if (xChange > yChange * 1.5f) {
                                    scaleX = (scaleX * zoomX).coerceIn(1f, 10f)
                                } else if (yChange > xChange * 1.5f) {
                                    scaleY = (scaleY * zoomY).coerceIn(1f, 10f)
                                } else {
                                    scaleX = (scaleX * zoomX).coerceIn(1f, 10f)
                                    scaleY = (scaleY * zoomY).coerceIn(1f, 10f)
                                }

                                val mt = (size.height * 0.1f).coerceIn(60f, 110f)
                                val cx = centroid.x - ML
                                val cy = centroid.y - mt
                                offsetX = cx - (cx - offsetX) * scaleX / oldSx
                                offsetY = cy - (cy - offsetY) * scaleY / oldSy
                                val bw = size.width - ML - MR
                                val bh = size.height - mt - mt
                                offsetX = offsetX.coerceIn(-(bw * (scaleX - 1)), 0f)
                                offsetY = offsetY.coerceIn(-(bh * (scaleY - 1)), 0f)
                            }

                            prevP1 = p1; prevP2 = p2
                        }
                    }
                    touchPos = null
                }
            }
        ) {
            drawInterfaceTrend(this, records, textMeasurer, scaleX, scaleY, offsetX, offsetY, touchPos, tUnit)
        }
    }
}

private fun drawInterfaceTrend(
    scope: DrawScope, records: List<TrendRecord>, textMeasurer: TextMeasurer,
    scaleX: Float = 1f, scaleY: Float = 1f, offsetX: Float = 0f, offsetY: Float = 0f, touchPos: Offset? = null,
    tUnit: TemperatureUnit = TemperatureUnit.fromInt(0)
) {
    val totalW = scope.size.width
    val totalH = scope.size.height

    val marginLeft = 70f
    val marginRight = 70f
    val marginTop = (totalH * 0.1f).coerceIn(60f, 110f)
    val marginBottom = marginTop

    val baseW = totalW - marginLeft - marginRight
    val baseH = totalH - marginTop - marginBottom
    val chartW = baseW * scaleX
    val chartH = baseH * scaleY

    if (chartW <= 0 || chartH <= 0) return

    if (records.isEmpty()) {
        val result = textMeasurer.measure(
            AnnotatedString("No Data"),
            TextStyle(fontSize = 16.sp, color = AppColors.GrayLabel)
        )
        scope.drawText(result, topLeft = Offset(
            (totalW - result.size.width) / 2,
            (totalH - result.size.height) / 2
        ))
        return
    }

    // 범위 계산 — Light(dst), Heavy(eeaD*0.01)를 합쳐서 Level 범위
    var levelMin = Double.MAX_VALUE
    var levelMax = Double.MIN_VALUE
    var tempMin = records.first().temperature
    var tempMax = records.first().temperature
    for (r in records) {
        val light = r.dst * 0.01
        val heavy = r.eeaD * 0.01
        if (light < levelMin) levelMin = light
        if (light > levelMax) levelMax = light
        if (heavy < levelMin) levelMin = heavy
        if (heavy > levelMax) levelMax = heavy
        if (r.temperature < tempMin) tempMin = r.temperature
        if (r.temperature > tempMax) tempMax = r.temperature
    }
    levelMin = (levelMin - 0.2).coerceAtLeast(0.0)
    levelMax = levelMax + 0.2
    tempMin -= 5; tempMax += 5
    val levelSpan = if (abs(levelMax - levelMin) < 0.001) 1.0 else levelMax - levelMin
    val tempSpan = if (abs(tempMax - tempMin) < 0.001) 1.0 else tempMax - tempMin

    // Y축 가로 점선
    val dashEffect = PathEffect.dashPathEffect(floatArrayOf(8f, 6f), 0f)
    for (i in 0..4) {
        val y = marginTop + chartH * i / 4
        scope.drawLine(Color(0xFFCCCCCC), Offset(marginLeft, y), Offset(marginLeft + chartW, y),
            strokeWidth = 1f, pathEffect = dashEffect)
    }

    // Y축 제목 — 왼쪽: Level(m) (위로 올림)
    val levelTitle = textMeasurer.measure(
        AnnotatedString("Level(m)"),
        TextStyle(fontSize = 15.sp, color = AppColors.DarkText, fontWeight = FontWeight.Bold)
    )
    val titleGap = (marginTop * 0.27f).coerceIn(8f, 30f)
    scope.drawText(levelTitle, topLeft = Offset(0f, marginTop - levelTitle.size.height - titleGap))

    // Y축 제목 — 오른쪽: Temp (위로 올림)
    val tempTitle = textMeasurer.measure(
        AnnotatedString("Temp(${tUnit.unitStr})"),
        TextStyle(fontSize = 15.sp, color = ColTemp, fontWeight = FontWeight.Bold)
    )
    scope.drawText(tempTitle, topLeft = Offset(totalW - tempTitle.size.width, marginTop - tempTitle.size.height - titleGap))

    // Visible range 계산 (줌/오프셋 반영)
    val visLevelTop = levelMax + offsetY * levelSpan / chartH
    val visLevelBot = levelMax - (baseH - offsetY) * levelSpan / chartH
    val visLevelSpan = visLevelTop - visLevelBot
    val visTempTop = tempMax + offsetY * tempSpan / chartH
    val visTempBot = tempMax - (baseH - offsetY) * tempSpan / chartH

    // Y축 라벨 — 왼쪽: Level (visible range 기반)
    for (i in 0..4) {
        val v = visLevelTop - visLevelSpan * i / 4
        val label = "%.2f".format(v)
        val result = textMeasurer.measure(AnnotatedString(label), TextStyle(fontSize = 13.sp, color = AppColors.DarkText))
        val y = marginTop + baseH * i / 4
        scope.drawText(result, topLeft = Offset(marginLeft - result.size.width - 4f, y - result.size.height / 2f))
    }

    // Y축 라벨 — 오른쪽: Temperature (visible range 기반, tUnit으로 포맷)
    val visTempSpan = visTempTop - visTempBot
    for (i in 0..4) {
        val v = visTempTop - visTempSpan * i / 4
        val label = tUnit.format(v)
        val result = textMeasurer.measure(AnnotatedString(label), TextStyle(fontSize = 13.sp, color = ColTemp))
        val y = marginTop + baseH * i / 4
        scope.drawText(result, topLeft = Offset(marginLeft + baseW + 4f, y - result.size.height / 2f))
    }

    // 시간 기준 X축
    val sorted = records.sortedBy { it.dateTime }
    val timeStart = sorted.first().dateTime.toEpochSecond(java.time.ZoneOffset.UTC)
    val timeEnd = sorted.last().dateTime.toEpochSecond(java.time.ZoneOffset.UTC)
    val timeSpan = if (timeEnd > timeStart) (timeEnd - timeStart).toFloat() else 1f

    val lightPoints = mutableListOf<Offset>()
    val heavyPoints = mutableListOf<Offset>()
    val tempPoints = mutableListOf<Offset>()

    for (r in sorted) {
        val t = r.dateTime.toEpochSecond(java.time.ZoneOffset.UTC)
        val x = marginLeft + offsetX + chartW * (t - timeStart) / timeSpan
        val lightY = marginTop + offsetY + chartH - ((r.dst * 0.01 - levelMin) / levelSpan * chartH).toFloat()
        val heavyY = marginTop + offsetY + chartH - ((r.eeaD * 0.01 - levelMin) / levelSpan * chartH).toFloat()
        val tempY = marginTop + offsetY + chartH - ((r.temperature - tempMin) / tempSpan * chartH).toFloat()
        lightPoints.add(Offset(x, lightY))
        heavyPoints.add(Offset(x, heavyY))
        tempPoints.add(Offset(x, tempY))
    }

    // Clip trend lines to the chart area so they never spill into the Y-axis
    // label margin or the right margin.
    scope.clipRect(marginLeft, marginTop, marginLeft + baseW, marginTop + chartH) {
        // Heavy 선 (주황, 반투명)
        if (heavyPoints.size >= 2) {
            val path = Path()
            path.moveTo(heavyPoints[0].x, heavyPoints[0].y)
            for (i in 1 until heavyPoints.size) path.lineTo(heavyPoints[i].x, heavyPoints[i].y)
            drawPath(path, ColHeavy.copy(alpha = 0.6f), style = Stroke(width = 4f, cap = StrokeCap.Round, join = StrokeJoin.Round))
        }

        // Light 선 (회색, 반투명)
        if (lightPoints.size >= 2) {
            val path = Path()
            path.moveTo(lightPoints[0].x, lightPoints[0].y)
            for (i in 1 until lightPoints.size) path.lineTo(lightPoints[i].x, lightPoints[i].y)
            drawPath(path, ColLight.copy(alpha = 0.6f), style = Stroke(width = 4f, cap = StrokeCap.Round, join = StrokeJoin.Round))
        }

        // Temperature 선 (빨강, 반투명 얇게)
        if (tempPoints.size >= 2) {
            val path = Path()
            path.moveTo(tempPoints[0].x, tempPoints[0].y)
            for (i in 1 until tempPoints.size) path.lineTo(tempPoints[i].x, tempPoints[i].y)
            drawPath(path, ColTemp.copy(alpha = 0.5f), style = Stroke(width = 2f, cap = StrokeCap.Round, join = StrokeJoin.Round))
        }
    }


    // X축 라벨 + 눈금 (visible time range 기반)
    val visTimeFracL = -offsetX / chartW
    val visTimeFracR = (baseW - offsetX) / chartW
    val visTimeStart = timeStart + (visTimeFracL * timeSpan).toLong()
    val visTimeEnd = timeStart + (visTimeFracR * timeSpan).toLong()

    val labelCount = min(5, sorted.size)
    if (labelCount > 1) {
        val xInset = 20f
        val visTimeSpanL = visTimeEnd - visTimeStart
        for (i in 0 until labelCount) {
            val t = visTimeStart + visTimeSpanL * i / (labelCount - 1)
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
                (x - result.size.width / 2).coerceIn(marginLeft, marginLeft + baseW - result.size.width),
                marginTop + baseH + 20f
            ))
        }
    }

    // 터치 크로스헤어 + 툴팁
    if (touchPos != null && sorted.isNotEmpty()) {
        var nearestIdx = 0; var nearestDist = Float.MAX_VALUE
        for (i in lightPoints.indices) {
            val dist = abs(lightPoints[i].x - touchPos.x)
            if (dist < nearestDist) { nearestDist = dist; nearestIdx = i }
        }
        val lp = lightPoints[nearestIdx]
        val hp = heavyPoints[nearestIdx]
        val tp = tempPoints[nearestIdx]
        val rec = sorted[nearestIdx]

        scope.drawLine(Color(0x66888888), Offset(lp.x, marginTop), Offset(lp.x, marginTop + baseH), strokeWidth = 1f)
        scope.drawLine(Color(0x66888888), Offset(marginLeft, lp.y), Offset(marginLeft + baseW, lp.y), strokeWidth = 0.5f)

        scope.drawCircle(ColLight, 6f, lp); scope.drawCircle(Color.White, 3.5f, lp)
        scope.drawCircle(ColHeavy, 6f, hp); scope.drawCircle(Color.White, 3.5f, hp)
        scope.drawCircle(ColTemp, 5f, tp); scope.drawCircle(Color.White, 3f, tp)

        val dt = rec.dateTime

        // 시간
        val timeTxt = textMeasurer.measure(
            AnnotatedString("%04d/%02d/%02d  %02d:%02d:%02d".format(dt.year, dt.monthValue, dt.dayOfMonth, dt.hour, dt.minute, dt.second)),
            TextStyle(fontSize = 12.sp, color = Color(0xFFAAAAAA), fontWeight = FontWeight.Medium)
        )
        // Light
        val lTxt = textMeasurer.measure(
            AnnotatedString("Light  %.2f".format(rec.dst * 0.01)),
            TextStyle(fontSize = 13.sp, color = ColLight, fontWeight = FontWeight.Bold)
        )
        // Heavy
        val hTxt = textMeasurer.measure(
            AnnotatedString("Heavy  %.2f".format(rec.eeaD * 0.01)),
            TextStyle(fontSize = 13.sp, color = ColHeavy, fontWeight = FontWeight.Bold)
        )
        // Temp
        val tTxt = textMeasurer.measure(
            AnnotatedString("Temp  ${tUnit.format(rec.temperature)}"),
            TextStyle(fontSize = 13.sp, color = ColTemp, fontWeight = FontWeight.Bold)
        )

        val boxW = maxOf(timeTxt.size.width, lTxt.size.width + hTxt.size.width + tTxt.size.width + 48).toFloat() + 24f
        val boxH = timeTxt.size.height + lTxt.size.height + 16f
        val bx = ((totalW - boxW) / 2).coerceAtLeast(0f)
        val by = 2f

        scope.drawRoundRect(Color(0xF0FFFFFF), topLeft = Offset(bx, by),
            size = androidx.compose.ui.geometry.Size(boxW, boxH),
            cornerRadius = androidx.compose.ui.geometry.CornerRadius(12f, 12f))
        scope.drawRoundRect(Color(0x22000000), topLeft = Offset(bx, by),
            size = androidx.compose.ui.geometry.Size(boxW, boxH),
            cornerRadius = androidx.compose.ui.geometry.CornerRadius(12f, 12f),
            style = Stroke(width = 1f))

        scope.drawText(timeTxt, topLeft = Offset(bx + (boxW - timeTxt.size.width) / 2, by + 4f))
        val valY = by + timeTxt.size.height + 8f
        scope.drawText(lTxt, topLeft = Offset(bx + 12f, valY))
        scope.drawText(hTxt, topLeft = Offset(bx + (boxW - hTxt.size.width) / 2, valY))
        scope.drawText(tTxt, topLeft = Offset(bx + boxW - tTxt.size.width - 12f, valY))
    }
}
