#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)
#include "MyString.h"

//!! we don't have MyString object in the members of StingView !!
//we have 3 constructors: takes begin and end; takes c-style string; takes MyString object
//method to return size
//operator[]
//substr
//ostream
class StringView {
private:
	const char* begin;  //!! const !!
	const char* end;  //1 element after the final char

public:
	StringView(const char* begin, const char* end);
	StringView(const char* str);  //terminated string
	StringView(const MyString& str);

	size_t length() const;
	char operator[](size_t idx) const;

	StringView substr(size_t from, size_t length) const;
	friend std::ostream& operator<<(std::ostream& os, const StringView& strView);
};

