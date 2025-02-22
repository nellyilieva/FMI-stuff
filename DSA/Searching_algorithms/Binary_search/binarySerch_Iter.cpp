#include <iostream>
#include <vector>

//sorted data

template <class T>
int binarySearch(const std::vector<T>& data, const T& el) {
	int left = 0;
	int right = data.size() - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (data[mid] == el) {
			return mid;
		}
		else if (data[mid] < el) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return -1;
}

template <typename Iterator, typename T>
Iterator binarySearch(Iterator begin, Iterator end, const T& el) {
	Iterator left = begin;
	Iterator right = end;

	while (left < right) {
		Iterator mid = left + std::distance(left, right) / 2;

		if (*mid == el) {
			return mid;
		}
		else if (*mid < el) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}
	return end;     //the element is not in data
}

int main()
{

}