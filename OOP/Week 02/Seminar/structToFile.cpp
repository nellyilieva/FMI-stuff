#include <iostream>
#include <fstream>
#include <sstream>

void copyData(const char* fileName, const char* fileDestination) {
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		std::cout << "Can't open!";
		return;
	}

	std::ofstream ofs(fileDestination);

	if (!ofs.is_open()) {
		std::cout << "Can't open!";
		return;
	}

	char buffer[1024];

	while (!ifs.eof()) {
		ifs.getline(buffer, 1024);
		ofs << buffer << std::endl;
	}

	ifs.close();
	ofs.close();
}


enum class Major {
	undefined,
	IS,
	SI,
	KN
};

struct Student {
	char name[100] = "";
	unsigned fn = 0;
	Major major = Major::undefined;
};

const int MAX_SIZE = 10;

struct StudentsDatabase {
	Student students[MAX_SIZE];
	unsigned count = 0;
};

void serializeStudent(std::ostream& os, const Student& s) {
	os << s.name << std::endl << s.fn << std::endl << (int)s.major << std::endl;
}

void serializeDatabase(std::ostream& os, const StudentsDatabase& db) {
	os << db.count << std::endl;

	for (int i = 0; i < db.count; i++) {
		serializeStudent(os, db.students[i]);
	}
}

void deserializeStudent(std::istream& is, Student& s) {
	is.ignore();
	is.getline(s.name, 100);
	is >> s.fn;
	int tempMajor;
	is >> tempMajor;
	s.major = (Major)tempMajor;
}

StudentsDatabase deserializeDatabase(std::istream& is) {
	StudentsDatabase db;

	is >> db.count;
	for (int i = 0; i < db.count; i++) {
		deserializeStudent(is, db.students[i]);
	}

	return db;
}


int getCharCount(std::ifstream& ifs, char ch) {
	int curr = ifs.tellg();

	ifs.seekg(0, std::ios::beg);

	if (!ifs.is_open()) {
		return 0;
	}

	int count = 0;

	while (true) {
		int currCh = ifs.get();

		if (ifs.eof()) {
			break;
		}

		if (currCh == ch) {
			count++;
		}
	}

	ifs.clear();
	ifs.seekg(curr);

	return count;
}

int* getArrFromFile(const char* fileName, int& arrSize) {
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return nullptr;
	}

	arrSize = getCharCount(ifs, ' ') + 1;
	int* result = new int[arrSize];

	for (int i = 0; i < arrSize; i++) {
		ifs >> result[i];
	}

	ifs.close();
	return result;
}

int* merge(const int* first, int firstSize, const int* second, int secondSize) {
	int* result = new int[firstSize + secondSize];

	int iterFirst = 0;
	int iterSecond = 0;
	int iterMerged = 0;

	while (iterFirst < firstSize && iterSecond < secondSize) {
		if (first[iterFirst] <= second[iterSecond]) {
			result[iterMerged] = first[iterFirst];
			iterMerged++;
			iterFirst++;
		}
		else {
			result[iterMerged] = second[iterSecond];
			iterMerged++;
			iterSecond++;
		}
	}

	while (iterFirst < firstSize) {
		result[iterMerged] = first[iterFirst];
		iterMerged++;
		iterFirst++;
	}

	while (iterSecond < secondSize) {
		result[iterMerged] = second[iterSecond];
		iterMerged++;
		iterSecond++;
	}

	return result;
}

void mergeFromFile(const char* first, const char* second, const char* result) {
	int firstSize;
	int secondSize;

	int* firstArr = getArrFromFile(first, firstSize);
	if (!firstArr) {
		return;
	}

	int* secondArr = getArrFromFile(second, secondSize);
	if (!secondArr) {
		delete[] firstArr;   //!!!!!
 		return;
	}

	int* resultArr = merge(firstArr, firstSize, secondArr, secondSize);

	std::ofstream ofs(result);

	if (!ofs.is_open()) {
		delete[] firstArr;
		delete[] secondArr;
		delete[] resultArr;
		return;
	}

	for (int i = 0; i < firstSize + secondSize; i++) {
		ofs << result[i] << " ";
	}

	delete[] firstArr;
	delete[] secondArr;
	delete[] resultArr;

	ofs.close();
}

int main() {
	

	std::ifstream ifs("seminar.cpp");

	if (!ifs.is_open()) {
		std::cout << "Can't open!";
	}

	char buff[1024];

	while (!ifs.eof()) {
		ifs.getline(buff, 1024);
		std::cout << buff << std::endl;
	}

	ifs.close();
}
