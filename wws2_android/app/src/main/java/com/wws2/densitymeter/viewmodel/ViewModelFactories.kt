package com.wws2.densitymeter.viewmodel

import android.app.Application
import androidx.lifecycle.ViewModel
import androidx.lifecycle.ViewModelProvider
import androidx.lifecycle.viewmodel.CreationExtras
import com.wws2.densitymeter.DensityMeterApp

inline fun <reified T : ViewModel> appViewModelFactory(
    crossinline create: (DensityMeterApp) -> T
): ViewModelProvider.Factory = object : ViewModelProvider.Factory {
    @Suppress("UNCHECKED_CAST")
    override fun <V : ViewModel> create(modelClass: Class<V>, extras: CreationExtras): V {
        val app = extras[ViewModelProvider.AndroidViewModelFactory.APPLICATION_KEY] as DensityMeterApp
        return create(app) as V
    }
}
