#include "DeviceDriver.h"
#include <windows.h>
#include <exception>
#include <iostream>
#include <stdexcept>
using namespace std;

class ReadFailException : public std::exception
{
public:
	explicit  ReadFailException()
	{
		printf("\nREAD FAIL EXCEPTION!\n");
	}
};
class WriteFailException : public std::exception {
public:
	explicit  WriteFailException() {
		printf("\nWRITE FAIL EXCEPTION!\n");
	}
};


DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware)
	: m_hardware(hardware) {
}



int DeviceDriver::ReadAndPrint(unsigned char startAddr, unsigned char endAddr){
	
	for (unsigned char addr = startAddr; addr<=endAddr; addr++ )	{
		cout << read(addr) << endl;
	}
	return 0;
}
void DeviceDriver::WriteAll(unsigned char value) {

	for (unsigned char addr = 0x00; addr <= 0x04; addr++) {
		write(addr, value);
	}
}
#define READ_ATTEMPT_COUNT 5

int DeviceDriver::read(long address) {
	// TODO: implement this method properly
	
	int time_loop = READ_ATTEMPT_COUNT;
	int result_buf[READ_ATTEMPT_COUNT];
	printf("READ . . . ");
	while (time_loop-- > 0) {
		printf("#");
		result_buf[time_loop] = (int)m_hardware->read(address);
		Sleep(100);
	}

	int base_val = result_buf[READ_ATTEMPT_COUNT - 1];
	bool valid = true;
	for (int idx = 0; idx < READ_ATTEMPT_COUNT - 1; idx++) {
		if (base_val != result_buf[idx]) 
			valid = false;
	}
	if (valid) 
		return base_val;
	else 
		throw ReadFailException();
}

void DeviceDriver::write(long address, int data) {
	// TODO: implement this method
	if (read(address) != 0xFF)
		throw WriteFailException();
	m_hardware->write(address, (unsigned char)data);
}