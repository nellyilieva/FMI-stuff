#include <iostream>
#include <vector>

//ternary search -> O(logn)
//- sorted and PARABOLIC data
//- good for finding min and max of a function
//- binary search is better because it makes less comparisons in worst case (look recursive functions)

int ternarySearchIter(const int* arr, int len, int el) {
	int left = 0;
	int right = len - 1;

	while (left <= right) {
		int mid1 = left + (right - left) / 3;
		int mid2 = right - (right - left) / 3;

		if (arr[mid1] == el) {
			return mid1;
		}

		if (arr[mid2] == el) {
			return mid2;
		}

		if (arr[mid1] > el) {
			right = mid1 - 1;
		}
		else if (arr[mid2] < el) {
			left = mid2 + 1;
		}
		else {
			left = mid1 + 1;
			right = mid2 - 1;
		}
	}
	return -1;
}

int ternarySearchRec(const int* arr, int left, int right, int el) {
	if (left <= right) {
		int mid1 = left + (right - left) / 3;
		int mid2 = right - (right - left) / 3;

		if (arr[mid1] == el) {
			return mid1;
		}

		if (arr[mid2] == el) {
			return mid2;
		}

		if (arr[mid1] > el) {
			return ternarySearchRec(arr, left, mid1 - 1, el);
		}
		else if (arr[mid2] < el) {
			return ternarySearchRec(arr, mid2 + 1, right, el);
		}
		else {
			return ternarySearchRec(arr, mid1 + 1, mid2 - 1, el);
		}
	}
	return -1;
}


int main()
{
   
}