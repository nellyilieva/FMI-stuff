#include "Collections.h"

void DynamicCollection::resize(size_t newCap) {
	int* temp = new int[newCap];

	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;

	capacity = newCap;
}

void DynamicCollection::copyFrom(const DynamicCollection& other) {
	size = other.size;
	capacity = other.capacity;

	data = new int[other.capacity];

	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

void DynamicCollection::moveFrom(DynamicCollection&& other) {
	data = other.data;
	capacity = other.capacity;
	size = other.size;

	other.data = nullptr;
	other.capacity = other.size = 0;
}

void DynamicCollection::free() {
	delete[] data;
}

DynamicCollection::DynamicCollection(size_t capacity) {
	this->capacity = capacity;
	size = 0;

	data = new int[capacity];
}

DynamicCollection::DynamicCollection() : size(0), capacity(8) {
	data = new int[capacity];
}

DynamicCollection::DynamicCollection(const DynamicCollection& other) {
	copyFrom(other);
}

DynamicCollection& DynamicCollection::operator=(const DynamicCollection& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

DynamicCollection::DynamicCollection(DynamicCollection&& other) {
	moveFrom(std::move(other));
}

DynamicCollection& DynamicCollection::operator=(DynamicCollection&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

DynamicCollection::~DynamicCollection() {
	free();
}


void NormalCollection::add(int n) {
	if (size >= capacity) {
		resize(capacity * 2);
	}

	data[size++] = n;
}

//find element idx, swap with last, size--;
void NormalCollection::remove(int n) {
	int idx = -1;

	for (int i = 0; i < size; i++) {
		if (data[i] == n) {
			idx = i;
			break;
		}
	}

	if (idx != -1) {
		std::swap(data[idx], data[size - 1]);
		size--;
	}
}

unsigned NormalCollection::count(int n) const {
	unsigned count = 0;

	for (int i = 0; i < size; i++) {
		if (data[i] == n) {
			count++;
		}
	}

	return count;
}

bool NormalCollection::contains(int n) const {
	for (int i = 0; i < size; i++) {
		if (data[i] == n) {
			return true;
		}
	}

	return false;
}


int SortedCollectioin::lowerBound(int n) const {
	int left = 0;
	int right = size - 1;

	int result = size;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (data[mid] == n) {
			result = mid;
			right = mid - 1;
		}
		else if (data[mid] < n) {
			left = mid + 1;
		}
		else {
			right = mid + 1;
		}
	}

	return result;
}

int SortedCollectioin::upperBound(int n) const {
	int left = 0;
	int right = size - 1;

	int result = -1;

	while (left <= right) {
		int mid = left + (right - left) / 2;

		if (data[mid] == n) {
			result == mid;
			left = mid + 1;
		}
		else if (data[mid] > n) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
		}
	}

	return result;
}

void SortedCollectioin::add(int n) {
	if (size >= capacity) {
		resize(capacity * 2);
	}

	int idx = size;

	while (idx != 0 && data[idx - 1] > n) {
		data[idx] = data[idx - 1];
		idx--;
	}

	data[idx] = n;
	size++;
}

void SortedCollectioin::remove(int n) {
	int idx = lowerBound(n);

	if (idx == -1) {
		return;
	}

	for (int i = 0; i < size - 1; i++) {
		data[i] = data[i + 1];
	}

	size--;
}

unsigned SortedCollectioin::count(int n) const {
	int left = lowerBound(n);

	if (left == -1) {
		return 0;
	}

	int right = upperBound(n);

	return right - left + 1;
}

bool SortedCollectioin::contains(int n) const {
	return lowerBound(n) != -1;
}


IntervalCollection::IntervalCollection(int start, int end) {
	if (end < start) {
		std::swap(start, end);
	}

	this->start = start;
	this->end = end;

	int size = end - start;

	data = new int[size];
}

unsigned IntervalCollection::intervalLength() const {
	return end - start;
}

void IntervalCollection::add(int n) {
	if (n < start || n > end) {
		return;
	}

	++data[n - start];
}

void IntervalCollection::remove(int n) {
	if (n < start || n > end) {
		return;
	}

	int idx = n - start;

	if (data[idx] == 0) {
		return;
	}

	--data[idx];
}

unsigned IntervalCollection::count(int n) const {
	if (n < start || n > end) {
		return;
	}

	return data[n - start];
}

bool IntervalCollection::contains(int n) const {
	return count(n) > 0;
}

Set::Set(CollectionType type) {
	if (type == NORMAL_COLLECTION) {
		collection = new NormalCollection();
	}
	else if (type == SORTED_COLLECTION) {
		collection = new SortedCollectioin();
	}
}

void Set::add(int n) {
	if (!collection->contains(n)) {
		collection->add(n);
	}
}

void Set::remove(int n) {
	collection->remove(n);
}

unsigned Set::count(int n) const {
	return collection->count(n);
}

bool Set::contains(int n) const {
	return collection->contains(n);
}

Set::~Set() {
	delete collection;
}