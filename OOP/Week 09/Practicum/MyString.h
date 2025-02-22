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

	void resize(unsigned newCapacity);

	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other);

	void free();

	explicit MyString(size_t size);

public:
	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	MyString(MyString&& other) noexcept;
	MyString& operator=(MyString&& other) noexcept;

	~MyString();

	size_t getSize() const;
	size_t getCapacity() const;

	const char* c_str() const;

	MyString& operator+=(const MyString& obj);

	char& operator[](size_t idx);
	const char& operator[](size_t idx) const;

	friend MyString operator+(const MyString& lhs, const MyString& rhs);
	friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
	friend std::istream& operator>>(std::istream& is, MyString& obj);
};

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);
bool operator<(const MyString& lhs, const MyString& rhs);
bool operator<=(const MyString& lhs, const MyString& rhs);
bool operator>(const MyString& lhs, const MyString& rhs);
bool operator>=(const MyString& lhs, const MyString& rhs);