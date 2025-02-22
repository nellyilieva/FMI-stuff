#include <iostream>
#include "ImmutableString.h"

//!!!!!!!
StringPool ImmutableString::pool;

//we use getString function from pool which finds the string and acording to refCount manages the string
void ImmutableString::copyFrom(const ImmutableString& other) {
	data = pool.getString(other.data);
	length = other.length;
}

void ImmutableString::free() {
	pool.removeString(data);
	data = nullptr;
}

ImmutableString::ImmutableString() : ImmutableString("") {}


ImmutableString::ImmutableString(const char* data) {
	data = pool.getString(data);
	length = strlen(data);
}

ImmutableString::ImmutableString(const ImmutableString& other) {
	copyFrom(other);
}

ImmutableString::~ImmutableString() {
	free();
}

size_t ImmutableString::getLength() const {
	return length;
}

char ImmutableString::operator[](size_t idx) const {
	return data[idx];
}

const char* ImmutableString::c_str() const {
	return data;
}

std::ostream& operator<<(std::ostream& os, const ImmutableString& str) {
	return os << str.c_str();
}

bool operator<(const ImmutableString& lhs, const ImmutableString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const ImmutableString& lhs, const ImmutableString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const ImmutableString& lhs, const ImmutableString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator>(const ImmutableString& lhs, const ImmutableString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator==(const ImmutableString& lhs, const ImmutableString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}
