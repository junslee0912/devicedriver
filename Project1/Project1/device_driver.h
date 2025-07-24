#pragma once
#include "flash_memory_device.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);
    static constexpr int COMPARE_COUNT = 5;
protected:
    FlashMemoryDevice* m_hardware;
private:
    void checkAssert(int* returnArr);
};