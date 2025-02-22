#include <iostream>

void countingSort(int* arr, unsigned len) {
	constexpr int MAX_SIZE = 1e5;
	int copy[MAX_SIZE];

	int max = arr[0];
	for (int i = 0; i < len; i++) {     //init copy array and find max element(value) in array
		copy[i] = arr[i];

		if (max < arr[i]) {
			max = arr[i];
		}
	}

	int count[MAX_SIZE];

	for (int i = 0; i < max + 1; i++) {    //init count array
		count[i] = 0;
	}

	for (int i = 0; i < len; i++) {        //give count array the values
		count[arr[i]]++;
	}

	for (int i = 1; i <= max; i++) {       //уплътняване
		count[i] += count[i - 1];
	}

	for (int i = len - 1; i >= 0; i--) {   //idx array
		arr[count[copy[i]] - 1] = copy[i];
		count[copy[i]]--;

		/*el_from_arr = copy[i];
		idx_to_put_el = count[el] - 1;
		arr[idx] = copy[i];   put element
		idx--;                decrease idx to be ready for next same element*/
	}
}


int main()
{

}
