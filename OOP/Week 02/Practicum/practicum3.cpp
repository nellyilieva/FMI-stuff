#include <iostream>
#include <fstream>
#include <sstream>


void writeSumAndDiff(const char* fileName) {
	int a, b;
	std::cin >> a >> b;

	std::ofstream ofs(fileName);

	if (!ofs.is_open()) {
		return;
	}

	ofs << a + b << " " << a - b << std::endl;

	ofs.close();
}

void readSumAndDiff(const char* fileName) {
	int sum, diff;

	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return;
	}

	ifs >> sum >> diff;

	int a = (sum + diff) / 2;
	int b = sum - a;

	ifs.close();

	std::cout << a << " " << b;
}


int countOccurances(const int* arr, int size, int num) {
	int count = 0;

	for (int i = 0; i < size; i++) {
		if (arr[i] == num) {
			count++;
		}
	}

	return count;
}

int mostCommonNumInArr(const int* arr, int size) {
	int result = 0;
	int occurances = 0;

	for (int i = 0; i < size; i++) {
		int curr = arr[i];
		int currOcc = countOccurances(arr, size, curr);

		if (occurances < currOcc) {
			result = curr;
			occurances = currOcc;
		}
	}

	return result;
}

void mostCommonNumInFile(const char* fileName) {
	int n;

	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return;
	}

	ifs >> n;

	int* arr = new int[n];

	for (int i = 0; i < n; i++) {
		ifs >> arr[i];
	}

	ifs.close();

	std::cout << mostCommonNumInArr(arr, n);

	delete[] arr;
}


void printOwnCode() {
	std::ifstream ifs("OOP_practicum.cpp");

	if (!ifs.is_open()) {
		return;
	}

	char buff[1024];

	while (true) {
		ifs.getline(buff, 1024);

		if (ifs.eof()) {
			return;
		}

		std::cout << buff << std::endl;
	}
}


void compareFiles(const char* firstFileName, const char* secondFileName) {
	std::ifstream first(firstFileName);
	
	if (!first.is_open()) {
		return;
	}

	std::ifstream second(secondFileName);

	if (!second.is_open()) {
		first.close();
		return;
	}

	char buff1[1024];
	char buff2[1024];

	int line = 0;

	while (true) {
		line++;
		first.getline(buff1, 1024);
		second.getline(buff2, 1024);

		if (first.eof() && second.eof()) {
			return;
		}

		if (std::strcmp(buff1, buff2) != 0 || first.eof() || second.eof()) {
			std::cout << line;
			return;
		}
	}

}


int main() {
	
}