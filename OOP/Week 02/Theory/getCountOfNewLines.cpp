#include <iostream>
#include <fstream>

const char NEW_LINE_SYMBOL = '\n';

int getCharCount(std::ifstream& ifs, char ch) {
	if (!ifs.is_open()) {
		return -1;
	}

	int count = 0;

	while (true) {
		char curr = ifs.get();

		if (ifs.eof()) {
			break;
		}

		if (curr == ch) {
			count++;
		}
	}

	return count;
}

int getCountOfNewLines(const char* fileName) {
	if (!fileName) {
		return -1;
	}

	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return -1;
	}

	return getCharCount(ifs, NEW_LINE_SYMBOL) + 1;
}

int main() {
	std::cout << coutntOfNewLines("getCountOfNewLines.cpp")
}
