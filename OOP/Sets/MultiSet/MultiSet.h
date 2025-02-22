#pragma once
#include <iostream>

class MultiSet {
private:
	uint8_t* buckets;

	unsigned maxNum = 0;
	unsigned bucketsCount = 0;

	const unsigned elementsInBucket = 4; //7 - maxOccurances
	const unsigned maxOccurances = 3;

	void copyFrom(const MultiSet& other);
	void free();

	void printNumber(unsigned num, unsigned occurrences) const;
	void addNumberMultipleTimes(unsigned num, unsigned times);

public:
	explicit MultiSet(unsigned maxNum);
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	unsigned getCountOfOccurances(unsigned num) const;
	bool addNumber(unsigned num);
	bool removeNumber(unsigned num);
	void printSet() const;


	friend MultiSet intersect(const MultiSet& lhs, const MultiSet& rhs);
	friend MultiSet unify(const MultiSet& lhs, const MultiSet& rhs);
};