package com.wws2.densitymeter.viewmodel.state

import com.wws2.densitymeter.model.TrendRecord

data class TrendState(
    val trendRecords: List<TrendRecord> = emptyList(),
    val downloadRecords: List<TrendRecord> = emptyList(),
    val trendExpectedRecords: Int = 0,
    val isTrendStreaming: Boolean = false,
    val trendError: String? = null,
)
