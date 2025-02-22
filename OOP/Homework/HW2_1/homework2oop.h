#pragma once
#include <iostream>


class MultiSet {
    unsigned n = 0;
    unsigned k = 0;

    unsigned countOfBuckets = 0;

    uint8_t* buckets = nullptr;

    void copyFrom(const MultiSet& other);
    void free();

    unsigned getBucket(unsigned n) const;
    unsigned getBit(unsigned idx) const;
    bool isBitZero(unsigned bucket, unsigned bit) const;

    void makeBitOne(unsigned bucketIndex, unsigned bit);
    void makeBitZero(unsigned bucketIndex, unsigned bit);

    void printBucketMemoryView(unsigned idx) const;

public:
    MultiSet();
    MultiSet(unsigned n, unsigned k);
    MultiSet(unsigned n, unsigned k, uint8_t* buckets);

    MultiSet(const MultiSet& other);
    MultiSet& operator=(const MultiSet& other);
    ~MultiSet();

    int getBucketsCount() const;

    void add(unsigned num);
    void addNumber(unsigned num, unsigned n);
    unsigned getOccurrences(unsigned num) const;
    void print() const;
    void printMemoryView() const;
    void serialize(const char* filename) const;
    
    friend MultiSet difference(const MultiSet& lhs, const MultiSet& rhs);
    friend MultiSet intersection(const MultiSet& lhs, const MultiSet& rhs);
    MultiSet compliment() const;
};

MultiSet deserialize(const char* filename);
size_t getFileSize(std::ifstream& ifs);

bool checkBit(unsigned bucket, unsigned bitIndex);