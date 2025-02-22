#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#pragma warning (disable: 4996)

bool isValidSymbol(unsigned char ch) {
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ('0' <= ch && ch <= '9');
}

int getFileSize(std::ifstream& ifs) {
	int curr = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	int size = ifs.tellg();
	ifs.seekg(curr, std::ios::beg);

	return size;
}

struct HexViewFile {
	unsigned char* data = nullptr;
	size_t dataSize = 0;
};

HexViewFile initData(const char* fileName) {   //we write the data from the file into the structure
	HexViewFile file;

	std::ifstream ifs(fileName, std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		file.data = nullptr;
		file.dataSize = 0;
		return file;
	}

	file.dataSize = getFileSize(ifs);
	file.data = new unsigned char[file.dataSize];
	ifs.read((char*)file.data, file.dataSize);

	ifs.close();

	return file;

}

void freeData(HexViewFile& file) {
	delete[] file.data;
	file.data = nullptr;
	file.dataSize = 0;
}

void saveHexViewFile(const char* fileName, const HexViewFile& file) {
	std::ofstream ofs(fileName, std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		return;
	}

	ofs.write((const char*)&file.data, file.dataSize);   //we write only the data in the file
	ofs.close();
}

void printData(const HexViewFile& file) {
	for (int i = 0; i < file.dataSize; i++) {
		std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)file.data[i] << " ";
	}

	std::cout << std::endl;

	for (int i = 0; i < file.dataSize; i++) {
		if (isValidSymbol(file.data[i])) {
			std::cout << file.data[i] << " ";
		}
		else {
			std::cout << ".. ";
		}
	}

	std::cout << std::endl;
}

void modify(HexViewFile& file, unsigned idx, char ch) {
	if (idx >= file.dataSize) {
		return;
	}

	file.data[idx] = ch;
}

int main() {

	HexViewFile myFile = initData("test.bin");
	printData(myFile);
	modify(myFile, 0, 'a');
	saveHexViewFile("test.bin", myFile);
	freeData(myFile);
}