package com.wws2.densitymeter.ui.screen

import android.content.Context
import android.util.Log
import androidx.compose.foundation.background
import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.lazy.rememberLazyListState
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.automirrored.filled.ArrowBackIos
import androidx.compose.material.icons.automirrored.filled.Send
import androidx.compose.material3.*
import androidx.compose.runtime.*
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.draw.shadow
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.graphics.Brush
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.wws2.densitymeter.ui.theme.AppColors
import androidx.lifecycle.compose.collectAsStateWithLifecycle
import com.wws2.densitymeter.viewmodel.MainViewModel
import com.wws2.densitymeter.viewmodel.MainUiState
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import org.json.JSONArray
import org.json.JSONObject
import java.net.HttpURLConnection
import java.net.URL
import kotlin.math.sqrt
import kotlin.math.max
import kotlin.math.min
import kotlin.math.abs
import com.wws2.densitymeter.model.InterfaceEchoReading
import com.wws2.densitymeter.model.EchoReading
import com.wws2.densitymeter.BuildConfig

private const val TAG = "Chatbot"
private val OPENAI_KEY = BuildConfig.OPENAI_API_KEY

private val PRODUCTS = listOf("ENV200", "ENV130", "ENV120")
private val PRODUCT_ASSET = mapOf("ENV200" to "rag_density.json", "ENV130" to "rag_interface.json", "ENV120" to "rag_interface_120.json")

data class LangConfig(val greeting: String, val placeholder: String, val langRule: String, val unknown: String)

private val LANGUAGES = mapOf(
    "English" to LangConfig(
        "Hello!",
        "Type your question...",
        "You must answer only in English. Keep product names and model names as-is.",
        "The requested information could not be found. Please contact support at 041-584-8820.",
    ),
    "Korean" to LangConfig(
        "안녕하세요! 제품에 대해 궁금한 점을 물어보세요.",
        "질문을 입력하세요...",
        "반드시 한국어로만 답변하세요. 제품명, 모델명 등 고유명사만 영어 그대로 사용하세요.",
        "해당 정보는 확인되지 않습니다. 추가 문의는 고객지원(041-584-8820)으로 연락해주세요.",
    ),
    "Japanese" to LangConfig(
        "こんにちは！製品についてお気軽にご質問ください。",
        "質問を入力してください...",
        "必ず日本語のみで回答してください。製品名・モデル名はそのまま英語で使用してください。",
        "該当情報は確認できませんでした。詳細はサポート(041-584-8820)までお問い合わせください。",
    ),
    "Chinese" to LangConfig(
        "您好！欢迎咨询产品相关问题。",
        "请输入您的问题...",
        "必须仅用中文回答。产品名称和型号保持英文原样。",
        "未找到相关信息。如需进一步咨询，请联系客服(041-584-8820)。",
    ),
    "Spanish" to LangConfig(
        "Hola! Pregunteme sobre los productos.",
        "Escriba su pregunta...",
        "Debes responder solo en espanol. Manten los nombres de productos y modelos en su forma original.",
        "No se encontro la informacion solicitada. Contacte al soporte al 041-584-8820.",
    ),
    "German" to LangConfig(
        "Hallo! Fragen Sie mich zu den Produkten.",
        "Geben Sie Ihre Frage ein...",
        "Sie muessen ausschliesslich auf Deutsch antworten. Produkt- und Modellnamen bleiben in der Originalform (Englisch).",
        "Die angeforderten Informationen konnten nicht gefunden werden. Bitte wenden Sie sich an den Support unter 041-584-8820.",
    ),
)

// ─── RAG: 벡터 데이터 캐시 ───
data class RagChunk(val text: String, val embedding: FloatArray)

private val ragCache = mutableMapOf<String, List<RagChunk>>()

private fun loadRagData(context: Context, product: String): List<RagChunk> {
    ragCache[product]?.let { return it }
    val asset = PRODUCT_ASSET[product] ?: return emptyList()
    return try {
        val json = context.assets.open(asset).bufferedReader().readText()
        val arr = JSONArray(json)
        val chunks = mutableListOf<RagChunk>()
        for (i in 0 until arr.length()) {
            val obj = arr.getJSONObject(i)
            val text = obj.getString("text")
            val embArr = obj.getJSONArray("embedding")
            val emb = FloatArray(embArr.length()) { embArr.getDouble(it).toFloat() }
            chunks.add(RagChunk(text, emb))
        }
        ragCache[product] = chunks
        Log.d(TAG, "RAG loaded: $product = ${chunks.size} chunks")
        chunks
    } catch (e: Exception) {
        Log.e(TAG, "RAG load failed: ${e.message}")
        emptyList()
    }
}

private fun cosineSimilarity(a: FloatArray, b: FloatArray): Float {
    var dot = 0f; var normA = 0f; var normB = 0f
    for (i in a.indices) { dot += a[i] * b[i]; normA += a[i] * a[i]; normB += b[i] * b[i] }
    val denom = sqrt(normA) * sqrt(normB)
    return if (denom > 0f) dot / denom else 0f
}

private fun searchSimilar(query: FloatArray, chunks: List<RagChunk>, topK: Int = 15): List<String> {
    return chunks.map { it to cosineSimilarity(query, it.embedding) }
        .sortedByDescending { it.second }
        .take(topK)
        .map { it.first.text }
}

data class ChatMessage(val role: String, val content: String)

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun ChatbotScreen(onBack: () -> Unit, vm: MainViewModel) {
    val context = LocalContext.current
    val state by vm.state.collectAsStateWithLifecycle()
    var selectedProduct by remember { mutableStateOf(PRODUCTS[0]) }
    var selectedLang by remember { mutableStateOf("English") }
    var langConfig by remember { mutableStateOf(LANGUAGES["English"]!!) }
    var messages by remember { mutableStateOf(listOf(ChatMessage("assistant", LANGUAGES["English"]!!.greeting))) }
    var input by remember { mutableStateOf("") }
    var isLoading by remember { mutableStateOf(false) }
    var productExpanded by remember { mutableStateOf(false) }
    var langExpanded by remember { mutableStateOf(false) }
    val scope = rememberCoroutineScope()
    val listState = rememberLazyListState()

    LaunchedEffect(messages.size) {
        if (messages.isNotEmpty()) listState.animateScrollToItem(messages.size - 1)
    }

    Column(modifier = Modifier.fillMaxSize().background(AppColors.Background)) {
        // Header
        Row(
            modifier = Modifier.fillMaxWidth().background(AppColors.White).padding(horizontal = 8.dp, vertical = 12.dp),
            verticalAlignment = Alignment.CenterVertically,
        ) {
            IconButton(onClick = onBack) {
                Icon(Icons.AutoMirrored.Filled.ArrowBackIos, contentDescription = "Back", tint = AppColors.DarkText)
            }
            Text("AI Chatbot", fontSize = 20.sp, fontWeight = FontWeight.W700, color = AppColors.DarkText)
        }

        // Product / Language
        Row(
            modifier = Modifier.fillMaxWidth().background(AppColors.White).padding(horizontal = 12.dp, vertical = 4.dp),
            horizontalArrangement = Arrangement.spacedBy(8.dp),
        ) {
            ExposedDropdownMenuBox(expanded = productExpanded, onExpandedChange = { productExpanded = it }, modifier = Modifier.weight(1f)) {
                OutlinedTextField(value = selectedProduct, onValueChange = {}, readOnly = true,
                    label = { Text("Product", fontSize = 12.sp) },
                    trailingIcon = { ExposedDropdownMenuDefaults.TrailingIcon(expanded = productExpanded) },
                    modifier = Modifier.menuAnchor().fillMaxWidth(),
                    textStyle = androidx.compose.ui.text.TextStyle(fontSize = 13.sp), singleLine = true)
                ExposedDropdownMenu(expanded = productExpanded, onDismissRequest = { productExpanded = false }) {
                    PRODUCTS.forEach { p ->
                        DropdownMenuItem(text = { Text(p, fontSize = 13.sp) }, onClick = {
                            selectedProduct = p; productExpanded = false
                            messages = listOf(ChatMessage("assistant", langConfig.greeting))
                        })
                    }
                }
            }
            ExposedDropdownMenuBox(expanded = langExpanded, onExpandedChange = { langExpanded = it }, modifier = Modifier.weight(1f)) {
                OutlinedTextField(value = selectedLang, onValueChange = {}, readOnly = true,
                    label = { Text("Language", fontSize = 12.sp) },
                    trailingIcon = { ExposedDropdownMenuDefaults.TrailingIcon(expanded = langExpanded) },
                    modifier = Modifier.menuAnchor().fillMaxWidth(),
                    textStyle = androidx.compose.ui.text.TextStyle(fontSize = 13.sp), singleLine = true)
                ExposedDropdownMenu(expanded = langExpanded, onDismissRequest = { langExpanded = false }) {
                    LANGUAGES.keys.forEach { lang ->
                        DropdownMenuItem(text = { Text(lang, fontSize = 13.sp) }, onClick = {
                            selectedLang = lang; langConfig = LANGUAGES[lang]!!; langExpanded = false
                            messages = listOf(ChatMessage("assistant", LANGUAGES[lang]!!.greeting))
                        })
                    }
                }
            }
        }

        // Messages
        LazyColumn(
            state = listState, modifier = Modifier.weight(1f).fillMaxWidth().padding(horizontal = 12.dp),
            verticalArrangement = Arrangement.spacedBy(8.dp), contentPadding = PaddingValues(vertical = 12.dp),
        ) {
            items(messages) { msg -> ChatBubble(msg) }
            if (isLoading) {
                item {
                    Row(modifier = Modifier.padding(start = 8.dp, top = 4.dp)) {
                        CircularProgressIndicator(modifier = Modifier.size(20.dp), strokeWidth = 2.dp, color = AppColors.Primary)
                        Spacer(Modifier.width(8.dp))
                        Text("Generating...", fontSize = 14.sp, color = AppColors.GrayLabel)
                    }
                }
            }
        }

        // Input
        Row(
            modifier = Modifier.fillMaxWidth().background(AppColors.White).padding(horizontal = 12.dp, vertical = 8.dp),
            verticalAlignment = Alignment.CenterVertically,
        ) {
            OutlinedTextField(value = input, onValueChange = { input = it }, modifier = Modifier.weight(1f),
                placeholder = { Text(langConfig.placeholder, fontSize = 15.sp) },
                shape = RoundedCornerShape(24.dp), singleLine = false, maxLines = 4)
            Spacer(Modifier.width(8.dp))
            IconButton(
                onClick = {
                    val question = input.trim()
                    if (question.isNotEmpty() && !isLoading) {
                        input = ""
                        messages = messages + ChatMessage("user", question)
                        isLoading = true
                        scope.launch {
                            val hasTrend = state.trendRecords.isNotEmpty()
                            val measurementData = buildMeasurementData(state)
                            val answer = callOpenAIWithRAG(context, question, messages, selectedProduct, langConfig, measurementData, hasTrend)
                            messages = messages + ChatMessage("assistant", answer)
                            isLoading = false
                        }
                    }
                },
                enabled = input.isNotBlank() && !isLoading,
                modifier = Modifier.size(44.dp).clip(CircleShape)
                    .background(
                        if (input.isNotBlank() && !isLoading)
                            Brush.linearGradient(listOf(Color(0xFF3182F6), Color(0xFF7C3AED)))
                        else Brush.linearGradient(listOf(AppColors.LightGray, AppColors.LightGray)),
                        CircleShape,
                    ),
            ) {
                Icon(Icons.AutoMirrored.Filled.Send, contentDescription = "Send",
                    tint = if (input.isNotBlank() && !isLoading) AppColors.White else AppColors.GrayLabel,
                    modifier = Modifier.size(22.dp))
            }
        }
    }
}

// ─── 바텀시트용 AI 챗봇 콘텐츠 (HTML 프로토타입 스타일) ───
@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun ChatbotSheetContent(vm: MainViewModel, modifier: Modifier = Modifier) {
    val context = LocalContext.current
    val state by vm.state.collectAsStateWithLifecycle()
    var selectedLang by remember { mutableStateOf("English") }
    var langExpanded by remember { mutableStateOf(false) }
    var langConfig by remember { mutableStateOf(LANGUAGES["English"]!!) }
    val selectedProduct = remember(state.activeDeviceLabel) {
        when {
            state.activeDeviceLabel.startsWith("ENV130") -> "ENV130"
            state.activeDeviceLabel.startsWith("ENV120") -> "ENV120"
            else -> "ENV200"
        }
    }
    var messages by remember { mutableStateOf(listOf(ChatMessage("assistant", LANGUAGES["English"]!!.greeting))) }
    var input by remember { mutableStateOf("") }
    var isLoading by remember { mutableStateOf(false) }
    val scope = rememberCoroutineScope()
    val listState = rememberLazyListState()

    LaunchedEffect(messages.size) {
        if (messages.isNotEmpty()) listState.animateScrollToItem(messages.size - 1)
    }

    Column(modifier = modifier.fillMaxWidth()) {
        // Header: language selector only (WESS-AI title removed)
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .padding(horizontal = 12.dp, vertical = 2.dp),
            verticalAlignment = Alignment.CenterVertically,
        ) {
            ExposedDropdownMenuBox(
                expanded = langExpanded,
                onExpandedChange = { langExpanded = it },
                modifier = Modifier.width(110.dp),
            ) {
                OutlinedTextField(
                    value = selectedLang,
                    onValueChange = {},
                    readOnly = true,
                    label = { Text("Language", fontSize = 10.sp) },
                    trailingIcon = { ExposedDropdownMenuDefaults.TrailingIcon(expanded = langExpanded) },
                    modifier = Modifier.menuAnchor().fillMaxWidth(),
                    textStyle = androidx.compose.ui.text.TextStyle(fontSize = 12.sp),
                    singleLine = true,
                )
                ExposedDropdownMenu(
                    expanded = langExpanded,
                    onDismissRequest = { langExpanded = false },
                ) {
                    LANGUAGES.keys.forEach { lang ->
                        DropdownMenuItem(
                            text = { Text(lang, fontSize = 12.sp) },
                            onClick = {
                                selectedLang = lang
                                langConfig = LANGUAGES[lang]!!
                                langExpanded = false
                                messages = listOf(ChatMessage("assistant", LANGUAGES[lang]!!.greeting))
                            },
                        )
                    }
                }
            }
        }

        // Messages
        LazyColumn(
            state = listState,
            modifier = Modifier.weight(1f).fillMaxWidth().padding(horizontal = 16.dp),
            verticalArrangement = Arrangement.spacedBy(10.dp),
            contentPadding = PaddingValues(vertical = 8.dp),
        ) {
            items(messages) { msg -> ChatBubble(msg) }
            if (isLoading) {
                item {
                    Row(modifier = Modifier.padding(start = 8.dp, top = 4.dp)) {
                        CircularProgressIndicator(modifier = Modifier.size(18.dp), strokeWidth = 2.dp, color = Color(0xFF7C3AED))
                        Spacer(Modifier.width(8.dp))
                        Text("Generating...", fontSize = 13.sp, color = AppColors.GrayLabel)
                    }
                }
            }
        }

        // Input bar
        Row(
            modifier = Modifier
                .fillMaxWidth()
                .background(AppColors.White)
                .padding(horizontal = 12.dp, vertical = 8.dp),
            verticalAlignment = Alignment.CenterVertically,
        ) {
            OutlinedTextField(
                value = input,
                onValueChange = { input = it },
                modifier = Modifier.weight(1f),
                placeholder = { Text("Ask a question...", fontSize = 13.sp) },
                shape = RoundedCornerShape(22.dp),
                singleLine = false,
                maxLines = 3,
                textStyle = androidx.compose.ui.text.TextStyle(fontSize = 13.sp),
                colors = OutlinedTextFieldDefaults.colors(
                    unfocusedContainerColor = AppColors.LightGray,
                    focusedContainerColor = AppColors.White,
                    unfocusedBorderColor = AppColors.Border,
                    focusedBorderColor = AppColors.Primary,
                ),
            )
            Spacer(Modifier.width(8.dp))
            IconButton(
                onClick = {
                    val question = input.trim()
                    if (question.isNotEmpty() && !isLoading) {
                        input = ""
                        messages = messages + ChatMessage("user", question)
                        isLoading = true
                        scope.launch {
                            val hasTrend = state.trendRecords.isNotEmpty()
                            val measurementData = buildMeasurementData(state)
                            val answer = callOpenAIWithRAG(context, question, messages, selectedProduct, langConfig, measurementData, hasTrend)
                            messages = messages + ChatMessage("assistant", answer)
                            isLoading = false
                        }
                    }
                },
                enabled = input.isNotBlank() && !isLoading,
                modifier = Modifier.size(34.dp).clip(CircleShape)
                    .background(
                        if (input.isNotBlank() && !isLoading)
                            Brush.linearGradient(listOf(Color(0xFF3182F6), Color(0xFF7C3AED)))
                        else Brush.linearGradient(listOf(AppColors.LightGray, AppColors.LightGray)),
                        CircleShape,
                    ),
            ) {
                Icon(Icons.AutoMirrored.Filled.Send, contentDescription = "Send",
                    tint = if (input.isNotBlank() && !isLoading) AppColors.White else AppColors.GrayLabel,
                    modifier = Modifier.size(15.dp))
            }
        }
    }
}

private val AiGradient = Brush.linearGradient(
    colors = listOf(Color(0xFF3182F6), Color(0xFF7C3AED)),
    start = Offset(0f, 0f),
    end = Offset(400f, 400f),
)

@Composable
internal fun ChatBubble(msg: ChatMessage) {
    val isUser = msg.role == "user"
    Column(
        modifier = Modifier.fillMaxWidth(),
        horizontalAlignment = if (isUser) Alignment.End else Alignment.Start,
    ) {
        Box(
            modifier = Modifier
                .widthIn(max = 300.dp)
                .shadow(2.dp, RoundedCornerShape(18.dp))
                .then(
                    if (isUser) Modifier.background(AiGradient, RoundedCornerShape(18.dp))
                    else Modifier.background(AppColors.LightGray, RoundedCornerShape(18.dp))
                )
                .padding(horizontal = 14.dp, vertical = 10.dp),
        ) {
            Text(msg.content, fontSize = 14.sp, color = if (isUser) Color.White else AppColors.DarkText, lineHeight = 21.sp)
        }
    }
}

// ─── 시스템 프롬프트 (Streamlit app.py와 동일) ───
private fun buildSystemPrompt(product: String, langConfig: LangConfig, context: String, measurementData: String): String {
    val commonRules = """How to answer:
1. Cross-reference multiple documents to ensure consistency before answering.
2. Even if the exact answer is not directly stated, infer and reason based on related information. Provide practical tips.
3. Provide step-by-step procedures that can be followed immediately.
4. Think deeply before answering. Consider the context, related parameters, and potential issues.
5. If the answer is ambiguous, say: 'This may not be accurate. Further verification is needed.'
6. If documents contain conflicting information, note that 'versions may differ'.

Rules:
- Never reference table/figure/chapter numbers like 'Table 3-3', 'Figure 2.1', 'Chapter 5'. The customer does not have the manual.
- Explain the content directly instead.
- But always try your best to find related information and provide a helpful answer before giving up.
- CRITICAL LANGUAGE RULE (HIGHEST PRIORITY, OVERRIDES EVERYTHING ELSE):
  ${langConfig.langRule}
  * IGNORE the language of the user's message. Even if the user writes in a different language, you MUST respond ONLY in the language specified above.
  * NEVER mix languages in a single response. Always keep product names and model names in English as-is.
- If truly no relevant information exists, respond using the fallback phrase in the required language: '${langConfig.unknown}'
"""

    val env200Terms = """
Product-specific terminology rules (ENV200 - Density Meter):
- Use these terms: EEA, Detection Area, Density, Damping, Pipe Diameter, Calibration, AGC, Profile, Clamp-on, Spool-piece
- Units: %, ppm, mg/L, g/L
- Calibration: multi-point calibration (EEA - Density)
- Channel: single
- DO NOT use these terms (they belong to interface meters): Threshold, Echo AMP, ASF, Light/Heavy, Level/Distance, m/ft, CH1/CH2
"""

    val env130Terms = """
Product-specific terminology rules (ENV130 - Interface Meter):
- Use these terms: Threshold, Echo AMP, ASF, Light/Heavy, Damping, Level/Distance, Echo, CH1/CH2
- Units: m, ft
- Channel: dual (CH1/CH2)
- DO NOT use these terms (they belong to density meters): EEA, Detection Area, Pipe Diameter, AGC, Profile, Clamp-on, Spool-piece, %, ppm, mg/L, g/L
- CRITICAL: This product is a "계면계" (interface meter), NOT "수위계" (level meter). NEVER use the word "수위" or "수위계". Always use "계면" or "계면계" when referring to this product in Korean. In English, use "interface" not "level meter".
"""

    val env120Terms = """
Product-specific terminology rules (ENV120 - Interface Meter):
- Use these terms: Threshold, Echo AMP, ASF, Damping, Level/Distance, Echo
- Units: m, ft
- Channel: single
- DO NOT use these terms: EEA, Detection Area, Pipe Diameter, AGC, Profile, Clamp-on, Spool-piece, Light/Heavy, CH1/CH2, %, ppm, mg/L, g/L
- CRITICAL: This product is a "계면계" (interface meter), NOT "수위계" (level meter). NEVER use the word "수위" or "수위계". Always use "계면" or "계면계" when referring to this product in Korean. In English, use "interface" not "level meter".
"""

    val diagnosisGuide = """

[Response Rules]
- Do NOT explain what the product is. The user already knows their device.
- Get straight to the point and focus on the question asked.

[Diagnosis Function — DISABLED]
- Do NOT perform diagnostic reasoning based on measurement values.
- Do NOT interpret error codes (ST00, ST01, ST02, ST03, ST10, ER01, ER02, etc.)
  even if the user asks. Reply that diagnostic interpretation is not supported yet.
- Do NOT suggest specific setting changes (Echo AMP, Threshold, ASF, Damping, etc.)
  based on current measurement values.
- Do NOT judge signal quality, waveform, or measurement health.
- If the user asks diagnosis-style questions, answer with general product information
  from the documents only, and suggest they contact support for diagnostic help.
"""

    val productPrompt = when (product) {
        "ENV200" -> "You are a product support specialist for ultrasonic sludge density meter (ENV200).\n\n$commonRules$diagnosisGuide\n$env200Terms"
        "ENV130" -> "You are a product support specialist for ultrasonic sludge interface meter (ENV130).\n\n$commonRules$diagnosisGuide\n$env130Terms"
        "ENV120" -> {
            // ENV120 전용 상세 프롬프트 (Streamlit과 동일)
            """You are a product support specialist with deep field experience in ultrasonic sludge interface meters (ENV120).
You have extensive knowledge of installation, calibration, troubleshooting, and field operation.

How to answer:
1. Thoroughly analyze ALL the product documents provided below before answering. Cross-reference multiple documents to ensure consistency.
2. Combine and synthesize information from multiple documents to give comprehensive, practical answers.
3. Even if the exact answer is not directly stated, infer and reason based on related information. Provide practical field tips.
4. Provide step-by-step procedures that a field engineer can follow immediately.
5. When relevant, include recommended values, typical ranges, and real-world tips from field experience.
6. If the question is about settings, explain both HOW to access the menu (button sequence) AND what values to set.
7. Think deeply before answering. Consider the context, related parameters, and potential issues.
8. For measurement error questions, emphasize that Echo AMP should be checked before Threshold.
9. For relay questions, always clarify R1/R2 contact open/close conditions to prevent confusion.
10. Use clear option names (Threshold, ASF, Echo AMP, etc.) to aid understanding.

Rules:
- Never reference table/figure/chapter numbers.
- Explain the content directly instead.
- If documents contain conflicting information, note that 'versions may differ'.
- Do not use the term 'TVG' unless the user specifically asks about it.
- CRITICAL LANGUAGE RULE (HIGHEST PRIORITY, OVERRIDES EVERYTHING ELSE):
  ${langConfig.langRule}
  * IGNORE the language of the user's message. Even if the user writes in a different language, you MUST respond ONLY in the language specified above.
  * NEVER mix languages in a single response. Always keep product names and model names in English as-is.
- If truly no relevant information exists, respond using the fallback phrase in the required language: '${langConfig.unknown}'
- If the answer is ambiguous, say: 'This may not be accurate. Further verification is needed.'
- But always try your best to find related information and provide a helpful answer before giving up.
$diagnosisGuide
$env120Terms"""
        }
        else -> "You are a product support specialist.\n\n$commonRules$diagnosisGuide"
    }

    return "$productPrompt\n\n[App Screen Data — use ONLY these values for diagnosis and answers]\nThese are the values currently shown to the user on the app screens (Main / Echo / Param / Trend tabs). Do not infer raw BLE payloads or hidden internal data — base your analysis only on the values listed below.\n$measurementData\n\n[Product Documents - Reference when needed]\n$context"
}

// ─── OpenAI 임베딩 API ───
private fun getEmbedding(text: String): FloatArray? {
    return try {
        val url = URL("https://api.openai.com/v1/embeddings")
        val conn = url.openConnection() as HttpURLConnection
        conn.requestMethod = "POST"
        conn.setRequestProperty("Content-Type", "application/json")
        conn.setRequestProperty("Authorization", "Bearer $OPENAI_KEY")
        conn.connectTimeout = 15000
        conn.readTimeout = 15000
        conn.doOutput = true

        val body = JSONObject()
        body.put("model", "text-embedding-3-small")
        body.put("input", text)
        conn.outputStream.use { it.write(body.toString().toByteArray()) }

        if (conn.responseCode == 200) {
            val resp = conn.inputStream.bufferedReader().readText()
            val embArr = JSONObject(resp).getJSONArray("data").getJSONObject(0).getJSONArray("embedding")
            FloatArray(embArr.length()) { embArr.getDouble(it).toFloat() }
        } else null
    } catch (e: Exception) {
        Log.e(TAG, "Embedding failed: ${e.message}")
        null
    }
}

// ─── 농도계 파형 분석 ───
private fun analyzeDensityWaveform(echo: EchoReading, reading: com.wws2.densitymeter.model.DeviceReading?): String {
    val wave = echo.rawWave
    if (wave.isEmpty()) return "- Waveform: NO DATA"

    // Detection Area 내 신호 분석
    val loIdx = echo.detAreaLO
    val hiIdx = min(echo.detAreaHI, wave.size - 1)
    val inZone = if (loIdx < hiIdx) wave.subList(loIdx, hiIdx + 1) else wave
    val outZone = wave.filterIndexed { i, _ -> i < loIdx || i > hiIdx }

    val zoneMax = inZone.max()
    val zoneAvg = inZone.average()
    val outAvg = if (outZone.isNotEmpty()) outZone.average() else 0.0

    val signalQuality = when {
        zoneMax < 500   -> "VERY_WEAK (매우 약함)"
        zoneMax < 2000  -> "WEAK (약함)"
        zoneMax < 10000 -> "FAIR (보통)"
        zoneMax < 30000 -> "GOOD (양호)"
        else            -> "STRONG (강함)"
    }

    // EEA 안정성 (eeaR vs eeaD 차이)
    val eeaDiff = abs(echo.eeaR - echo.eeaD)
    val eeaStability = when {
        eeaDiff < 500  -> "STABLE (안정)"
        eeaDiff < 2000 -> "MODERATE (보통)"
        else           -> "UNSTABLE (불안정)"
    }

    // Detection Area 외부 노이즈
    val noiseRatio = if (zoneAvg > 0) outAvg / zoneAvg else 0.0

    // 자동 진단
    val issues = mutableListOf<String>()

    if (zoneMax < 500) {
        issues.add("CRITICAL: Detection Area 내 신호 매우 약함 → 센서 설치 상태 확인, 배관 내 유체 확인")
    } else if (zoneMax < 2000) {
        issues.add("WARNING: Detection Area 내 신호 약함 → 센서 위치/커플링 확인")
    }

    if (echo.eeaR == 0 && echo.eeaD == 0) {
        issues.add("CRITICAL: EEA 값 0 → 수신 신호 없음, 센서 연결 및 배관 확인")
    }

    if (eeaDiff > 2000) {
        issues.add("WARNING: EEA 불안정 (Real=${echo.eeaR}, Damped=${echo.eeaD}, 차이=$eeaDiff) → Damping 값 올리기 권장")
    }

    if (noiseRatio > 0.5) {
        issues.add("WARNING: Detection Area 외부 노이즈 높음 (비율 ${String.format("%.1f", noiseRatio * 100)}%) → Detection Area 범위 재조정")
    }

    val errorMsg = when (reading?.errorCode ?: 0) {
        0    -> "정상"
        0x01 -> "ER01: 에러 지속 — 센서/환경 점검 필요"
        0x02 -> "ER02: 온도 센서 이상 — 온도 센서 케이블 확인"
        else -> "Unknown (0x${(reading?.errorCode ?: 0).toString(16)})"
    }

    return buildString {
        appendLine("=== Waveform Analysis (Density) ===")
        appendLine("- Detection Area: index $loIdx ~ $hiIdx (${hiIdx - loIdx + 1} points)")
        appendLine("- Signal Max in Zone: $zoneMax / 65535")
        appendLine("- Signal Quality: $signalQuality")
        appendLine("- Zone Average: ${String.format("%.0f", zoneAvg)}")
        appendLine("- Outside Noise Avg: ${String.format("%.0f", outAvg)}")
        appendLine("- Noise Ratio: ${String.format("%.1f", noiseRatio * 100)}%")
        appendLine("- EEA Real: ${echo.eeaR}, EEA Damped: ${echo.eeaD}")
        appendLine("- EEA Stability: $eeaStability (diff=$eeaDiff)")
        appendLine("- Error Status: $errorMsg")
        appendLine("")
        if (issues.isNotEmpty()) {
            appendLine("=== Auto-Diagnosis ===")
            issues.forEach { appendLine("- $it") }
        } else {
            appendLine("=== Auto-Diagnosis ===")
            appendLine("- OK: 파형 정상, 특이사항 없음")
        }
    }
}

// ─── 계면계 파형 분석 ───
private fun analyzeWaveform(echo: InterfaceEchoReading): String {
    val wave = echo.wave
    if (wave.isEmpty()) return "- Waveform: NO DATA"

    val maxAmp = wave.max()
    val avgAmp = wave.average()
    val sorted = wave.sorted()
    val noiseFloor = sorted.take(max(1, wave.size / 2)).average()
    val snr = if (noiseFloor > 1.0) maxAmp / noiseFloor else maxAmp.toDouble()

    // 피크 검출 (로컬 최대, threshold 이상)
    val peakThreshold = max(200, (avgAmp * 2.5).toInt())
    data class Peak(val index: Int, val amp: Int)
    val peaks = mutableListOf<Peak>()
    for (i in 2 until wave.size - 2) {
        if (wave[i] > peakThreshold && wave[i] >= wave[i-1] && wave[i] >= wave[i+1]
            && wave[i] >= wave[i-2] && wave[i] >= wave[i+2]) {
            if (peaks.isEmpty() || i - peaks.last().index > 5) {
                peaks.add(Peak(i, wave[i]))
            }
        }
    }
    peaks.sortByDescending { it.amp }

    val signalQuality = when {
        maxAmp < 100  -> "NONE (신호 없음)"
        maxAmp < 300  -> "VERY_WEAK (매우 약함)"
        maxAmp < 700  -> "WEAK (약함)"
        maxAmp < 1500 -> "FAIR (보통)"
        maxAmp < 3000 -> "GOOD (양호)"
        else          -> "STRONG (강함)"
    }

    val noiseLevel = when {
        noiseFloor < 30  -> "CLEAN (깨끗)"
        noiseFloor < 80  -> "LOW (적음)"
        noiseFloor < 200 -> "MODERATE (보통)"
        else             -> "HIGH (노이즈 많음)"
    }

    // Threshold 분석
    val thrLightDetected = echo.thrLightDist > 0
    val thrHeavyDetected = echo.thrHeavyDist > 0
    val thrLightEffective = if (echo.thrLightMode == 0) "Auto(${echo.thrLightSet}%)" else "Manual(${echo.thrLightSet})"
    val thrHeavyEffective = if (echo.thrHeavyMode == 0) "Auto(${echo.thrHeavySet}%)" else "Manual(${echo.thrHeavySet})"

    // 자동 진단 판정
    val issues = mutableListOf<String>()

    if (maxAmp < 100) {
        issues.add("CRITICAL: 수신 신호 없음 → Echo AMP 증가 필요 (현재 ${echo.echoAmp}, 권장 ${echo.echoAmp + 10}~${echo.echoAmp + 20})")
    } else if (maxAmp < 300) {
        issues.add("WARNING: 수신 신호 매우 약함 → Echo AMP를 ${echo.echoAmp}에서 ${min(50, echo.echoAmp + 10)}으로 올릴 것")
    }

    if (snr < 3.0 && maxAmp >= 100) {
        issues.add("WARNING: SNR 낮음 (${String.format("%.1f", snr)}) → 노이즈 환경, ASF 설정 권장")
    }

    if (!thrLightDetected && peaks.isNotEmpty()) {
        issues.add("WARNING: Light Threshold 미교차 — 에코 피크 존재하나 Threshold가 높음 → Threshold 낮추기 또는 Echo AMP 올리기")
    }
    if (!thrHeavyDetected && peaks.size >= 2) {
        issues.add("INFO: Heavy Threshold 미교차 — 진한 층 미감지 → Heavy Threshold 설정 확인")
    }

    if (echo.thrLightReal > 0 && echo.thrLightReal < 150) {
        issues.add("WARNING: Light Threshold 교차 진폭 낮음 (${echo.thrLightReal}/4095) → 에코 약함, Echo AMP 올리기")
    }
    if (echo.thrHeavyReal > 0 && echo.thrHeavyReal < 150) {
        issues.add("WARNING: Heavy Threshold 교차 진폭 낮음 (${echo.thrHeavyReal}/4095) → 에코 약함, Echo AMP 올리기")
    }

    if (peaks.size > 4) {
        issues.add("WARNING: 다중 피크 ${peaks.size}개 감지 → 노이즈/부유물, ASF 값 올리기 권장")
    }

    val statusMeaning = when (echo.statusCh) {
        0, 4 -> "ST00: 수신 신호 없음 — 센서 잠김 확인, 케이블 확인"
        1    -> "ST01: 신호 있으나 유효 측정 불가 — Echo AMP/Threshold 조정 필요"
        2    -> "ST02: 정상 측정 중"
        3    -> "ST03: 정지 상태"
        5    -> "ER01: 에러 지속 — 센서 상태/환경 점검 필요"
        6    -> "ER02: 온도 센서 이상 — 온도 센서 케이블 확인"
        else -> "Unknown"
    }

    return buildString {
        appendLine("=== Waveform Analysis (Interface) ===")
        appendLine("- Signal Max Amplitude: $maxAmp / 4095")
        appendLine("- Signal Quality: $signalQuality")
        appendLine("- Noise Floor: ${String.format("%.0f", noiseFloor)}")
        appendLine("- Noise Level: $noiseLevel")
        appendLine("- SNR: ${String.format("%.1f", snr)} ${if (snr >= 10) "(Good)" else if (snr >= 3) "(Fair)" else "(Poor)"}")
        appendLine("- Echo AMP Setting: ${echo.echoAmp} (range 1~50)")
        appendLine("- Significant Peaks: ${peaks.size}")
        for ((idx, p) in peaks.take(5).withIndex()) {
            appendLine("  Peak${idx+1}: index=${p.index}, amplitude=${p.amp}/4095")
        }
        appendLine("- Status: ${echo.statusLabel} → $statusMeaning")
        appendLine("")
        appendLine("=== Threshold Analysis ===")
        appendLine("- Light Threshold Mode: ${echo.thrLightModeLabel}, Setting: $thrLightEffective")
        appendLine("- Light Threshold Crossing: ${if (thrLightDetected) "YES at ${echo.thrLightDist * 0.01}m, amplitude=${echo.thrLightReal}" else "NOT DETECTED"}")
        appendLine("- Heavy Threshold Mode: ${echo.thrHeavyModeLabel}, Setting: $thrHeavyEffective")
        appendLine("- Heavy Threshold Crossing: ${if (thrHeavyDetected) "YES at ${echo.thrHeavyDist * 0.01}m, amplitude=${echo.thrHeavyReal}" else "NOT DETECTED"}")
        appendLine("")
        if (issues.isNotEmpty()) {
            appendLine("=== Auto-Diagnosis ===")
            issues.forEach { appendLine("- $it") }
        } else {
            appendLine("=== Auto-Diagnosis ===")
            appendLine("- OK: 파형 정상, 특이사항 없음")
        }
    }
}

// ─── 트렌드 요약 ───
private fun summarizeTrend(records: List<com.wws2.densitymeter.model.TrendRecord>): String {
    if (records.isEmpty()) return "- No trend records available"
    val recent = records.takeLast(720)
    val levels = recent.map { it.dst }
    val temps = recent.map { it.temperature }
    val eeas = recent.map { it.eeaD }

    fun stats(values: List<Double>): String {
        val min = values.min()
        val max = values.max()
        val avg = values.average()
        val first10 = values.take(min(10, values.size)).average()
        val last10 = values.takeLast(min(10, values.size)).average()
        val trend = when {
            last10 - first10 > (max - min) * 0.1 -> "RISING"
            first10 - last10 > (max - min) * 0.1 -> "FALLING"
            else -> "STABLE"
        }
        return "min=%.2f, max=%.2f, avg=%.2f, trend=$trend".format(min, max, avg)
    }

    // 급변 감지
    val spikes = mutableListOf<String>()
    for (i in 1 until levels.size) {
        val diff = abs(levels[i] - levels[i - 1])
        if (diff > (levels.max() - levels.min()) * 0.3 && diff > 0.1) {
            spikes.add("${recent[i].dateTime}: %.2fm → %.2fm (Δ%.2f)".format(levels[i-1], levels[i], diff))
            if (spikes.size >= 3) break
        }
    }

    return buildString {
        appendLine("Total records: ${recent.size}, Period: ${recent.first().dateTime} ~ ${recent.last().dateTime}")
        appendLine("- Level: ${stats(levels)}")
        appendLine("- Temperature: ${stats(temps)}")
        appendLine("- EEA: min=${eeas.min()}, max=${eeas.max()}, avg=${eeas.average().toInt()}")
        if (spikes.isNotEmpty()) {
            appendLine("- Sudden changes detected:")
            spikes.forEach { appendLine("  $it") }
        }
    }
}

// ─── 실시간 측정 데이터 빌드 ───
private fun buildMeasurementData(state: MainUiState): String {
    val reading = state.deviceReadings[state.activeDeviceId]
    val echo = state.echoReading
    val ifaceEcho = state.interfaceEchoReading

    return buildString {
        appendLine("=== Main Tab (현재 측정값) ===")
        reading?.let {
            appendLine("- Level: ${it.level} m")
            appendLine("- Temperature: ${it.temperature} °C")
            appendLine("- Current: ${it.currentMA} mA")
            appendLine("- Damping: ${it.damping}")
            appendLine("- 4mA Setting: ${it.set4mA} m")
            appendLine("- 20mA Setting: ${it.set20mA} m")
            appendLine("- Pipe Diameter: ${it.pipeDiaLabel}")
            appendLine("- Frequency: ${it.freqMHz} MHz")
            appendLine("- Error Code: ${it.errorCode}")
        } ?: appendLine("- (Main 탭 측정값 없음)")

        appendLine("\n=== Echo Tab (농도계 파형) ===")
        echo?.let {
            appendLine("- EEA (Real): ${it.eeaR}")
            appendLine("- EEA (Density): ${it.eeaD}")
            appendLine("- Level: ${it.level}")
            appendLine("- Detection Area: ${it.detAreaLO} ~ ${it.detAreaHI}")
            appendLine("- Pipe Diameter: ${it.pipeDia}")
        } ?: appendLine("- (Echo 탭 데이터 없음)")

        appendLine("\n=== Echo Tab (계면계 파형) ===")
        ifaceEcho?.let {
            appendLine("- Light Level: ${it.lightLevel} m")
            appendLine("- Heavy Level: ${it.heavyLevel} m")
            appendLine("- Dead Zone: ${it.deadzone}")
            appendLine("- Empty: ${it.empty}")
            appendLine("- Threshold Light Distance: ${it.thrLightDist}")
            appendLine("- Threshold Heavy Distance: ${it.thrHeavyDist}")
            appendLine("- Threshold Light Setting: ${it.thrLightSet}")
            appendLine("- Threshold Heavy Setting: ${it.thrHeavySet}")
            appendLine("- Threshold Light Mode: ${it.thrLightModeLabel}")
            appendLine("- Threshold Heavy Mode: ${it.thrHeavyModeLabel}")
            appendLine("- Echo AMP: ${it.echoAmp}")
            appendLine("- Status: ${it.statusLabel}")
        } ?: appendLine("- (Echo 탭 데이터 없음)")

        appendLine("\n=== Param Tab (계면계 파라미터) ===")
        state.interfaceDiag?.let {
            appendLine("- Temperature: ${it.temperature} °C")
            appendLine("- Current: ${it.currentMA} mA")
            appendLine("- Frequency: ${it.freqLabel}")
            appendLine("- Offset: ${it.offset} m")
            appendLine("- 4mA Setting: ${it.set4mA}")
            appendLine("- 20mA Setting: ${it.set20mA}")
            appendLine("- TVG: ${it.tvg}")
            appendLine("- Damping: ${it.damp}")
            appendLine("- Relay: ${if (it.relayOn) "ON (OPEN)" else "OFF (CLOSED)"}")
        } ?: appendLine("- (Param 탭 데이터 없음)")

        appendLine("\n=== Main Tab (계면계 CH1/CH2) ===")
        state.interfaceReading?.let {
            appendLine("- CH1 Light Level: ${it.ch1Light} m")
            appendLine("- CH1 Heavy Level: ${it.ch1Heavy} m")
            appendLine("- CH1 Temperature: ${it.ch1Temperature} °C")
            appendLine("- CH1 Current: ${it.ch1CurrentMA} mA")
            appendLine("- CH2 Light Level: ${it.ch2Light} m")
            appendLine("- CH2 Heavy Level: ${it.ch2Heavy} m")
            appendLine("- CH2 Temperature: ${it.ch2Temperature} °C")
            appendLine("- CH2 Current: ${it.ch2CurrentMA} mA")
            appendLine("- Damping: ${it.damping}")
            appendLine("- 4mA Setting: ${it.set4mA} m")
            appendLine("- 20mA Setting: ${it.set20mA} m")
            appendLine("- Empty: ${it.emptyDist} m")
            appendLine("- Status: ${it.status}")
        } ?: appendLine("- (Main CH1/CH2 데이터 없음)")

        appendLine("\n=== Trend Tab (트렌드 요약, ${state.trendRecords.size} records) ===")
        append(summarizeTrend(state.trendRecords))

        appendLine("\n=== Device Info ===")
        appendLine("- Active Device: ${state.activeDeviceLabel.ifEmpty { "None" }}")
        appendLine("- Device Type: ${state.deviceType}")
        appendLine("- Connected Devices: ${state.connectedDevices.size}")
    }
}

// ─── RAG + GPT 호출 ───
private suspend fun callOpenAIWithRAG(ctx: Context, question: String, history: List<ChatMessage>, product: String, langConfig: LangConfig, measurementData: String, hasTrend: Boolean = false): String {
    return withContext(Dispatchers.IO) {
        try {
            // 1. RAG 데이터 로드
            val chunks = loadRagData(ctx, product)

            // 2. 질문 임베딩
            var contextDocs = ""
            if (chunks.isNotEmpty()) {
                val queryEmb = getEmbedding(question)
                if (queryEmb != null) {
                    val topDocs = searchSimilar(queryEmb, chunks, 15)
                    contextDocs = topDocs.joinToString("\n\n---\n\n")
                }
            }

            // 3. GPT 호출
            val url = URL("https://api.openai.com/v1/chat/completions")
            val conn = url.openConnection() as HttpURLConnection
            conn.requestMethod = "POST"
            conn.setRequestProperty("Content-Type", "application/json")
            conn.setRequestProperty("Authorization", "Bearer $OPENAI_KEY")
            conn.connectTimeout = 15000
            conn.readTimeout = 60000
            conn.doOutput = true

            val systemPrompt = buildSystemPrompt(product, langConfig, contextDocs, measurementData)

            val messagesArray = JSONArray()
            messagesArray.put(JSONObject().put("role", "system").put("content", systemPrompt))
            for (msg in history.takeLast(20)) {
                messagesArray.put(JSONObject().put("role", msg.role).put("content", msg.content))
            }
            messagesArray.put(JSONObject().put("role", "user").put("content", question))

            val body = JSONObject()
            body.put("model", if (hasTrend) "gpt-5.4-nano" else "gpt-5.4-mini")
            body.put("messages", messagesArray)
            body.put("temperature", 0.3)

            conn.outputStream.use { it.write(body.toString().toByteArray()) }

            val code = conn.responseCode
            if (code == 200) {
                val response = conn.inputStream.bufferedReader().readText()
                JSONObject(response).getJSONArray("choices").getJSONObject(0).getJSONObject("message").getString("content")
            } else {
                val error = conn.errorStream?.bufferedReader()?.readText() ?: "Unknown error"
                Log.e(TAG, "OpenAI error $code: $error")
                "Server error. (Code: $code)"
            }
        } catch (e: Exception) {
            Log.e(TAG, "RAG+GPT failed: ${e.message}")
            "Network error: ${e.message}\nPlease check your internet connection."
        }
    }
}
