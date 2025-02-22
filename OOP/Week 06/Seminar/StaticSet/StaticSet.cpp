#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)
#include "StaticSet.h"

unsigned StaticSet::getBucketIdx(unsigned n) const {
	return n / BUCKET_SIZE;
}

unsigned StaticSet::getBitIdx(unsigned n) const {
	return n % BUCKET_SIZE;
}

void StaticSet::add(unsigned n) {
	if (n > MAX_NUM) {
		return;
	}

	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = getBitIdx(n);

	uint8_t mask = 1;
	mask <<= bitIdx;

	bucket[bucketIdx] |= mask;
}

void StaticSet::remove(unsigned n) {
	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = getBitIdx(n);

	uint8_t mask = 1;
	mask <<= bitIdx;

	bucket[bucketIdx] &= (~mask);
}

bool StaticSet::isInSet(unsigned n) const {
	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = getBitIdx(n);

	uint8_t mask = 1;
	mask <<= bitIdx;

	return (bucket[bucketIdx] & mask) != 0;
}

void StaticSet::printNumbers() const {
	std::cout << "{ ";

	for (unsigned i = 0; i < MAX_NUM; i++) {
		if (isInSet(i)) {
			std::cout << i << " ";
		}
	}

	std::cout << "}";
}

void StaticSet::memoryView() const {
	for (unsigned i = 0; i < MAX_NUM; i++) {
		if (getBitIdx(i) % 8 == 0) {
			std::cout << std::endl;
		}
		std::cout << isInSet(i) << " ";
	}
}

StaticSet StaticSet::unionOfSets(const StaticSet& other) {
	StaticSet result;

	for (int i = 0; i < BUCKETS_COUNT; i++) {
		result.bucket[i] = (bucket[i] | other.bucket[i]);
	}

	return result;
}

StaticSet StaticSet::intersectionOfSets(const StaticSet& other) {
	StaticSet result;

	for (int i = 0; i < BUCKETS_COUNT; i++) {
		result.bucket[i] = (bucket[i] & other.bucket[i]);
	}

	return result;
}

int main() {
	StaticSet s1;

	s1.add(1);
	s1.add(10);
	s1.add(5);
	s1.printNumbers();

	StaticSet s2;

	s2.add(1);

	s2.add(17);
	s1.add(130);
	s1.printNumbers();

	StaticSet s3 = s1.unionOfSets(s2);
	s3.printNumbers();

	//s1.memoryView();
}
