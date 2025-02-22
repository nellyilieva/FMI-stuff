#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)
#include "StringPool.h"

//idk it looks like unique pointer (to manage dynamic memory), but here is StringPool to manage immutable strings

class ImmutableString {
private:
	const char* data;  //we won't change it => const
	size_t length;

	static StringPool pool;  //one for all objects; !! we need to initialize it !!
							// !! we have arr of data in the pool -> static -> only one !!

	void copyFrom(const ImmutableString& other);
	void free();

public:
	ImmutableString();

	ImmutableString(const char* data);
	ImmutableString(const ImmutableString& other);
	ImmutableString& operator=(const ImmutableString& other) = delete;

	~ImmutableString();

	size_t getLength() const;
	char operator[](size_t idx) const;
	const char* c_str() const;
};

std::ostream& operator<<(std::ostream& os, const ImmutableString& str);

bool operator<(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator<=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator>=(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator>(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator==(const ImmutableString& lhs, const ImmutableString& rhs);
bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs);