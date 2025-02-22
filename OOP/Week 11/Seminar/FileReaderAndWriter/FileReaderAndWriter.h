#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)
#include "MyString.h"

//file read and write
//Масив може да бъде сериализиран по няколко начина :
//
//В двоичен файл(с разширение.dat).
//Csv формат(с разширение.csv).Числата са разделени със запетаи. (Например : 3, 4, 5, 6)
//Arr формат(с разширение.arr).Започваме със скоба, между числата може да има произволен брой интервали и приключваме със скоба. (Например : [3 4 12 4]
//Напишете програма, която приема като вход имена на два файла - входен и изходен.
//Програмата трябва да сортира масива от входиния файл и да го запази в изходния файл.
//Форматите на файловете се определят от тяхното разширение.

//polymorphism -> one name, but many different implementations
// !! Едни и същи действия се реализират по различен начин, в зависимост от обектите, върху които се прилагат !!
//here this will be the reading and the writing

//first we need to find of what type are the files -> abstract class FileReader with filePath member
//filePath member -> it contains two things -> name and extension; how we get the name and the extension from filePath?
//we need this for factory reader factory and writer factory (the creation of the file types)

class FilePath {
private:
	MyString name;
	MyString extension;

public:
	FilePath(const MyString& fileName);
	const MyString& getName() const;
	const MyString& getExtension() const;
};

class FileReader {
protected:   //!!!
	MyString filePath;

public:
	FileReader(const MyString& filePath);

	//pure virtual function
	virtual int* read(size_t& size) const = 0;

	virtual ~FileReader() = default;
};

//now we create the different types of FileReader -> arr, binary, csv
//for the different types we have different like helper functions according to the way we read the file

//for ArrFileReader we need to find the count of elements -> size of arr
class ArrFileReader : public FileReader {
private:
	static int getCharCount(std::ifstream& ifs, char ch);

public:
	ArrFileReader(const MyString& filePath);
	int* read(size_t& size) const override;  //return the arr; we read the arr from file; deserialize
};

//we need fileSize (binary file -> we know the exact size)
class BinaryFileReader : public FileReader {
private:
	static int getFileSize(std::ifstream& ifs);

public:
	BinaryFileReader(const MyString& filePath);
	int* read(size_t& size) const override;

};

class CSVFileReader : public FileReader {
private:
	static int getCharCount(std::ifstream& ifs, char ch);

public:
	CSVFileReader(const MyString& filePath);
	int* read(size_t& size) const override;
};


//after we have the read(deserialize) functions, we need to do the same for the write(serialize) functions

class FileWriter {
protected:
	MyString filePath;

public:
	FileWriter(const MyString& filePath);
	virtual void write(const int* srr, size_t size) const = 0;
	virtual ~FileWriter() = default;
};

class ArrFileWriter : public FileWriter {
public:
	ArrFileWriter(const MyString& filePath);
	void write(const int* arr, size_t size) const override;
};

class BinaryFileWriter : public FileWriter {
public:
	BinaryFileWriter(const MyString& filePath);
	void write(const int* arr, size_t size) const override;
};

class CSVFileWriter : public FileWriter {
public:
	CSVFileWriter(const MyString& filePath);
	void write(const int* arr, size_t size) const override;
};

//now we create the function; we need factory to create filereaders and fileWriters
