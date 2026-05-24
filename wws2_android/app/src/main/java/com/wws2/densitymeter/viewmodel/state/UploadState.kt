package com.wws2.densitymeter.viewmodel.state

data class UploadState(
    val pickedFileName: String? = null,
    val pickedFileSize: Int? = null,
    val isUploading: Boolean = false,
    val uploadProgress: Double = 0.0,
    val uploadDone: Boolean = false,
    val uploadElapsed: Long = 0L,
    val firmwareTargetDeviceId: String = "",
)
