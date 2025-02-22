#pragma once
#include <iostream>

constexpr unsigned MAX_NUM = 1023;
constexpr unsigned NUM_COUNT = MAX_NUM + 1;
constexpr unsigned BUCKET_SIZE = sizeof(uint8_t) * 8;
constexpr unsigned BUCKETS_COUNT = NUM_COUNT / BUCKET_SIZE + 1;


class StaticSet {
	uint8_t buckets[BUCKETS_COUNT] = { 0 };

	unsigned getBucketIdx(unsigned n) const;
	unsigned getBitIdx(unsigned n) const;
public:
	void add(unsigned n);
	void remove(unsigned n);

	bool contains(unsigned n) const;

	void print() const;
	void printBucketInMemory(int bucketIdx) const; //maybe privte
	void printInMemory() const;

	friend StaticSet unionOfSets(const StaticSet& lhs, const StaticSet& rhs);
	friend StaticSet intersectionOfSets(const StaticSet& lhs, const StaticSet& rhs);
};