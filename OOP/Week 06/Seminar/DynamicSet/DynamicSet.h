#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#pragma warning (disable: 4996)

constexpr unsigned MAX_ELEMENTSIN_BUCKET = sizeof(uint8_t) * 8;

class DynamicSet {
private:
	uint8_t* buckets = nullptr;
	unsigned bucketsCount = 0;
	unsigned N = 0;

	unsigned getBucketIdx(unsigned n) const;

	void copyFrom(const DynamicSet& other);
	void free();

public:
	DynamicSet() = default;
	DynamicSet(unsigned N);

	DynamicSet(const DynamicSet& other);
	DynamicSet& operator=(const DynamicSet& other);

	~DynamicSet();

	void add(unsigned n);
	void remove(unsigned n);

	bool isInSet(unsigned n) const;

	void printNumbers() const;

	friend DynamicSet UnionOfSets(const DynamicSet& lhs, const DynamicSet& rhs);
	friend DynamicSet IntersectionOfSets(const DynamicSet& lhs, const DynamicSet& rhs);
};