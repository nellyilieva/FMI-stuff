#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

const int MAX_SIZE_FIELD = 30;
const int MAX_COUNT_FILEDS = 10;
const int MAX_COUNT_ROWS = 300;
const char SEP = ',';
const int BUFF_SIZE = 1024;


typedef char Field[MAX_SIZE_FIELD];

struct Row {
    Field fields[MAX_COUNT_FILEDS];
};

struct CSVTable {
    Row rows[MAX_COUNT_ROWS];
    int countRows = 0;
    int countColls = 0;
};


size_t parseRow(const char* row, Row& rowToReturn) {
    std::stringstream ss(row);

    size_t currColl = 0;

    while (!ss.eof()) {
        ss.getline(rowToReturn.fields[currColl], MAX_SIZE_FIELD, SEP);
        currColl++;
    }

    return currColl;
}

CSVTable parseFromFile(std::ifstream& ifs) {
    CSVTable result;

    char buff[BUFF_SIZE];

    while (ifs.eof()) {
        ifs.getline(buff, BUFF_SIZE);
        result.countColls = parseRow(buff, result.rows[result.countRows]);
        result.countRows++;
    }

    return result;
}

CSVTable parseFromFile(const char* fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "not open" << std::endl;
        return {};
    }

    return parseFromFile(file);
}

void printTable(const CSVTable& table) {
    for (int i = 0; i < table.countRows; i++) {
        for (int j = 0; j < table.countColls; j++) {
            std::cout << table.rows[i].fields[j] << " ";
        }
        std::cout << std::endl;
    }
}

void saveRowToFile(std::ofstream& ofs, const Row& row, size_t collsCount) {
    for (int i = 0; i < collsCount; i++) {
        ofs << row.fields[i];

        if (i != collsCount - 1) {
            ofs << SEP;
        }
    }
}

void saveToFile(std::ofstream& ofs, const CSVTable& table) {
    for (int i = 0; i < table.countRows; i++) {
        saveRowToFile(ofs, table.rows[i], table.countColls);

        if (i != table.countRows - 1) {
            ofs << std::endl;
        }
    }
}

void saveToFile(const char* fileName, const CSVTable& table) {
    std::ofstream file(fileName);

    saveToFile(file, table);
    file.close();
}

int getColumnIndex(const CSVTable& table, const char* columnName) {
    for (size_t i = 0; i < table.countColls; i++) {
        if (strcmp(table.rows[0].fields[i], columnName) == 0) {
            return i;
        }
    }

    return -1;
}

void modifyColumn(CSVTable& table, const char* columnName, const char* values, char separator) {
    int columnIndex = getColumnIndex(table, columnName);

    if (columnIndex == -1) {
        return;
    }

    std::stringstream ss(values);
    size_t rowIndex = 1;
    while (rowIndex < table.countRows && !ss.eof())
    {
        ss.getline(table.rows[rowIndex++].fields[columnIndex], MAX_SIZE_FIELD, separator);
    }
}


int main()
{
    CSVTable csv = parseFromFile("table.csv");

    modifyColumn(csv, "Ime", "Test1,Test2,Test3,Test4", ',');

    printTable(csv);
    //do something with the table....
    saveToFile("table_result.csv", csv);
}
