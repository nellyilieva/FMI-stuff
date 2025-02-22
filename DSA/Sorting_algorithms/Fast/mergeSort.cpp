#include <iostream>

template <class T>
void merge(T* arr1, unsigned len1, T* arr2, unsigned len2, T* result) {
	int f = 0;
	int s = 0;
	int r = 0;

	while (f < len1 && s < len2) {
		result[r++] = (arr1[f] < arr2[s] ? arr1[f++] : arr2[s++]);
	}

	while (f < len1) {
		result[r++] = arr1[f++];
	}

	while (s < len2) {
		result[r++] = arr2[s++];
	}
}

template <class T>
void mergeSortStep(T* arr, unsigned len, T* buffer) {
	if (len <= 1) {
		return;
	}

	int mid = len / 2;
	mergeSortStep(arr, mid, buffer);
	mergeSortStep(arr + mid, len - mid, buffer + mid);
	merge(arr, mid, arr + mid, len - mid, buffer);

	for (int i = 0; i < len; i++) {
		arr[i] = buffer[i];
	}
}

template <class T>
void mergeSort(T* arr, unsigned len) {
	if (!arr || len == 0) {
		return;
	}

	T* buffer = new T[len];
	mergeSortStep(arr, len, buffer);

	delete[] buffer;
}


int main()
{

}
