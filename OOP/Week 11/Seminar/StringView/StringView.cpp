#include "StringView.h"

StringView::StringView(const char* begin, const char* end) : begin(begin), end(end) {}

//we use (begin, end) constructor
StringView::StringView(const char* str) : StringView(str, str + std::strlen(str)) {}

//we use (const char*) constructor
StringView::StringView(const MyString& str) : StringView(str.c_str()) {}

size_t StringView::length() const {
	return end - begin;
}

char StringView::operator[](size_t idx) const {
	return begin[idx];     //because begin is pointer to the begining of the string
}

//we move the pointer from the begining of the string in order to construct our substring
StringView StringView::substr(size_t from, size_t length) const {
	if (begin + from + length > end) {
		throw std::length_error("Error, Substr out of range");
	}

	return StringView(begin + from, begin + from + length);
}

//we have iter; we iterate through every character until the end character and we write them
std::ostream& operator<<(std::ostream& os, const StringView& strView) {
	const char* iter = strView.begin;

	while (iter != strView.end) {
		os << *iter;
		iter++;
	}

	return os;
}