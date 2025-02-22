#include "DynamicSet.h"
#pragma once
#pragma warning(disable : 4996)


unsigned DynamicSet::getBucketIdx(unsigned n) const {
	return n / BUCKET_SIZE;
}

void DynamicSet::copyFrom(const DynamicSet& other) {
	bucketsCount = other.bucketsCount;
	maxNum = other.maxNum;

	buckets = new uint8_t[bucketsCount];
	for (int i = 0; i < bucketsCount; i++) {
		buckets[i] = other.buckets[i];
	}
}

void DynamicSet::free() {
	delete[] buckets;
	buckets = nullptr;

	bucketsCount = 0;
	maxNum = 0;
}

DynamicSet::DynamicSet() : DynamicSet(15) {}

DynamicSet::DynamicSet(unsigned n) {
	bucketsCount = n / BUCKET_SIZE + 1;
	buckets = new uint8_t[bucketsCount];

	maxNum = n;
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
	if (n > maxNum) {
		throw std::out_of_range("Too big number");
	}

	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = n % BUCKET_SIZE;

	uint8_t mask = 1 << bitIdx;

	buckets[bucketIdx] |= mask;
}

void DynamicSet::remove(unsigned n) {
	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = n % BUCKET_SIZE;

	uint8_t mask = 1 << bitIdx;
	mask = ~mask;

	buckets[bucketIdx] &= mask;
}

bool DynamicSet::contains(unsigned n) const {
	unsigned bucketIdx = getBucketIdx(n);
	unsigned bitIdx = n % BUCKET_SIZE;

	uint8_t mask = 1 << bitIdx;
	return (mask & buckets[bucketIdx]);
}

void DynamicSet::print() const {
	for (int i = 0; i < maxNum; i++) {
		if (contains(i)) {
			std::cout << i << " ";
		}
	}
}

DynamicSet UnionOfSets(const DynamicSet& lhs, const DynamicSet& rhs) {
	DynamicSet s(std::max(lhs.maxNum, rhs.maxNum));

	unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	for (int i = 0; i < minBucketsCount; i++) {
		s.buckets[i] = lhs.buckets[i] | rhs.buckets[i];
	}

	const DynamicSet& biggerN = lhs.bucketsCount > rhs.bucketsCount ? lhs : rhs; //no copy here

	for (int i = minBucketsCount; i < biggerN.bucketsCount; i++) {
		s.buckets[i] = biggerN.buckets[i];
	}

	return s;
}

DynamicSet IntersectionOfSets(const DynamicSet& lhs, const DynamicSet& rhs) {
	DynamicSet s(std::min(lhs.maxNum, rhs.maxNum));

	unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);
	for (int i = 0; i < minBucketsCount; i++) {
		s.buckets[i] = lhs.buckets[i] & rhs.buckets[i];
	}

	return s;
}


int main() {

}
