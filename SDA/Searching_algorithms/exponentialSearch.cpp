#include <iostream>
#include <vector>

//sorted data
//for searching elements at the begining of the data -> O(log(i))
//when we don't know the the size of the data (streams)

int binarySearchRecursive(const std::vector<int>& arr, int l, int r, int x) {
	if (r >= l) {
		int mid = l + (r - l) / 2;
		if (arr[mid] == x)
			return mid;
		if (arr[mid] > x)
			return binarySearchRecursive(arr, l, mid - 1, x);
		return binarySearchRecursive(arr, mid + 1, r, x);
	}
	return -1;
}

int exponentialSearch(std::vector<int>& data, int el) {
	int n = data.size();

	if (data[0] == el) {
		return 0;
	}

	int i = 1;
	while (i <= n && data[i] <= el) {
		i *= 2;
	}

	int left = i / 2;
	int right = std::min(i, n - 1);

	return binarySearchRecursive(data, left, right, el);
}

int main()
{
   
}