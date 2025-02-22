#include "StringPool.h"
#include <iostream>

void StringPool::StringNode::allocateData(const char* str) {
	data = new char[strlen(str) + 1];
	strcpy(data, str);
}

void StringPool::resize() {
	StringNode* newNodes = new StringNode[capacity * 2]{};

	for (size_t i = 0; i < size; i++) {
		newNodes[i] = nodes[i];
	}

	delete[] nodes;
	nodes = newNodes;
}

StringPool::StringPool() {
	nodes = new StringNode[capacity];
}

StringPool::~StringPool() {
	for (size_t i = 0; i < size; i++) {
		delete[] nodes[i].data;
	}

	delete[] nodes;
}

bool StringPool::lowerBound(const char* str, size_t& idx) {
	int left = 0;
	int right = size - 1;
	int leftMostIdx = -1;

	while (left <= right) {
		int mid = (right - left) / 2 + left;
		int cmp = strcmp(nodes[mid].data, str);

		if (cmp == 0) {
			idx = mid;
			return true;
		}
		else if (cmp > 0) {
			right = mid - 1;
		}
		else {
			left = mid + 1;
			leftMostIdx = mid;
		}
	}

	idx = leftMostIdx;
	return false;
}

const char* StringPool::insert(const char* str, size_t idx) {
	if (idx > size) {
		throw std::out_of_range("Out of range");
	}

	if (size == capacity) {
		resize();
	}

	for (size_t i = size - 1; i > idx; i--) {
		nodes[i + 1] = nodes[i];
	}

	nodes[idx].allocateData(str);
	nodes[idx].referenceCount = 1;

	size++;

	return nodes[idx].data;
}

void StringPool::removeStringFromPool(size_t idx) {
	if (idx > size) {
		throw std::out_of_range("Out of range");
	}

	delete[] nodes[idx].data;

	for (size_t i = idx; i < size - 1; i++) {
		nodes[i] = nodes[i + 1];
	}

	nodes[size - 1].data = nullptr;
	nodes[size - 1].referenceCount = 0;
	size--;
}

const char* StringPool::getString(const char* str) {
	size_t idx = -1;
	bool found = lowerBound(str, idx);

	if (found) {
		nodes[idx].referenceCount++;
		return nodes[idx].data;
	}

	return insert(str, idx + 1);
}

void StringPool::removeString(const char* str) {
	size_t idx = -1;
	bool found = lowerBound(str, idx);
	if (!found) {
		throw std::runtime_error("String not found");
	}

	nodes[idx].referenceCount--;
	if (nodes[idx].referenceCount == 0) {
		removeStringFromPool(idx);
	}
}

void StringPool::print() const {
	for (size_t i = 0; i < size; i++) {
		std::cout << nodes[i].data << " " << nodes[i].referenceCount << '/n';
	}
}