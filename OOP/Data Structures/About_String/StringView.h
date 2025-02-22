#pragma once
#include <iostream>
#include "String.h"

class StringView {
private:
	const char* begin;
	const char* end;

public:
	StringView(const char* str);

	StringView(const String& obj);

	StringView(const char* newBegin, const char* newEnd);

	size_t size() const;
	
	char operator[](size_t idx) const;

	StringView substr(size_t fromIdx, size_t size) const;

	friend std::ostream& operator<<(std::ostream& os, const StringView& view);

	friend int compare(const StringView& lhs, const StringView& rhs);
};

bool operator<(const StringView& lhs, const StringView& rhs);
bool operator<=(const StringView& lhs, const StringView& rhs);
bool operator>=(const StringView& lhs, const StringView& rhs);
bool operator>(const StringView& lhs, const StringView& rhs);
bool operator==(const StringView& lhs, const StringView& rhs);
bool operator!=(const StringView& lhs, const StringView& rhs);