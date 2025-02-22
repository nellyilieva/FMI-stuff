#include <iostream>
#include <vector>

//sorted data
//we use it to minimize nunmber of steps back; steps back is slow operation -> O(sqrt(n))
//we use linear search for the range, because binary search makes more steps back

int jumpSearch(const std::vector<int>& data, int el) {
	int n = data.size();
	int jump = sqrt(n);    //optimal
	int left = 0;
	int right = left + jump;

	while (right < n && data[right] <= el) {
		left = right;
		right += jump;

		if (right > n - 1) {
			right = n;
		}
	}

	for (int i = left; i < right; i++) {   //linear search
		if (data[i] == el) {
			return i;
		}
	}

	return -1;
}


int main()
{
   
}