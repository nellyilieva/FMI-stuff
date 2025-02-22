#include <iostream>

template <class T>
unsigned partition(T* arr, unsigned len) {
	T pivot = arr[len / 2];

	int s = 0;
	int e = len - 1;

	while (true) {
		while (arr[s] < pivot) {
			s++;
		}

		while (arr[e] > pivot) {
			e--;
		}

		if (s >= e) {    //start and end do not meet
			break;
		}

		if (arr[s] == arr[e]) {
			s++;
		}

		std::swap(arr[s], arr[e]);
	}

	return s;
}

template <class T>
void quickSort(T* arr, unsigned len) {
	if (len <= 1) {
		return;
	}

	int pIdx = partition(arr, len);
	quickSort(arr, pIdx);
	quickSort(arr + pIdx + 1, len - pIdx - 1);
}


int main()
{

}
