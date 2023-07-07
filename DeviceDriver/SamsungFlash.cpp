#include "FlashMemoryDevice.h"

unsigned char SamsungFlash::read(long address) {
	unsigned char binary = 0;

	unsigned int number = 1713;
	unsigned char bitPosition = 0;
	while (number > 0) {
		unsigned char bit = number % 2;
		binary |= (bit << bitPosition);
		number /= 2;
		bitPosition++;
	}
	return binary;
}

void SamsungFlash::write(long address, unsigned char data) {
	printf("Hello");
};