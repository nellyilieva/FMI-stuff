#include <iostream>

template <class T>
void merge(T* arr1, unsigned len1, T* arr2, unsigned len2) {
	T* result = new T[len1 + len2];

	int f = 0;
	int s = 0;
	int r = 0;

	while (f < len1 && s < len2) {
		if (arr1[f] > arr2[s]) {
			result[r] = arr2[s];
			r++;
			s++
		}
		else {
			result[r] = arr1[f];
			r++;
			f++;
		}
	}

	while (f < len1) {
		result[r] = arr1[f];
		r++;
		f++;
	}

	while (s < len2) {
		result[r] = arr2[s];
		r++;
		s++;
	}

	for (int i = 0; i < len1 + len2; i++) {
		arr1[i] = result[i];
	}

	delete[] result;
}

template <class T>
void naiveMergeSort(T* arr, unsigned len) {
	if (len == 1) {
		return;
	}

	int mid = len / 2;
	naiveMergeSort(arr, mid);
	naiveMergeSort(arr + mid, len - mid);

	merge<T>(arr, mid, arr + mid, len - mid);
	
}

int main()
{

}
