#include <iostream>

bool isLittleEndian() {
	union {
		uint32_t n = 1;
		unsigned char bytes[4];
	} test;

	return test.bytes[0];
}

int main()
{
	std::cout << isLittleEndian();

}