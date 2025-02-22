#include "FileReaderAndWriter.h"

FilePath::FilePath(const MyString& fileName) {
	//like stringView -> geting substring; while(*str && *str != '.') str++ return str + 1;
	const char* beg = fileName.c_str();
	const char* end = fileName.c_str() + fileName.getSize();
	const char* iter = end;

	while (iter != beg && *iter != '.') {
		iter--;
	}

	name = fileName.substr(0, iter - beg);
	extension = fileName.substr(iter - beg, end - iter);

}

const MyString& FilePath::getName() const {
	return name;
}

const MyString& FilePath::getExtension() const {
	return extension;
}


FileReader::FileReader(const MyString& filePath) : filePath(filePath) {}


int ArrFileReader::getCharCount(std::ifstream& ifs, char ch) {
	size_t currPos = ifs.tellg();

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

	ifs.clear();
	ifs.seekg(currPos);

	return count;
}

ArrFileReader::ArrFileReader(const MyString& filePath) : FileReader(filePath) {}

int* ArrFileReader::read(size_t& size) const {

	std::ifstream ifs(filePath.c_str());

	if (!ifs.is_open()) {
		throw std::exception("Cannot open file");
	}

	size = getCharCount(ifs, ' ') + 1;  //to find size of arr -> how many elements

	int* arr = new int[size];

	ifs.ignore();

	for (int i = 0; i < size; i++) {
		ifs >> arr[i];
	}

	ifs.close();
	return arr;
}

int BinaryFileReader::getFileSize(std::ifstream& ifs) {
	int curr = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	int size = ifs.tellg();
	ifs.seekg(0, curr);

	return size;
}

BinaryFileReader::BinaryFileReader(const MyString& filePath) : FileReader(filePath) {}

int* BinaryFileReader::read(size_t& size) const {
	std::ifstream ifs(filePath.c_str(), std::ios::binary);

	if (!ifs.is_open()) {
		throw std::exception("Cannot open file");
	}

	size = getFileSize(ifs) / sizeof(int);
	int* arr = new int[size];

	ifs.read((char*)arr, size * sizeof(int));

	ifs.close();

	return arr;
}


int CSVFileReader::getCharCount(std::ifstream& ifs, char ch) {
	int currPos = ifs.tellg();

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

	ifs.clear();
	ifs.seekg(currPos);

	return count;
}

CSVFileReader::CSVFileReader(const MyString& filePath) : FileReader(filePath) {}

int* CSVFileReader::read(size_t& size) const {
	std::ifstream ifs(filePath.c_str());

	if (!ifs.is_open()) {
		throw std::exception("Cannot open file");
	}

	size = getCharCount(ifs, ',') + 1;

	int* arr = new int[size];

	for (int i = 0; i < size; i++) {
		ifs >> arr[i];
		ifs.ignore();  //to miss the ,
	}

	ifs.close();

	return arr;
}

FileWriter::FileWriter(const MyString& filePath)  : filePath(filePath) {}

ArrFileWriter::ArrFileWriter(const MyString& filePath) : FileWriter(filePath) {}

void ArrFileWriter::write(const int* arr, size_t size) const {
	std::ofstream ofs(filePath.c_str());

	if (!ofs.is_open()) {
		throw std::exception("Cannot open file");
	}

	ofs << '[ ';

	for (int i = 0; i < size; i++) {
		ofs << arr[i];

		if (i != size - 1) {
			ofs << ' ';
		}
	}

	ofs << ']';

	ofs.close();
}

BinaryFileWriter::BinaryFileWriter(const MyString& filePath) : FileWriter(filePath) {}

void BinaryFileWriter::write(const int* arr, size_t size) const {
	std::ofstream ofs(filePath.c_str(), std::ios::binary);

	if (!ofs.is_open()) {
		throw std::exception("Cannot open file");
	}

	ofs.write((const char*)arr, size * sizeof(int));

	ofs.close();
}

CSVFileWriter::CSVFileWriter(const MyString& filePath) : FileWriter(filePath) {}

void CSVFileWriter::write(const int* arr, size_t size) const {
	std::ofstream ofs(filePath.c_str());

	if (!ofs.is_open()) {
		throw std::exception("Cannot open file");
	}

	ofs << '{ ';

	for (int i = 0; i < size; i++) {
		ofs << arr[i];

		if (i != size - 1) {
			ofs << ',';
		}
	}

	ofs.close();
}



void selectionSort(int* arr, size_t size) {
	for (int i = 0; i < size - 1; i++) {
		int minElIndex = i;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[minElIndex]) {
				minElIndex = j;
			}
		}

		if (minElIndex != i) {
			std::swap(arr[minElIndex], arr[i]);
		}
	}
}

FileReader* getFileReader(const MyString& str) {  //ReaderFactory
	FilePath path(str);
	if (path.getExtension() == ".dat") {
		return new BinaryFileReader(str);  //we create NEW FileReader
	}
	if (path.getExtension() == ".csv") {
		return new CSVFileReader(str);
	}
	if (path.getExtension() == ".arr") {
		return new ArrFileReader(str);
	}
	throw std::exception();
}

FileWriter* getFileWriter(const MyString& str) {  //WriterFactory
	FilePath path(str);
	if (path.getExtension() == ".dat") {
		return new BinaryFileWriter(str);
	}
	if (path.getExtension() == ".csv") {
		return new CSVFileWriter(str);
	}
	if (path.getExtension() == ".arr") {
		return new ArrFileWriter(str);
	}
	throw std::exception();
}

void transfer(const MyString& in, const MyString& out) {
	size_t size;

	FileReader* reader = getFileReader(in);
	int* arr = reader->read(size);

	selectionSort(arr, size);

	FileWriter* writer = getFileWriter(out);
	writer->write(arr, size);

	delete[] arr;
	delete reader;
	delete writer;
}

int main() {
	transfer("numbers.dat", "numbers2.arr");
}
