#include <iostream>

template <class T>
void bubbleSort(T* arr, unsigned len) {    //optimized; in cases when arr is already/nearly sorted -> best_case O(n)
	size_t end = len - 1;

	for (size_t i = 0; i < len; i++) {
		size_t lastSwappedIdx = i;          //after lastSwappedIdx the array is sorted

		for (size_t j = 0; j < end; j++) {
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				lastSwappedIdx = j;
			}
		}

		end = lastSwappedIdx;

		if (lastSwappedIdx == 0) {      //arr is sorted
			return;
		}
	}
}


template <class T>
void selectionSort(T* arr, unsigned len) {
	for (size_t i = 0; i < len; i++) {
		int minElementIdx = i;

		for (size_t j = i + 1; j < len; j++) {         //look for smallest element here and swap it with i
			if (arr[j] < arr[minElementIdx]) {
				minElementIdx = j;
			}
		}

		if (i != minElementIdx) {
			std::swap(arr[i], arr[minElementIdx]);
		}
	}
}
//(10, 9, 8, 7, 6, 5, 4, 3, 2, 1 -> for reversed); min swaps

template <class T>
void naiveInsertionSort(T* arr, unsigned len) {       //left part is sorted, we place the current element in sorted part by swaping
	for (size_t i = 0; i < len; i++) {
		int idx = i;

		while (idx > 0 && arr[idx] < arr[idx - 1]) {
			std::swap(arr[idx], arr[idx - 1]);
			idx--;
		}
	}
}

template <class T>
void insertionSort(T* arr, unsigned len) {       //we don't swap the elements, we shift them to the right to make space for the current element
	for (size_t i = 0; i < len; i++) {
		T element = arr[i];
		int idx = i - 1;

		while (idx >= 0 && arr[idx] > element) {
			arr[idx + 1] = arr[idx];
			idx--;
		}

		arr[idx + 1] = element;
	}
}

int main()
{

}
