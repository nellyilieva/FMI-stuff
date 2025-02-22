#include <iostream>
#include <vector>

template <class T>
int binarySearch(const std::vector<T>& arr, const T& el, int left, int right) {
	if (left <= right) {
		int mid = left + (right - left) / 2;

		if (arr[mid] == el) {
			return mid;
		}
		else if (arr[mid] < el) {
			return binarySearch(arr, el, mid + 1, right);
		}
		else {
			return binarySearch(Arr, el, left, mid - 1);
		}
	}
	return -1;
}



int main()
{

}