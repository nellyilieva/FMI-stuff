#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)
#include "MyString.h"


void MyString::copyFrom(const MyString& other) {
	str = new char[other.length + 1];
	strcpy(str, other.str);
	length = other.length;
}

void MyString::free() {
	delete[] str;
	str = nullptr;
	length = 0;
}

MyString::MyString(size_t length) : length(length) {
	str = new char[length + 1];
}

MyString::MyString() : MyString(size_t(0)) {
	str[0] = '\0';
}

MyString::MyString(const char* str) : MyString(str ? strlen(str) : 0) {
	if (!str) {
		this->str[0] = '\0';
	}

	else {
		strcpy(this->str, str);
	}
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

size_t MyString::getLength() const {
	return length;
}

const char* MyString::c_str() const {
	return str;
}


int main() {
	MyString str1("abcd");

	MyString str2("efgh");

	MyString str3 = str1;

	str3 = "aaa";  //first constructor for "aaa", them operator=

}