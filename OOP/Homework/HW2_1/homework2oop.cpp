#include <iostream>
#include "homework2oop.h"
#include <fstream>


MultiSet::MultiSet() {
    buckets = nullptr;
    n = 0;
    k = 0;
    countOfBuckets = 0;
}

MultiSet::MultiSet(unsigned n, unsigned k) {
    this->n = n;
    this->k = k;

    int product = n * k;
    int reminder = product % 8;
    int result;

    if (reminder == 0) {
        result = product;
    }

    else {
        result = product + 8 - reminder;
    }

    countOfBuckets = result / 8;
    buckets = new uint8_t[countOfBuckets]{ 0 };
    
}

MultiSet::MultiSet(unsigned n, unsigned k, uint8_t* buckets) {
    MultiSet(n, k);
    delete[] this->buckets;

    this->buckets = buckets;
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

void MultiSet::copyFrom(const MultiSet& other) {
    buckets = new uint8_t[other.countOfBuckets];

    for (int i = 0; i < other.countOfBuckets; i++) {
        buckets[i] = other.buckets[i];
    }

    n = other.n;
    k = other.k;

    countOfBuckets = other.countOfBuckets;
}

void MultiSet::free() {
    delete[] buckets;
    buckets = nullptr;

    n = 0;
    k = 0;

    countOfBuckets = 0;
}

int MultiSet::getBucketsCount() const {
    return countOfBuckets;
}

unsigned MultiSet::getBucket(unsigned idx) const {
    return idx / 8;
}

unsigned MultiSet::getBit(unsigned idx) const {
    return idx % 8;
}

bool MultiSet::isBitZero(unsigned bucket, unsigned bit) const {
    return ((1 << bit) & bucket) == 0;
}

unsigned MultiSet::getOccurrences(unsigned num) const {
    unsigned occurrences = 0;
    int startBit = num * k;

    for (int i = 0; i < k; i++) {
        unsigned currentBit = startBit + i;
        unsigned bucket = getBucket(currentBit);
        unsigned bit = getBit(currentBit);

        if (!isBitZero(buckets[bucket], bit)) {
            occurrences += (1 << i);
        }
    }

    return occurrences;
}

void MultiSet::add(unsigned num) {
    if (num > n) {
        std::cout << "The number is too big" << '/n';
        return;
    }

    int startBit = num * k;

    for (int i = 0; i < k; i++) {
        int currentBit = startBit + i;
        unsigned bucket = getBucket(currentBit);
        unsigned bit = getBit(currentBit);

        if (isBitZero(buckets[bucket], bit)) {
            makeBitOne(buckets[bucket], bit);

            for (int j = i - 1; j >= 0; j--) {
                int previousBit = startBit + j;
                unsigned prevBucket = getBucket(previousBit);
                unsigned prevBit = getBit(previousBit);

                if (!isBitZero(buckets[prevBucket], prevBit)) {
                    makeBitZero(buckets[prevBucket], prevBit);
                }
            }

            return;
        }
    }

    std::cout << "Unable to add the number " << num << std::endl;
}

void MultiSet::addNumber(unsigned num, unsigned n) {
    for (int i = 0; i < n; i++) {
        add(num);
    }
}

void MultiSet::print() const {
    std::cout << '{';

    for (int i = 0; i <= n; i++) {
        unsigned numOccurences = getOccurrences(i);
        if (numOccurences > 0) {
            std::cout << "|" << i << "|" << numOccurences << "|" << '/n';
        }
    }

    std::cout << '}' << std::endl;
}

void MultiSet::printBucketMemoryView(unsigned idx) const {
    for (int i = 7; i >= 0; i--) {
        std::cout << checkBit(buckets[idx], i);
    }
}

void MultiSet::printMemoryView() const {
    for (int i = 0; i < countOfBuckets - 1; i++) {
        printBucketMemoryView(i);
        std::cout << ' ';
    }

    printBucketMemoryView(countOfBuckets - 1);
    std::cout << '/n';
}

bool checkBit(unsigned n, unsigned idx) {
    unsigned int mask = 1;
    mask <<= idx;
    return (mask & n) == mask;
}

void MultiSet::makeBitOne(unsigned bucketIdx, unsigned bitIdx) {
    unsigned mask = 1;
    mask <<= bitIdx;
    buckets[bucketIdx] |= mask;
}

void MultiSet::makeBitZero(unsigned bucketIdx, unsigned bitIdx) {
    unsigned mask = 1;
    mask <<= bitIdx;
    buckets[bucketIdx] ^= mask;
}

size_t getFileSize(std::ifstream& ifs) {
    size_t currPos = ifs.tellg();
    ifs.seekg(std::ios::end);

    size_t fileSize = ifs.tellg();
    ifs.seekg(currPos);

    return fileSize;
}

void MultiSet::serialize(const char* filename) const {
    std::ofstream ofs(filename, std::ios::binary);

    if (!ofs.is_open()) {
        return;
    }

    ofs.write((const char*)&n, sizeof(n));
    ofs.write((const char*)&k, sizeof(k));
    ofs.write((const char*)buckets, sizeof(uint8_t) * countOfBuckets);
    ofs.close();
}

MultiSet deserialize(const char* filename) {
    std::ifstream ifs(filename, std::ios::binary);

    if (!ifs.is_open()) {
        return MultiSet();
    }

    unsigned n = 0;
    unsigned k = 0;

    uint8_t* buckets = new uint8_t[getFileSize(ifs) - 2 * sizeof(n)];
    ifs.read((char*)&n, sizeof(n));
    ifs.read((char*)&k, sizeof(k));
    ifs.read((char*)buckets, getFileSize(ifs) - 2 * sizeof(n));

    MultiSet result(n, k, buckets);
    delete[] buckets;
    return result;
}

MultiSet difference(const MultiSet& lhs, const MultiSet& rhs) {
    MultiSet result(lhs.n, lhs.k);

    for (int i = 0; i < lhs.n; i++) {
        int lhsOccurrences = lhs.getOccurrences(i);
        int rhsOccurrences = rhs.getOccurrences(i);

        int newOccurrences = lhsOccurrences - rhsOccurrences;
        if (newOccurrences < 0) {
            newOccurrences = 0;
        }

        if (newOccurrences > 0) {
            result.addNumber(i, newOccurrences);
        }
    }

    return result;
}

MultiSet intersection(const MultiSet& lhs, const MultiSet& rhs) {
    unsigned newN = std::min(lhs.n, rhs.n);
    unsigned newK = std::min(lhs.k, rhs.k);

    MultiSet result(newN, newK);

    for (int i = 0; i <= newN; i++) {
        int minOccurrences = std::min(lhs.getOccurrences(i), rhs.getOccurrences(i));
        result.addNumber(i, minOccurrences);
    }

    return result;
}

MultiSet MultiSet::compliment() const {
    MultiSet result(n, k);

    for (int i = 0; i <= result.countOfBuckets; i++) {
        result.buckets[i] = ~buckets[i];
    }

    return result;
}




int main()
{

}
