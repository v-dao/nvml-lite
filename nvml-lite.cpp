#include "nvml-lite.h"

#include <Windows.h>
#include <assert.h>

typedef nvmlReturn_t(*nvmlInitType)();
typedef nvmlReturn_t(*nvmlShutdownType)();
typedef const char* (*nvmlErrorStringType)(nvmlReturn_t result);
typedef nvmlReturn_t(*nvmlDeviceGetCountType)(unsigned int* device);
typedef nvmlReturn_t(*nvmlDeviceGetHandleByIndexType)(unsigned int index, nvmlDevice_t* device);
typedef nvmlReturn_t(*nvmlDeviceGetNameType)(nvmlDevice_t device, char* name, unsigned int  length);
typedef nvmlReturn_t(*nvmlDeviceGetPciInfoType)(nvmlDevice_t device, nvmlPciInfo_t* pci);
typedef nvmlReturn_t(*nvmlDeviceGetTemperatureThresholdType)(nvmlDevice_t device, nvmlTemperatureThresholds_t thresholdType, unsigned int* temp);
typedef nvmlReturn_t(*nvmlDeviceGetTemperatureType)(nvmlDevice_t device, nvmlTemperatureSensors_t sensorType, unsigned int* temp);
typedef nvmlReturn_t(*nvmlDeviceGetUtilizationRatesType)(nvmlDevice_t device, nvmlUtilization_t* utilization);
typedef nvmlReturn_t(*nvmlDeviceGetMemoryInfoType)(nvmlDevice_t device, nvmlMemory_t* memory);
typedef nvmlReturn_t(*nvmlDeviceGetBAR1MemoryInfoType)(nvmlDevice_t device, nvmlBAR1Memory_t* bar1Memory);


namespace {
	HMODULE mvmlModule = nullptr;
	nvmlInitType fnInit = nullptr;
	nvmlShutdownType fnShutdown = nullptr;
	nvmlErrorStringType fnErrorString = nullptr;
	nvmlDeviceGetCountType fnDeviceGetCount = nullptr;
	nvmlDeviceGetHandleByIndexType fnDeviceGetHandleByIndex = nullptr;
	nvmlDeviceGetNameType fnDeviceGetName = nullptr;
	nvmlDeviceGetPciInfoType fnDeviceGetPciInfo = nullptr;
	nvmlDeviceGetTemperatureThresholdType fnDeviceGetTemperatureThreshold = nullptr;
	nvmlDeviceGetTemperatureType fnDeviceGetTemperature = nullptr;
	nvmlDeviceGetUtilizationRatesType fnDeviceGetUtilizationRates = nullptr;
	nvmlDeviceGetMemoryInfoType fnDeviceGetMemoryInfo = nullptr;
	nvmlDeviceGetBAR1MemoryInfoType fnDeviceGetBAR1MemoryInfo = nullptr;
}

nvmlReturn_t nvmlInit()
{
	if (!mvmlModule)
	{
		HMODULE m = ::LoadLibraryA("nvml.dll");
		if (!m)
		{
			return NVML_ERROR_UNKNOWN;
		}
		mvmlModule = m;

		fnInit = (nvmlInitType)::GetProcAddress(m, "nvmlInit");
		assert(fnInit);
		fnShutdown = (nvmlShutdownType)::GetProcAddress(m, "nvmlShutdown");
		assert(fnShutdown);
		fnErrorString = (nvmlErrorStringType)::GetProcAddress(m, "nvmlErrorString");
		assert(fnErrorString);
		fnDeviceGetCount = (nvmlDeviceGetCountType)::GetProcAddress(m, "nvmlDeviceGetCount");
		assert(fnDeviceGetCount);
		fnDeviceGetHandleByIndex = (nvmlDeviceGetHandleByIndexType)::GetProcAddress(m, "nvmlDeviceGetHandleByIndex");
		assert(fnDeviceGetHandleByIndex);
		fnDeviceGetName = (nvmlDeviceGetNameType)::GetProcAddress(m, "nvmlDeviceGetName");
		assert(fnDeviceGetName);
		fnDeviceGetPciInfo = (nvmlDeviceGetPciInfoType)::GetProcAddress(m, "nvmlDeviceGetPciInfo");
		assert(fnDeviceGetPciInfo);
		fnDeviceGetTemperatureThreshold = (nvmlDeviceGetTemperatureThresholdType)::GetProcAddress(m, "nvmlDeviceGetTemperatureThreshold");
		assert(fnDeviceGetTemperatureThreshold);
		fnDeviceGetTemperature = (nvmlDeviceGetTemperatureType)::GetProcAddress(m, "nvmlDeviceGetTemperature");
		assert(fnDeviceGetTemperature);
		fnDeviceGetUtilizationRates = (nvmlDeviceGetUtilizationRatesType)::GetProcAddress(m, "nvmlDeviceGetUtilizationRates");
		assert(fnDeviceGetUtilizationRates);
		fnDeviceGetMemoryInfo = (nvmlDeviceGetMemoryInfoType)::GetProcAddress(m, "nvmlDeviceGetMemoryInfo");
		assert(fnDeviceGetMemoryInfo);
		fnDeviceGetBAR1MemoryInfo = (nvmlDeviceGetBAR1MemoryInfoType)::GetProcAddress(m, "nvmlDeviceGetBAR1MemoryInfo");
		assert(fnDeviceGetBAR1MemoryInfo);
	}

	return fnInit ? fnInit() : NVML_ERROR_UNKNOWN;
}

nvmlReturn_t nvmlShutdown()
{
	return fnShutdown ? fnShutdown() : NVML_ERROR_UNINITIALIZED;
}

const char* nvmlErrorString(nvmlReturn_t result)
{
	return fnErrorString ? fnErrorString(result) : "UNINITIALIZED";
}

nvmlReturn_t nvmlDeviceGetCount(unsigned int* deviceCount)
{
	return fnDeviceGetCount ? fnDeviceGetCount(deviceCount) : NVML_ERROR_UNINITIALIZED;
}

nvmlReturn_t nvmlDeviceGetHandleByIndex(unsigned int index, nvmlDevice_t* device)
{
	return fnDeviceGetHandleByIndex ? fnDeviceGetHandleByIndex(index, device) : NVML_ERROR_UNINITIALIZED;
}
nvmlReturn_t nvmlDeviceGetName(nvmlDevice_t device, char* name, unsigned int length)
{
	return fnDeviceGetName ? fnDeviceGetName(device, name, length) : NVML_ERROR_UNINITIALIZED;
}
nvmlReturn_t nvmlDeviceGetPciInfo(nvmlDevice_t device, nvmlPciInfo_t* pci)
{
	return fnDeviceGetPciInfo ? fnDeviceGetPciInfo(device, pci) : NVML_ERROR_UNINITIALIZED;
}
nvmlReturn_t nvmlDeviceGetTemperatureThreshold(nvmlDevice_t device, nvmlTemperatureThresholds_t thresholdType, unsigned int* temp)
{
	return fnDeviceGetTemperatureThreshold ? fnDeviceGetTemperatureThreshold(device, thresholdType, temp) : NVML_ERROR_UNINITIALIZED;
}

nvmlReturn_t nvmlDeviceGetTemperature(nvmlDevice_t device, nvmlTemperatureSensors_t sensorType, unsigned int* temp)
{
	return fnDeviceGetTemperature ? fnDeviceGetTemperature(device, sensorType, temp) : NVML_ERROR_UNINITIALIZED;
}

nvmlReturn_t nvmlDeviceGetUtilizationRates(nvmlDevice_t device, nvmlUtilization_t* utilization)
{
	return fnDeviceGetUtilizationRates ? fnDeviceGetUtilizationRates(device, utilization) : NVML_ERROR_UNINITIALIZED;
}

nvmlReturn_t nvmlDeviceGetMemoryInfo(nvmlDevice_t device, nvmlMemory_t* memory)
{
	return fnDeviceGetMemoryInfo ? fnDeviceGetMemoryInfo(device, memory) : NVML_ERROR_UNINITIALIZED;
}

nvmlReturn_t nvmlDeviceGetBAR1MemoryInfo(nvmlDevice_t device, nvmlBAR1Memory_t* bar1Memory)
{
	return fnDeviceGetBAR1MemoryInfo ? fnDeviceGetBAR1MemoryInfo(device, bar1Memory) : NVML_ERROR_UNINITIALIZED;
}
