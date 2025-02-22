#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)

class MyString {
private:
	char* data = nullptr;
	size_t size;
	size_t capacity;

	void resize(unsigned newAllocateDataSize);

	void copyFrom(const MyString& other);
	void free();

	explicit MyString(size_t length);

public:
	MyString();
	MyString(const char* data);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	~MyString();

	const char* c_str() const;

	size_t getSize() const;
	size_t getCapacity() const;

	MyString& operator+=(const MyString& str);

	char& operator[] (size_t idx);
	const char& operator[](size_t idx) const;

	friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
	friend std::istream& operator>>(std::istream& is, MyString& obj);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
};

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);