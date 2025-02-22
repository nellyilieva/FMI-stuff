#include <iostream>
#include <vector>

template <class T>
bool linearSearch(const T* arr, unsigned len, const T& el) {
	if (len == 0) {
		return false;
	}

	return *arr == el || linearSearch(arr + 1, len - 1, el);
}

template <typename Iterator, typename T>
Iterator linearSearch(Iterator begin, Iterator end, const T& el) {
	if (begin == end) {
		return end;     //empty => element not found
	}

	if (*begin == el) {   //first el
		return begin;
	}

	return linearSearch(begin + 1, end, el);
}

int main()
{

}