#include "MultiSet.h"
#pragma once
#pragma warning(disable : 4996)

void MultiSet::copyFrom(const MultiSet& other) {
	maxNum = other.maxNum;
	bucketsCount = other.bucketsCount;

	for (int i = 0; i < bucketsCount; i++) {
		buckets[i] = other.buckets[i];
	}
}

void MultiSet::free() {
	delete[] buckets;
}

MultiSet::MultiSet(unsigned maxNum) {
	this->maxNum = maxNum;

	bucketsCount = maxNum / elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount];
}

MultiSet::MultiSet(const MultiSet& other) {
	copyFrom(other);
}

MultiSet& MultiSet::operator=(const MultiSet& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MultiSet::~MultiSet() {
	free();
}

unsigned MultiSet::getCountOfOccurances(unsigned num) const {
	unsigned bucket = maxNum / elementsInBucket;
	unsigned idx = maxNum % elementsInBucket;

	uint8_t& currBucket = buckets[bucket];
	uint8_t mask = 1;
	mask <<= idx * 2;

	bool isFirstUp = ((currBucket & mask) == mask);
	mask << 1;
	bool isSecondUp = ((currBucket & mask) == mask);

	return (isFirstUp * (1 << 0) + isSecondUp * (1 << 1));
}

bool MultiSet::addNumber(unsigned num) {
	unsigned bucket = maxNum / elementsInBucket;
	unsigned idx = maxNum % elementsInBucket;

	uint8_t& currBucket = buckets[bucket];
	unsigned occurances = getCountOfOccurances(num);

	uint8_t mask = 1;
	mask << idx * 2;

	switch (occurances) {
	case 1: {
		mask = ~mask;
		currBucket &= mask;
		mask = ~mask;
		mask <<= 1;
		currBucket |= mask;
		return true;
	}
	case 0:
	case 2: {
		currBucket |= mask;
		return true;
	}
	default: return false;
	}
}

void MultiSet::addNumberMultipleTimes(unsigned num, unsigned times) {
	if (times > maxOccurances)
		times = maxOccurances;

	for (unsigned i = 0; i < times; i++)
		addNumber(num);
}

bool MultiSet::removeNumber(unsigned num) {
	unsigned bucket = maxNum / elementsInBucket;
	unsigned idx = maxNum % elementsInBucket;

	uint8_t& currBucket = buckets[bucket];
	unsigned occurances = getCountOfOccurances(num);

	uint8_t mask = 1;
	mask << idx * 2;

	switch (occurances)
	{
	case 3:
	case 1:
	{
		mask = ~mask;
		currBucket &= mask;
		return true;
	}
	case 2: {
		currBucket |= mask;
		mask <<= 1;
		mask = ~mask;
		currBucket &= mask;
		return true;
	}
	default: return false;
	}
}

void MultiSet::printNumber(unsigned num, unsigned occurrences) const {
	for (int i = 0; i < occurrences; i++) {
		std::cout << num << " ";
	}
}

void MultiSet::printSet() const {
	for (int i = 0; i < maxNum; i++) {
		unsigned occurances = getCountOfOccurances(i);
		printNumber(i, occurances);
	}
}

MultiSet intersect(const MultiSet& lhs, const MultiSet& rhs) {
	//lhs.maxNum == rhs.maxNum  !!!!

	int n = lhs.maxNum;

	MultiSet s(n);

	for (unsigned i = 0; i < n; i++) {
		unsigned occurrencesInFirst = lhs.getCountOfOccurances(i);
		unsigned occurrencesInSecond = rhs.getCountOfOccurances(i);
		unsigned occurrences = occurrencesInFirst < occurrencesInSecond ? occurrencesInFirst : occurrencesInSecond;
		s.addNumberMultipleTimes(i, occurrences);
	}

	return s;
}

MultiSet unify(const MultiSet& lhs, const MultiSet& rhs) {
	//assert(lhs.maxNum == rhs.maxNum);

	int n = lhs.maxNum;
	MultiSet s(n);

	for (unsigned i = 0; i < lhs.bucketsCount; i++) {
		unsigned occurrencesInFirst = lhs.getCountOfOccurances(i);
		unsigned occurrencesInSecond = rhs.getCountOfOccurances(i);
		unsigned occurrences = occurrencesInFirst + occurrencesInSecond;
		s.addNumberMultipleTimes(i, occurrences);
	}

	return s;
}

int main() {

}
