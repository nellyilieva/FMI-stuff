#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

void divideOddAndEven(const char* fileName, const char* oddName, const char* evenName) {
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open()) {
		return;
	}

	std::ofstream odd(oddName, std::ios::binary);

	if (!odd.is_open()) {
		ifs.close();
		return;
	}

	std::ofstream even(evenName, std::ios::binary);

	if (!even.is_open()) {
		ifs.close();
		odd.close();
		return;
	}

	while (true) {
		int num;
		ifs.read((char*)&num, sizeof(int));

		if (ifs.eof()) {
			return;
		}

		if (num % 2 == 0) {
			even.write((const char*)&num, sizeof(int));
		}
		else {
			odd.write((const char*)&num, sizeof(int));
		}

	}

	ifs.close();
	odd.close();
	even.close();
}

int main() {
	int arr[5] = { 1, 2, 3, 4, 5 };
	std::ofstream ofs("test.bin", std::ios::binary);

	ofs.write((const char*)&arr, 5 * sizeof(int));

	ofs.close();

	divideOddAndEven("test.bin", "odd.bin", "even.bin");

	std::ifstream odd("odd.bin", std::ios::binary);

	int n;

	while (odd.read((char*)&n, sizeof(int))) {
		std::cout << n << " ";
	}

	odd.close();

	std::cout << std::endl;

	std::ifstream even("even.bin", std::ios::binary);

	while (even.read((char*)&n, sizeof(int))) {
		std::cout << n << " ";
	}
	even.close();
}