#pragma once

#ifndef NVML_H

enum nvmlReturn_t
{
    NVML_SUCCESS = 0,
    NVML_ERROR_UNINITIALIZED = 1,
    NVML_ERROR_INVALID_ARGUMENT = 2,
    NVML_ERROR_NOT_SUPPORTED = 3,
    NVML_ERROR_NO_PERMISSION = 4,
    NVML_ERROR_ALREADY_INITIALIZED = 5,
    NVML_ERROR_NOT_FOUND = 6,
    NVML_ERROR_INSUFFICIENT_SIZE = 7,
    NVML_ERROR_INSUFFICIENT_POWER = 8,
    NVML_ERROR_DRIVER_NOT_LOADED = 9,
    NVML_ERROR_TIMEOUT = 10,
    NVML_ERROR_IRQ_ISSUE = 11,
    NVML_ERROR_LIBRARY_NOT_FOUND = 12,
    NVML_ERROR_FUNCTION_NOT_FOUND = 13,
    NVML_ERROR_CORRUPTED_INFOROM = 14,
    NVML_ERROR_GPU_IS_LOST = 15,
    NVML_ERROR_RESET_REQUIRED = 16,
    NVML_ERROR_OPERATING_SYSTEM = 17,
    NVML_ERROR_LIB_RM_VERSION_MISMATCH = 18,
    NVML_ERROR_IN_USE = 19,
    NVML_ERROR_MEMORY = 20,
    NVML_ERROR_NO_DATA = 21,
    NVML_ERROR_VGPU_ECC_NOT_SUPPORTED = 22,
    NVML_ERROR_INSUFFICIENT_RESOURCES = 23,
    NVML_ERROR_FREQ_NOT_SUPPORTED = 24,
    NVML_ERROR_UNKNOWN = 999,
};

enum nvmlTemperatureThresholds_t
{
    NVML_TEMPERATURE_THRESHOLD_SHUTDOWN = 0,
    NVML_TEMPERATURE_THRESHOLD_SLOWDOWN = 1,
    NVML_TEMPERATURE_THRESHOLD_MEM_MAX = 2,
    NVML_TEMPERATURE_THRESHOLD_GPU_MAX = 3,
    NVML_TEMPERATURE_THRESHOLD_ACOUSTIC_MIN = 4,
    NVML_TEMPERATURE_THRESHOLD_ACOUSTIC_CURR = 5,
    NVML_TEMPERATURE_THRESHOLD_ACOUSTIC_MAX = 6,
    NVML_TEMPERATURE_THRESHOLD_COUNT
};

enum nvmlTemperatureSensors_t
{
    NVML_TEMPERATURE_GPU = 0,
    NVML_TEMPERATURE_COUNT
};

#define NVML_DEVICE_PCI_BUS_ID_BUFFER_SIZE 32
#define NVML_DEVICE_PCI_BUS_ID_BUFFER_V2_SIZE 16

typedef void* nvmlDevice_t;

typedef struct _nvmlPciInfo {
    unsigned int bus; // The bus on which the device resides, 0 to 0xff.
    char busId[NVML_DEVICE_PCI_BUS_ID_BUFFER_SIZE]; // The tuple domain:bus:device.function PCI identifier (& NULL terminator).
    char busIdLegacy[NVML_DEVICE_PCI_BUS_ID_BUFFER_V2_SIZE]; // The legacy tuple domain:bus:device.function PCI identifier (& NULL terminator).
    unsigned int device; // The device's id on the bus, 0 to 31.
    unsigned int domain; // The PCI domain on which the device's bus resides, 0 to 0xffffffff.
    unsigned int pciDeviceId; // The combined 16-bit device id and 16-bit vendor id.
    unsigned int pciSubSystemId; // The 32-bit Sub System Device ID.
}nvmlPciInfo_t;

typedef struct _nvmlUtilization {
    unsigned int gpu; // Percent of time over the past sample period during which one or more kernels was executing on the GPU.
    unsigned int memory; // Percent of time over the past sample period during which global (device) memory was being read or written.
}nvmlUtilization_t;

typedef struct _nvmlBAR1Memory {
    unsigned long long  total; // Total installed FB memory (in bytes).
    unsigned long long  free; // Unallocated FB memory (in bytes).
    unsigned long long  used; // Allocated FB memory (in bytes). Note that the driver/GPU always sets aside a small amount of memory for bookkeeping.
}nvmlBAR1Memory_t;

typedef struct _nvmlMemory {
    unsigned long long  total; // Total installed FB memory (in bytes).
    unsigned long long  free; // Unallocated FB memory (in bytes).
    unsigned long long  used; // Allocated FB memory (in bytes). Note that the driver/GPU always sets aside a small amount of memory for bookkeeping.
}nvmlMemory_t;

nvmlReturn_t (nvmlInit)();
nvmlReturn_t (nvmlShutdown)();
const char*  (nvmlErrorString)(nvmlReturn_t result);
nvmlReturn_t (nvmlDeviceGetCount)(unsigned int* deviceCount);
nvmlReturn_t (nvmlDeviceGetHandleByIndex)(unsigned int index, nvmlDevice_t* device);
nvmlReturn_t (nvmlDeviceGetName)(nvmlDevice_t device, char* name, unsigned int  length);
nvmlReturn_t (nvmlDeviceGetPciInfo)(nvmlDevice_t device, nvmlPciInfo_t* pci);
nvmlReturn_t (nvmlDeviceGetTemperatureThreshold)(nvmlDevice_t device, nvmlTemperatureThresholds_t thresholdType, unsigned int* temp);
nvmlReturn_t (nvmlDeviceGetTemperature)(nvmlDevice_t device, nvmlTemperatureSensors_t sensorType, unsigned int* temp);
nvmlReturn_t (nvmlDeviceGetUtilizationRates)(nvmlDevice_t device, nvmlUtilization_t* utilization);
nvmlReturn_t nvmlDeviceGetMemoryInfo(nvmlDevice_t device, nvmlMemory_t* memory);
nvmlReturn_t nvmlDeviceGetBAR1MemoryInfo(nvmlDevice_t device, nvmlBAR1Memory_t* bar1Memory);

#endif
