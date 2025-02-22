#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)
#include "MyString.h"

class StringVector {
private:
	MyString* strings;
	size_t size;
	size_t capacity;

	void resize(unsigned newCapacity);

	void copyFrom(const StringVector& other);
	void free();

public:
	StringVector();

	StringVector(const StringVector& other);
	StringVector& operator=(const StringVector& other);

	~StringVector();

	size_t getSize() const;
	size_t getCapacity() const;

	void push_back(const MyString& str);
	void pop_back();
	void insert(const MyString& str, size_t idx);
	void erase(size_t idx);

	void clear();

	MyString& operator[] (size_t idx);
	const MyString& operator[](size_t idx) const;

	bool empty() const;

	friend std::ostream& operator<<(std::ostream& os, const StringVector& data);
	friend std::istream& operator>>(std::istream& is, StringVector& data);
};
