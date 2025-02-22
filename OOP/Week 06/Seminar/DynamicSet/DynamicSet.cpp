#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)
#include "DynamicSet.h"

unsigned DynamicSet::getBucketIdx(unsigned n) const {
	return n / MAX_ELEMENTSIN_BUCKET;
}

void DynamicSet::copyFrom(const DynamicSet& other) {
	buckets = new uint8_t[other.bucketsCount];
	for (int i = 0; i < other.bucketsCount; i++) {
		buckets[i] = other.buckets[i];
	}

	bucketsCount = other.bucketsCount;
	N = other.N;
}

void DynamicSet::free() {
	delete[] buckets;
	buckets = nullptr;
	bucketsCount = 0;
}

DynamicSet::DynamicSet(unsigned N) {
	bucketsCount = N / MAX_ELEMENTSIN_BUCKET + 1;
	buckets = new uint8_t[bucketsCount]{ 0 };
	this->N = N;
}

DynamicSet::DynamicSet(const DynamicSet& other) {
	copyFrom(other);
}

DynamicSet& DynamicSet::operator=(const DynamicSet& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

DynamicSet::~DynamicSet() {
	free();
}

void DynamicSet::add(unsigned n) {
	if (n > N) {
		return;
	}

	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = n % MAX_ELEMENTSIN_BUCKET;

	uint8_t mask = 1;
	mask <<= bitIdx;

	buckets[bucketIdx] |= mask;
}

void DynamicSet::remove(unsigned n) {
	if (n > N) {
		return;
	}

	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = n % MAX_ELEMENTSIN_BUCKET;

	uint8_t mask = 1;
	mask <<= bitIdx;

	buckets[bucketIdx] &= (~mask);
}

bool DynamicSet::isInSet(unsigned n) const {
	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = n % MAX_ELEMENTSIN_BUCKET;

	uint8_t mask = 1;
	mask <<= bitIdx;

	return buckets[bucketIdx] & mask;
}

void DynamicSet::printNumbers() const {
	std::cout << "{ ";
	for (int i = 0; i <= N; i++) {
		if (isInSet(i)) {
			std::cout << i << " ";
		}
	}

	std::cout << "}" << std::endl;
}

DynamicSet UnionOfSets(const DynamicSet& lhs, const DynamicSet& rhs) {
	DynamicSet result(std::max(lhs.N, rhs.N));

	unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

	for (int i = 0; i < minBucketsCount; i++) {
		result.buckets[i] = lhs.buckets[i] | rhs.buckets[i];
	}

	const DynamicSet& biggerN = lhs.bucketsCount > rhs.bucketsCount ? lhs : rhs;

	for (int i = minBucketsCount; i < biggerN.bucketsCount; i++) {
		result.buckets[i] = biggerN.buckets[i];
	}

	return result;
}

DynamicSet IntersectionOfSets(const DynamicSet& lhs, const DynamicSet& rhs) {
	DynamicSet result(std::min(lhs.N, rhs.N));

	unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

	for (int i = 0; i < minBucketsCount; i++) {
		result.buckets[i] = lhs.buckets[i] & rhs.buckets[i];
	}

	return result;
}

int main() {
	DynamicSet s1(1024);

	s1.add(1);
	s1.add(10);
	s1.add(5);
	s1.printNumbers();

	DynamicSet s2(1024);

	s2.add(1);

	s2.add(17);
	s1.add(130);
	s1.printNumbers();


	DynamicSet intersect = UnionOfSets(s1, s2);
	DynamicSet uni = IntersectionOfSets(s1, s2);

	intersect.printNumbers();
	uni.printNumbers();

}