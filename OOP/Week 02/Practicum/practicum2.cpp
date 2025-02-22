#include <iostream>
#include <fstream>
#include <sstream>

struct FileData {
	int* arr = nullptr;
	size_t arrSize = 0;
};

void freeFileData(FileData& data) {
	delete[] data.arr;

	data.arr = nullptr;
	data.arrSize = 0;
}

size_t getFileSize(std::ifstream& ifs) {
	size_t currPos = ifs.tellg();

	ifs.seekg(0, std::ios::end);
	size_t fileSize = ifs.tellg();

	ifs.seekg(currPos, std::ios::beg);

	return fileSize;
}

bool isPrime(int n) {
	if (n == 0 || n == 1) {
		return false;
	}

	for (int i = 0; i < n / 2; i++) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

//FileData readData(std::ifstream& ifs) {
//	size_t fileSize = getFileSize(ifs);
//	size_t arraySize = fileSize / sizeof(int);
//
//	int* arr = new int[arraySize];
//	ifs.read((char*)arr, fileSize);
//
//	return { arr, arraySize };
//}

void divideNumbersToFiles(const char* sourseFile, const char* primeFile, const char* complexFile) {
	std::ifstream file(sourseFile, std::ios::binary);

	if (!file.is_open()) {
		return;
	}

	std::ofstream prime(primeFile, std::ios::binary);

	if (!prime.is_open()) {
		file.close();
		return;
	}

	std::ofstream complex(complexFile, std::ios::binary);

	if (!complex.is_open()) {
		file.close();
		prime.close();
		return;
	}

	//FileData data = readData(file);

	//file.close();

	//for (int i = 0; i < data.arrSize; i++) {
	//	if (isPrime(data.arr[i])) {
	//		prime.write((const char*)&data.arr[i], sizeof(data.arr[i])); //not a very good code, because we write more than once
	//	}                                                                //while we can use write only once

	//	else {
	//		complex.write((const char*)&data.arr[i], sizeof(data.arr[i]));
	//	}
	//}

	//freeFileData(data);

	int number;

	while (file.read((char*)&number, sizeof(number))) {
		if (isPrime(number)) {
			prime.write((const char*)&number, sizeof(number));
		}
		else {
			complex.write((const char*)&number, sizeof(number));
		}
	}

	file.close();
	prime.close();
	complex.close();
}


//constexpr int BYTES_COUNT = 256;
//
//struct FileData2 {
//	unsigned char* buff = nullptr;
//	size_t fileSize = 0;
//};
//
//void freeFileData2(FileData2& data) {
//	delete[] data.buff;
//
//	data.buff = nullptr;
//	data.fileSize = 0;
//}
//
////in getFileContent function we fill the buffer with the information from the file
//
//FileData2 getFileContent(const char* fileName) {
//	std::ifstream file(fileName, std::ios::binary);
//
//	if (!file.is_open()) {
//		return {};
//	}
//
//	size_t fileSize = getFileSize(file);
//	unsigned char* buff = new unsigned char[fileSize]; //create buffer
//
//	file.read((char*)buff, fileSize); //fill buffer
//	file.close();
//
//	return { buff, fileSize };
//}
//
//void printMissingBytes(const FileData2& data) {
//	int counter[BYTES_COUNT] = { 0 };  //we create array of ints with size 256 which is max bytes
//
//	for (int i = 0; i < data.fileSize; i++) {   //count how many times we meet each byte and the value to the counter array
//		counter[data.buff[i]]++;
//	}
//
//	for (int i = 0; i < BYTES_COUNT; i++) {          //iterate through the counter array and check if any byte cout is 0
//		if (counter[i] == 0) {                       //meaning is missing
//			std::cout << i << "is missing" << std::endl;
//		}
//	}
//}

typedef unsigned char byte;

void unusedBytes(const char* filename) {
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open()) {
		return;
	}

	int byteCounts[256] = { 0 }; //could also be bool array

	byte b;

	while (file.read((char*)&b, sizeof(b))) {
		byteCounts[b]++;
	}

	file.close();

	int count = 0;
	for (byte i = 0; i < 256; i++) {
		if (byteCounts[i] == 0) {
			count++;
		}
	}
}


const int MAX_CHAR_TITLE = 128;
const int MAX_BOOKS_COUNT = 1024;
const int MAX_TEXT_LINE_LENGTH = 256;

struct Book {
	char title[MAX_CHAR_TITLE + 1];
	unsigned int year;
	double price;
};

//dynamic array

//size_t getFileSize(std::ifstream& ifs) {
//	size_t currPos = ifs.tellg();
//
//	ifs.seekg(0, std::ios::end);
//	size_t fileSize = ifs.tellg();
//
//	ifs.seekg(currPos, std::ios::beg);
//
//	return fileSize;
//}
//
//unsigned getCharCountFromFile(std::ifstream& ifs, char ch) {
//	unsigned int count = 0;
//
//	while (true)
//	{
//		char current = ifs.get();
//		if (ifs.eof())
//			break;
//
//		if (current == ch)
//			count++;
//	}
//
//	return count;
//}
//
//Book readBook(std::ifstream& ifs) {
//	Book book;
//
//	ifs >> book.title >> book.year >> book.price;
//
//	return book;
//}
//
//Book* saveBooksInArray(std::ifstream& ifs, int countOfBooks) {
//	Book* books = new Book[countOfBooks];
//
//	if (!ifs.is_open()) {
//		return {};
//	}
//
//	for (int i = 0; i < countOfBooks; i++) {
//		books[i] = readBook(ifs);
//	}
//
//	ifs.close();
//	return books;
//}
//
//void deleteBooks(Book*& books) {
//	delete[] books;
//}
//
//struct FileData {
//	int* arr = nullptr;
//	size_t arrSize = 0;
//};
//
//FileData readData(std::ifstream& ifs) {
//	size_t fileSize = getFileSize(ifs);
//	size_t arraySize = fileSize / sizeof(int);
//
//	int* arr = new int[arraySize];
//	ifs.read((char*)arr, fileSize);
//
//	return { arr, arraySize };
//}
//
//void freeFileData(FileData& data) {
//	delete[] data.arr;
//
//	data.arr = nullptr;
//	data.arrSize = 0;
//}
//
//void writeBooks(const char* textFile, const char* yearFile, const char* bookFile) {
//	std::ifstream file(textFile);
//
//	if (!file.is_open()) {
//		return;
//	}
//
//	int countOfBooks = getCharCountFromFile(file, '\n') + 1;
//	Book* books = saveBooksInArray(file, countOfBooks);
//
//	file.close();
//
//	std::ifstream year(yearFile, std::ios::binary);
//
//	if (!year.is_open()) {
//		deleteBooks(books);
//		return;
//	}
//
//	std::ofstream newFile(bookFile, std::ios::binary);
//
//	if (!newFile.is_open()) {
//		deleteBooks(books);
//		year.close();
//		return;
//	}
//
//	FileData data = readData(year);
//
//	for (int i = 0; i < countOfBooks; i++) {
//		for (int j = 0; j < data.arrSize; j++) {
//			if (data.arr[j] == books[i].year) {
//				newFile.write((const char*)&books[i], sizeof(books[i]));
//				break;
//			}
//		}
//	}
//
//	year.close();
//	newFile.close();
//	deleteBooks(books);
//	freeFileData(data);
//}


//We have a static array of books and their count. Every book is written on one line, so we get every line (with getline).
//Then we use stringstream on every line to write the book and its info in the array. And find the count of the books.
//Then we open our binary file with years. We have to check which years are the same.
// We create bool array which takes value true if the book on that position is in the books array. We read every year and check.
//Then write the books in new binary file.

void writeBooks(const char* name) {
	std::ifstream file(name);

	if (!file.is_open()) {
		return;
	}

	Book books[MAX_BOOKS_COUNT];
	int booksCount = 0;

	char line[MAX_TEXT_LINE_LENGTH];
	while (file.getline(line, MAX_TEXT_LINE_LENGTH)) {
		std::stringstream ss(line);

		ss >> books[booksCount].title >> books[booksCount].year >> books[booksCount].price;
		booksCount++;
	}

	file.close();

	std::ifstream yearFile("years.dat", std::ios::binary);

	if (!yearFile.is_open()) {
		return;
	}

	bool toBeIncluded[MAX_BOOKS_COUNT] = { false };
	int year;

	while (yearFile.read((char*)&year, sizeof(year))) {
		for (int i = 0; i < booksCount; i++) {
			if (books[i].year == year) {
				toBeIncluded[i] = true;
			}
		}
	}

	yearFile.close();

	std::ofstream booksToWrite("books.dat", std::ios::binary);

	if (!booksToWrite.is_open()) {
		return;
	}

	for (int i = 0; i < booksCount; i++) {
		if (toBeIncluded[i]) {
			booksToWrite.write((const char*)&books[i], sizeof(books[i]));
		}
	}

	booksToWrite.close();
}


int main()
{
	/*FileData2 data = getFileContent("test.dat");

	printMissingBytes(data);

	freeFileData2(data);*/
}
