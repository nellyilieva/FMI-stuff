#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)
#include "MyString.h"


//resize function -> we need to allocate memory for the string; !! change the capacity !!
static unsigned roundToPowerOfTwo(unsigned v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLen) {
	return std::max(roundToPowerOfTwo(stringLen + 1), 16u);
}

void MyString::resize(unsigned newAllocateDataSize) {
	char* newData = new char[newAllocateDataSize + 1];
	std::strcpy(newData, data);

	delete[] data;
	data = newData;
	capacity = newAllocateDataSize;  //!!!
}

void MyString::copyFrom(const MyString& other) {
	size = other.size;
	capacity = other.capacity;

	data = new char[other.capacity];
	std::strcpy(data, other.data);
}

void MyString::free() {
	delete[]data;
	data = nullptr;
	size = capacity = 0;
}

//explicit constructor -> set the capacity; !! null terminator !!
MyString::MyString(size_t length) {
	capacity = dataToAllocByStringLen(length);

	data = new char[capacity];
	size = 0;
	data[0] = '\0';   //!!!
}


//deafult constructor -> using constructor with parametars -> const char*
MyString::MyString() : MyString("") {}

//const char* constructor -> find the size and capacity and so on
MyString::MyString(const char* data) {
	size = std::strlen(data);
	capacity = dataToAllocByStringLen(size);
	this->data = new char[capacity];
	std::strcpy(this->data, data);
}

MyString::MyString(const MyString& other) {
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MyString::~MyString() {
	free();
}

const char* MyString::c_str() const {
	return data;
}

size_t MyString::getSize() const {
	return size;
}

size_t MyString::getCapacity() const {
	return capacity;
}

//first check capacity; stncat, because the terminating zero of str will be destroyed by the first char
MyString& MyString::operator+=(const MyString& str) {
	if (getSize() + str.getSize() + 1 > capacity) {
		resize(dataToAllocByStringLen(getSize() + str.getSize()));
	}

	std::strncat(data, str.data, str.getSize());

	size = getSize() + str.getSize();
	return *this;
}

char& MyString::operator[] (size_t idx) {
	return data[idx];
}

const char& MyString::operator[](size_t idx) const {
	return data[idx];
}

std::ostream& operator<<(std::ostream& os, const MyString& obj) {
	return os << obj.data;
}

//reading -> we read the buff and find the size; change the capacity if needed and so ons
std::istream& operator>>(std::istream& is, MyString& obj) {
	char buff[1024];
	is >> buff;
	size_t buffSize = std::strlen(buff);

	if (buffSize > obj.capacity) {
		obj.resize(dataToAllocByStringLen(buffSize));
	}

	strcpy(obj.data, buff);
	obj.size = buffSize;

	return is;
}


//we use the explicit constructor
MyString operator+(const MyString& lhs, const MyString& rhs) {
	MyString result(lhs.getSize() + rhs.getSize()); //!!!

	result += lhs;
	result += rhs;

	return result;
}

//c_str -> the get function for data
bool operator==(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

int main() {
	

}