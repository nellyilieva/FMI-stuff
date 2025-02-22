#include "StaticSet.h"
#pragma once
#pragma warning(disable : 4996)


unsigned StaticSet::getBucketIdx(unsigned n) const {
	return n / BUCKET_SIZE;
}

unsigned StaticSet::getBitIdx(unsigned n) const {
	return n % BUCKET_SIZE;
}

void StaticSet::add(unsigned n) {
	if (n > MAX_NUM) {
		throw std::out_of_range("Too big number");
	}

	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = getBitIdx(n);

	uint8_t mask = 1 << bitIdx;
	buckets[bucketIdx] |= mask;
}

void StaticSet::remove(unsigned n) {
	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = getBitIdx(n);

	uint8_t mask = 1 << bitIdx;
	mask = ~mask;

	buckets[bucketIdx] &= mask;
}

bool StaticSet::contains(unsigned n) const {
	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = getBitIdx(n);

	uint8_t mask = 1 << bitIdx;

	return (mask & buckets[bucketIdx]) != 0;
}

void StaticSet::print() const {
	for (int i = 0; i < MAX_NUM; i++) {
		if (contains(i)) {
			std::cout << i << " ";
		}
	}
}

void StaticSet::printBucketInMemory(int bucketIdx) const {
	for (int i = BUCKET_SIZE - 1; i >= 0; i--) {
		std::cout << contains(i);
	}
}

void StaticSet::printInMemory() const {
	for (int i = 0; i < BUCKETS_COUNT; i++) {
		printBucketInMemory(i);
		std::cout << " ";
	}
}

StaticSet unionOfSets(const StaticSet& lhs, const StaticSet& rhs) {
	StaticSet s;

	for (int i = 0; i < BUCKETS_COUNT; i++) {
		s.buckets[i] = lhs.buckets[i] | rhs.buckets[i];
	}

	return s;
	
}

StaticSet intersectionOfSets(const StaticSet& lhs, const StaticSet& rhs) {
	StaticSet s;

	for (int i = 0; i < BUCKETS_COUNT; i++) {
		s.buckets[i] = lhs.buckets[i] & rhs.buckets[i];
	}

	return s;
}


int main() {

}
