// NvApiUse.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <thread>
#include <functional>
#include <Windows.h>

#include "nvml-lite.h"

class Defer
{
    std::function<void()> _function;
public:
    inline Defer(std::function<void()> func) :_function(func) {}
    inline ~Defer() { if (_function) { _function(); } }
};



int main()
{
    nvmlReturn_t ret = nvmlInit();
    if (ret != NVML_SUCCESS)
    {
        printf("nvmlInit err: %s\n", nvmlErrorString(ret));
        return -1;
    }
    else 
    {
        printf("nvmlInit success\n");
    }
    Defer nvmlDefer([]{
        nvmlShutdown();
    });

    unsigned int device_count = 0;
    ret = nvmlDeviceGetCount(&device_count);
    if (ret != NVML_SUCCESS)
    {
        printf("nvmlDeviceGetCount err: %s\n", nvmlErrorString(ret));
        return ret;
    }

    std::cout << "device count: " << device_count << std::endl;

    for (unsigned int i = 0; i < device_count; ++i)
    {
        nvmlDevice_t device;
        ret = nvmlDeviceGetHandleByIndex(i, &device);
        if (ret != NVML_SUCCESS)
        {
            printf("nvmlDeviceGetHandleByIndex err: %s\n", nvmlErrorString(ret));
            return ret;
        }

        char name[128];
        ret = nvmlDeviceGetName(device, name, sizeof(name));
        if (ret != NVML_SUCCESS)
        {
            printf("nvmlDeviceGetName err: %s\n", nvmlErrorString(ret));
            return ret;
        }

        nvmlPciInfo_t pci;
        ret = nvmlDeviceGetPciInfo(device, &pci);
        if (ret != NVML_SUCCESS)
        {
            printf("nvmlDeviceGetPciInfo err: %s\n", nvmlErrorString(ret));
            return ret;
        }

        printf("num: %d. name: %s [%s]\n", i, name, pci.busId);

        printf("---- temperature ----\n");

        unsigned int temperature = 100;
        ret = nvmlDeviceGetTemperatureThreshold(device, NVML_TEMPERATURE_THRESHOLD_SHUTDOWN, &temperature);
        if (ret != NVML_SUCCESS)
        {
            printf("device %i failed to get NVML_TEMPERATURE_THRESHOLD_SHUTDOWN: %s\n", i, nvmlErrorString(ret));
        }
        else 
        {
            printf("TEMPERATURE_THRESHOLD_SHUTDOWN: %d ℃ (Temperature at which the GPU will shut down for HW protection)\n", temperature);
        }

        ret = nvmlDeviceGetTemperatureThreshold(device, NVML_TEMPERATURE_THRESHOLD_SLOWDOWN, &temperature);
        if (ret != NVML_SUCCESS)
        {
            printf("device %i failed to get NVML_TEMPERATURE_THRESHOLD_SLOWDOWN: %s\n", i, nvmlErrorString(ret));
        }
        else
        {
            printf("TEMPERATURE_THRESHOLD_SLOWDOWN: %d ℃ (Temperature at which the GPU will begin slowdown)\n", temperature);
        }

        ret = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temperature);
        if (ret != NVML_SUCCESS)
        {
            printf("device %i failed to get NVML_TEMPERATURE_GPU : %s\n", i, nvmlErrorString(ret));
        }
        else
        {
            printf("TEMPERATURE_GPU: %d ℃\n", temperature);
        }

        for (;;)
        {
            nvmlUtilization_t utilization;
            ret = nvmlDeviceGetUtilizationRates(device, &utilization);
            if (ret != NVML_SUCCESS)
            {
                printf("device %i nvmlDeviceGetUtilizationRates Failed: %s\n", i, nvmlErrorString(ret));
            }
            else 
            {
                printf("----- UtilizationRates -----\n");
                printf("GPU usage: %d %%\n", utilization.gpu);
                printf("MEM usage: %d %%\n", utilization.memory);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    return 0;
}
