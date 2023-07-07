#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver {
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int ReadAndPrint(unsigned char startAddr, unsigned char endAddr);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};