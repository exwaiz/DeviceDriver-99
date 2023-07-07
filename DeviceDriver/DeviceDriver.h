#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver {
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int ReadAndPrint(unsigned char startAddr, unsigned char endAddr);
    void WriteAll(unsigned char value);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};