#include <iostream>
#include "ImmutableString.h"

StringPool ImmutableString::pool;

ImmutableString::ImmutableString() : ImmutableString("") {}

ImmutableString::ImmutableString(const char* str) {
	data = pool.getString(str);
	size = strlen(data);
}

ImmutableString::ImmutableString(const ImmutableString& other) {
	size = other.size;
	data = pool.getString(other.data);
}

ImmutableString& ImmutableString::operator=(const ImmutableString& other) {
	if (this != &other) {
		pool.removeString(other.data);
		data = pool.getString(other.data);
		size = other.size;
	}

	return *this;
}

ImmutableString::~ImmutableString() {
	pool.removeString(data);
}

const char* ImmutableString::c_str() const {
	return data;
}

size_t ImmutableString::getSize() const {
	return size;
}

bool ImmutableString::empty() const {
	return size == 0;
}

char ImmutableString::operator[](size_t idx) const {
	if (idx >= size) {
		throw std::out_of_range("Out of range");
	}

	return data[idx];
}

bool operator==(const ImmutableString& lhs, const ImmutableString& rhs) {
	//we compare the pointers
	return lhs == rhs;
}

bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs) {
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const ImmutableString& str) {
	return os << str.c_str();
}
