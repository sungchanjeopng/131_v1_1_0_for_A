package com.wws2.densitymeter.data.repository

import com.wws2.densitymeter.model.ConnectedBleDevice
import com.wws2.densitymeter.service.BleProtocolService
import java.util.concurrent.ConcurrentHashMap

/**
 * Manages the set of connected BLE devices and their protocol services.
 * Does NOT own BLE connections — it tracks what's connected.
 *
 * Corresponds to firmware's Comm module (comm.c) device registry.
 */
class DeviceRepository {

    private val protocolServices = ConcurrentHashMap<String, BleProtocolService>()

    fun getProtocol(deviceId: String): BleProtocolService? = protocolServices[deviceId]

    fun setProtocol(deviceId: String, proto: BleProtocolService) {
        protocolServices[deviceId] = proto
    }

    fun removeProtocol(deviceId: String) {
        protocolServices.remove(deviceId)
    }

    fun removeProtocols(ids: List<String>) {
        ids.forEach { protocolServices.remove(it) }
    }

    fun disconnectAll() {
        protocolServices.values.forEach { it.disconnect() }
        protocolServices.clear()
    }

    /** Allocate label for density meter: ENV230_A01 ~ A04 */
    fun allocateDensityLabel(usedLabels: Set<String>): String {
        for (i in 1..4) {
            val label = "ENV230_A${i.toString().padStart(2, '0')}"
            if (label !in usedLabels) return label
        }
        return "ENV230_A04"
    }

    /** Allocate label pair for interface meter: ENV130_A02/A03, A04/A05, etc. */
    fun allocateInterfaceLabels(usedLabels: Set<String>): Pair<String, String> {
        val pairs = listOf(2 to 3, 4 to 5, 6 to 7, 8 to 9)
        for ((a, b) in pairs) {
            val l1 = "ENV130_A${a.toString().padStart(2, '0')}"
            val l2 = "ENV130_A${b.toString().padStart(2, '0')}"
            if (l1 !in usedLabels && l2 !in usedLabels) return l1 to l2
        }
        return "ENV130_A02" to "ENV130_A03"
    }

    /** Extract firmware version from BLE advertisement name (e.g., "WESS_V0.1_ENV230_A01" → "V0.1") */
    fun extractFirmwareVersion(bleName: String): String {
        val regex = Regex("V(\\d+\\.\\d+)", RegexOption.IGNORE_CASE)
        return regex.find(bleName)?.value ?: ""
    }

    companion object {
        /** Detect device type from BLE name */
        fun isInterfaceMeter(name: String): Boolean {
            val upper = name.uppercase()
            return upper.startsWith("W3") || upper.contains("130") ||
                    upper.contains("WE13") || upper.contains("INTERFACE")
        }
    }
}
