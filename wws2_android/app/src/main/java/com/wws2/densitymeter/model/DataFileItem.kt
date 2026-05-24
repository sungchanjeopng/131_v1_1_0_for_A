package com.wws2.densitymeter.model

data class DataFileItem(
    val name: String,
    val recordCount: Int,
    val rangeLabel: String,
    val sizeBytes: Int,
    val targetDevice: String,
    val chartRecords: List<TrendRecord>,
    val allRecords: List<TrendRecord> = chartRecords,
)
