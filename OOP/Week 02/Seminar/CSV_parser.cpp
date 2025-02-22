#include <iostream>
#include <fstream>
#include <sstream>


namespace GlobalConstants {
	constexpr int FILED_MAX_SIZE = 30;
	constexpr int MAX_FIELDS_ROW = 10;
	constexpr int ROWS_MAX_SIZE = 300;
	constexpr int BUFFER_SIZE = 1024;
	constexpr char SEP = ',';
}

typedef char Field[GlobalConstants::FILED_MAX_SIZE];
typedef Field Row[GlobalConstants::MAX_FIELDS_ROW];

//struct Field {
//	char data[GlobalConstants::FILED_MAX_SIZE];
//};
//
//struct Row {
//	Field fields[GlobalConstants::MAX_FIELDS_ROW];
//};

struct CsvTable {
	Row rows[GlobalConstants::ROWS_MAX_SIZE];
	size_t rowsCount = 0;
	size_t collsCount = 0;
};

size_t parseRow(const char* row, Row& r) {
	std::stringstream ss(row);

	size_t currColumnCount = 0;

	while (!ss.eof()) {
		ss.getline(r[currColumnCount++], GlobalConstants::FILED_MAX_SIZE, GlobalConstants::SEP);
	}

	return currColumnCount;
}

CsvTable parseFromFile(std::istream& is) {
	CsvTable result;
	char rowStr[GlobalConstants::BUFFER_SIZE];  //for a line in the table

	while (!is.eof()) {
		is.getline(rowStr, GlobalConstants::BUFFER_SIZE, '\n');   //read a line from the stream to rowStr
		result.collsCount = parseRow(rowStr, result.rows[result.rowsCount++]);   //parse the line
	}

	return result;
}

CsvTable parseFromFile(const char* fileName) {
	std::ifstream ifs(fileName);

	if (!ifs.is_open()) {
		return {};
	}

	return parseFromFile(ifs);
}

void printTable(const CsvTable& table) {
	for (int i = 0; i < table.rowsCount; i++) {
		for (int j = 0; j < table.collsCount; j++) {
			std::cout << table.rows[i][j] << "    ";
		}

		std::cout << std::endl;
	}
}

void saveRowToFile(std::ostream& os, const Row& row, size_t collsCount) {
	for (int i = 0; i < collsCount; i++) {
		os << row[i];

		if (i != collsCount - 1) {
			os << GlobalConstants::SEP;
		}
	}
}

void saveToFile(std::ostream& os, const CsvTable& table) {
	for (int i = 0; i < table.rowsCount; i++) {
		saveRowToFile(os, table.rows[i], table.collsCount);

		if (i != table.rowsCount - 1) {
			os << std::endl;
		}
	}
}

void saveToFile(const char* fileName, const CsvTable& table) {
	std::ofstream ofs(fileName);
	saveToFile(ofs, table);
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
