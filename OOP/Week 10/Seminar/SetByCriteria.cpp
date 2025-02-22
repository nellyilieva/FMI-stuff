#include "SetByCriteria.h"

unsigned DynamicSet::getBucketIdx(unsigned num) const {
	return num / elementsInBucket;
}

void DynamicSet::copyFrom(const DynamicSet& other) {
	buckets = new uint8_t[other.bucketsCount];

	for (int i = 0; i < other.bucketsCount; i++) {
		buckets[i] = other.buckets[i];
	}

	bucketsCount = other.bucketsCount;
	maxNum = other.maxNum;
}

void DynamicSet::moveFrom(DynamicSet&& other) {
	buckets = other.buckets;
	bucketsCount = other.bucketsCount;
	maxNum = other.maxNum;

	other.buckets = nullptr;
	other.bucketsCount = other.maxNum = 0;
}

void DynamicSet::free() {
	delete[] buckets;
	buckets = nullptr;
	bucketsCount = maxNum = 0;
}

DynamicSet::DynamicSet(unsigned maxNum) {
	this->maxNum = maxNum;
	bucketsCount = maxNum / elementsInBucket + 1;
	buckets = new uint8_t[bucketsCount]{};
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

DynamicSet::DynamicSet(DynamicSet&& other) noexcept {
	moveFrom(std::move(other));
}

DynamicSet& DynamicSet::operator=(DynamicSet&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

DynamicSet::~DynamicSet() {
	free();
}

unsigned DynamicSet::getMaxNum() const {
	return maxNum;
}

void DynamicSet::add(unsigned num) {
	if (num > maxNum) {
		return;
	}

	unsigned bucketIdx = getBucketIdx(num);
	unsigned bitIdx = maxNum % elementsInBucket;

	uint8_t mask = 1;
	mask <<= bitIdx;

	buckets[bucketIdx] |= mask;
}

void DynamicSet::remove(unsigned num) {
	if (num > maxNum) {
		return;
	}

	unsigned bucketIdx = getBucketIdx(num);
	unsigned bitIdx = maxNum % elementsInBucket;

	uint8_t mask = 1;
	mask <<= bitIdx;

	buckets[bucketIdx] &= (~mask);
}

bool DynamicSet::isInSet(unsigned num) const {
	unsigned bucketIdx = getBucketIdx(num);
	unsigned bitIdx = maxNum % elementsInBucket;

	uint8_t mask = 1;
	mask <<= bitIdx;

	return (buckets[bucketIdx] & mask);
}

void DynamicSet::printNumbers() const {
	std::cout << '{';
	for (int i = 0; i <= maxNum; i++)
	{
		if (isInSet(i))
			std::cout << i << " ";
	}

	std::cout << '}' << std::endl;
}

void DynamicSet::clear() {
	for (int i = 0; i < bucketsCount; i++) {
		buckets[i] = 0;
	}
}

DynamicSet unionOfSets(const DynamicSet& lhs, const DynamicSet& rhs) {
	DynamicSet result(std::max(lhs.maxNum, rhs.maxNum));

	unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

	for (int i = 0; i < minBucketsCount; i++) {
		result.buckets[i] = lhs.buckets[i] | rhs.buckets[i];
	}

	const DynamicSet& biggerN = lhs.bucketsCount > rhs.bucketsCount ? lhs : rhs; //no copy here

	for (int i = minBucketsCount; i < biggerN.bucketsCount; i++) {
		result.buckets[i] = biggerN.buckets[i];
	}

	return result;
}

DynamicSet intersectionOfSets(const DynamicSet& lhs, const DynamicSet& rhs) {
	DynamicSet result(std::min(lhs.maxNum, rhs.maxNum));

	unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

	for (int i = 0; i < minBucketsCount; i++) {
		result.buckets[i] = lhs.buckets[i] & rhs.buckets[i];
	}

	return result;
}

void SetByCriteria::fillSet() {
	for (int i = 0; i < getMaxNum(); i++) {
		if (criteria.includes(i) && !criteria.excludes(i)) {
			add(i);
		}
		else {
			remove(i);
		}
	}
}

//constructor
SetByCriteria::SetByCriteria(unsigned maxNumber, bool(*includes)(unsigned n), bool(*excludes)(unsigned n))
	: DynamicSet(maxNumber), criteria({includes, excludes}) {

	fillSet();
}

//set includes
void SetByCriteria::setIncludes(bool(*includes)(unsigned n)) {
	criteria.includes = includes;
	fillSet();
}

//set excludes
void SetByCriteria::setExcludes(bool(*excludes)(unsigned n)) {
	criteria.excludes = excludes;
	fillSet();
}

bool SetByCriteria::contains(unsigned num) const {
	return DynamicSet::isInSet(num);
}

void SetByCriteria::print() const {
	DynamicSet::printNumbers();
}

//!!!
void SetByString::fillSet() {
	clear();

	std::stringstream ss(str);

	while (!ss.eof()) {
		unsigned curr;
		ss >> curr;
		add(curr);
	}
}

void SetByString::copyFrom(const SetByString& other) {
	str = new char[other.length + 1];
	strcpy(str, other.str);

	length = other.length;
}

void SetByString::moveFrom(SetByString&& other) {
	str = other.str;
	length = other.length;

	other.str = nullptr;
	other.length = 0;
}

void SetByString::free() {
	delete[] str;

	str = nullptr;
	length = 0;
}

SetByString::SetByString(const SetByString& other) : DynamicSet(other) {
	copyFrom(other);
}

SetByString::SetByString(SetByString&& other) : DynamicSet(std::move(other)) {
	moveFrom(std::move(other));
}

SetByString& SetByString::operator=(SetByString&& other) {
	if (this != &other) {
		DynamicSet::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

SetByString& SetByString::operator=(const SetByString& other) {
	if (this != &other) {
		DynamicSet::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

SetByString::~SetByString() {
	free();
}

SetByString::SetByString(unsigned maxNum, const char* str) : DynamicSet(maxNum) {
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
	length = strlen(str);

	fillSet();
}

bool SetByString::contains(unsigned num) const {
	return DynamicSet::isInSet(num);
}

void SetByString::print() const {
	DynamicSet::printNumbers();
}

void SetByString::setAt(unsigned idx, char ch) {
	str[idx] = ch;
	fillSet();
}


int main() {

}