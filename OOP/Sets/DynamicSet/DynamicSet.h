#pragma once
#include <iostream>

//without move

constexpr unsigned BUCKET_SIZE = sizeof(uint8_t) * 8;

class DynamicSet {
private:
	uint8_t* buckets = nullptr;

	unsigned bucketsCount = 0;
	unsigned maxNum = 0;

	unsigned getBucketIdx(unsigned n) const;

	void copyFrom(const DynamicSet& other);
	void free();

public:
	DynamicSet();
	DynamicSet(unsigned n);

	DynamicSet(const DynamicSet& other);
	DynamicSet& operator=(const DynamicSet& other);

	~DynamicSet();

	void add(unsigned n);
	void remove(unsigned n);

	bool contains(unsigned n) const;
	void print() const;

	friend DynamicSet UnionOfSets(const DynamicSet& lhs, const DynamicSet& rhs);
	friend DynamicSet IntersectionOfSets(const DynamicSet& lhs, const DynamicSet& rhs);
};