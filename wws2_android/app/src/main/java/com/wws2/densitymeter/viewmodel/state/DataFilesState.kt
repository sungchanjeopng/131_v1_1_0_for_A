package com.wws2.densitymeter.viewmodel.state

import com.wws2.densitymeter.model.DataFileItem
import com.wws2.densitymeter.model.DataFilesStage

data class DataFilesState(
    val dataFilesStage: DataFilesStage = DataFilesStage.LIST,
    val activeDataFile: DataFileItem? = null,
    val dataDownloadProgress: Double = 0.0,
    val savedDataFiles: List<DataFileItem> = emptyList(),
)
