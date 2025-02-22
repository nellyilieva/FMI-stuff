#include <iostream>
#include <vector>

//std::upper_bound and std::lower_bound
//- we need sorted collection; based on binary search => O(logn); return iterators
//[first,last)

//int low = std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();     -> return idx
//int up = std::upper_bound(nums.begin(), nums.end(), target) - nums.begin() - 1;

// std::lower_bound
// auto lower = lower_bound(vec.begin(), vec.end(), target); 
// Returns an iterator to the first element that is >= the target value.
// Behavior: 
// - target is found -> iterator to the first occurrence of target
// - target is smaller than all elements -> it points to the first element
// - target is larger than the largest element -> it returns the end iterator

std::vector<int>::iterator lower(std::vector<int>::iterator begin, std::vector<int>::iterator end, int target) {
	int left = 0;
	int right = end - begin - 1;

	int result = 0;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (*(begin + mid) == target) {   //begin + mid because mid is int and we need pointer; begin and end are pointers; pointer arithmetics
			result = mid;
			right = mid - 1;   //we continue to search for el
		}
		if (*(begin + mid) < target) {
			left = mid + 1;
		}
		else {
			right = mid - 1;
		}
	}

	return begin + result;   //iterator pointing to the idx
}

// std::upper_bound
// auto upper = upper_bound(vec.begin(), vec.end(), target);
// Returns an iterator to the first element that is greater than the target value.
// Behavior: 
// - target is found -> iterator to the first element > the target value
// - target is larger than the largest element -> it returns the end iterator

int upper(std::vector<int>& nums, int target) {
	int left = 0;
	int right = nums.size();

	while (left < right) {
		int mid = left + (right - left) / 2;

		if (nums[mid] <= target) {
			left = mid + 1;
		}
		else {
			right = mid;
		}
	}
	return right;
}


//std::find; std::find_if; std::find_if_not


int main()
{
   
}