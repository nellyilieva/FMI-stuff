#include <iostream>
#include "StringView.h"

StringView::StringView(const char* str) : StringView(str, str + strlen(str)) {}

StringView::StringView(const String& obj) : StringView(obj.c_str()) {}

StringView::StringView(const char* newBegin, const char* newEnd) : begin(newBegin), end(newEnd) {}

size_t StringView::size() const{
	return end - begin;
}

char StringView::operator[](size_t idx) const{
	//check idx
	return begin[idx];
}

StringView StringView::substr(size_t fromIdx, size_t size) const {
	if (begin + fromIdx + size > end) {
		throw std::logic_error("Out of range");
	}

	return StringView(begin + fromIdx, begin + fromIdx + size);
}

std::ostream& operator<<(std::ostream& os, const StringView& view) {
	const char* iter = view.begin;

	while (iter != view.end) {
		os << *iter;
		iter++;
	}

	return os;
}

int compare(const StringView& lhs, const StringView& rhs) {
	const char* lhsIter = lhs.begin;
	const char* rhsIter = rhs.end;

	while (lhsIter != lhs.end && rhsIter != rhs.end) {
		if (*lhsIter != *rhsIter) {
			break;
		}

		lhsIter++;
		rhsIter++;
	}

	if (lhsIter == lhs.end && rhsIter == rhs.end) {
		return 0;
	}
	else if (lhsIter == lhs.end && rhsIter != rhs.end) {
		return -1;
	}
	else if (lhsIter != lhs.end && rhsIter == rhs.end) {
		return 1;
	}
	else {
		return *lhsIter - *rhsIter;
	}
}

bool operator<(const StringView& lhs, const StringView& rhs)
{
	return compare(lhs, rhs) < 0;
}

bool operator<=(const StringView& lhs, const StringView& rhs)
{
	return compare(lhs, rhs) <= 0;
}

bool operator>=(const StringView& lhs, const StringView& rhs)
{
	return compare(lhs, rhs) >= 0;
}

bool operator>(const StringView& lhs, const StringView& rhs)
{
	return compare(lhs, rhs) > 0;
}

bool operator==(const StringView& lhs, const StringView& rhs)
{
	return compare(lhs, rhs) == 0;
}

bool operator!=(const StringView& lhs, const StringView& rhs)
{
	return compare(lhs, rhs) != 0;
}

int main() {

}