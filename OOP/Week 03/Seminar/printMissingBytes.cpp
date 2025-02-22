#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

int getFileSize(std::ifstream& ifs) {
	int curr = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	int size = ifs.tellg();
	ifs.seekg(curr, std::ios::beg);

	return size;
}

struct FileData {
	unsigned char* data = nullptr;
	int fileSize = 0;
};

void freeData(FileData& fd) {
	delete[] fd.data;
	fd.fileSize = 0;
}

FileData initFileContent(const char* fileName) {
	std::ifstream ifs(fileName, std::ios::binary);

	if (!ifs.is_open()) {
		return {};
	}

	int fileSize = getFileSize(ifs);
	unsigned char* buff = new unsigned char[fileSize];

	ifs.read((char*)buff, fileSize);
	ifs.close();

	return { buff, fileSize };
}

void printMissingBytes(const FileData& fd) {
	int counter[256] = { 0 };

	for (int i = 0; i < fd.fileSize; i++) {
		counter[fd.data[i]]++;
	}

	for (int i = 0; i < 256; i++) {
		if (counter[i] == 0) {
			std::cout << i << std::endl;
		}
	}
}

int main() {
	FileData fd = initFileContent("test.bin");

	printMissingBytes(fd);

	freeData(fd);
}