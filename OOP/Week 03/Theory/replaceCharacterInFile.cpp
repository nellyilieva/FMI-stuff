#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

void replaceCharacterInFile(const char* fileName, const char ch, const char replacemnet) {
	std::fstream file(fileName, std::ios::in | std::ios::out);

	if (!file.is_open()) {
		return;
	}

	while (true) {
		char curr = file.get();

		if (file.eof()) {
			return;
		}

		if (curr == ch) {
			file.seekp(-1, std::ios::cur);  //seekp do flush
			file.put(replacemnet);
			file.flush();  //!!!
		}
	}

	file.close();
}

int main() {
	replaceCharacterInFile("test.bin", 'I', 'W');
}