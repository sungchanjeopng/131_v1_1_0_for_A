package com.wws2.densitymeter.ui.screen

import org.junit.Assert.assertFalse
import org.junit.Assert.assertTrue
import org.junit.Test

class ChatbotPromptConfigTest {

    @Test
    fun `selected language rule is injected into the system prompt`() {
        val langConfig = getChatbotLangConfig("Korean")

        val prompt = buildSystemPrompt(
            product = "ENV130",
            langConfig = langConfig,
            context = "DOC_CONTEXT",
            measurementData = "MEASUREMENT_DATA",
        )

        assertTrue(prompt.contains(langConfig.langRule))
        assertTrue(prompt.contains("DOC_CONTEXT"))
        assertTrue(prompt.contains("MEASUREMENT_DATA"))
    }

    @Test
    fun `auto language detection instructions are removed when language is selected manually`() {
        val langConfig = getChatbotLangConfig("Japanese")

        val prompt = buildSystemPrompt(
            product = "ENV120",
            langConfig = langConfig,
            context = "DOC_CONTEXT",
            measurementData = "MEASUREMENT_DATA",
        )

        assertFalse(prompt.contains("detect the language of each user message", ignoreCase = true))
        assertFalse(prompt.contains("If Korean → reply in Korean. If English → reply in English"))
    }
}
