#include <iostream>
#include <fstream>
#include <sstream>

class DynamicSet {
private:
    uint8_t* buckets;
    size_t bucketsCount = 0;
    unsigned maxNum;

    void copyFrom(const DynamicSet& other) {
        bucketsCount = other.bucketsCount;
        maxNum = other.maxNum;

        buckets = new uint8_t[bucketsCount];

        for (int i = 0; i < bucketsCount; i++) {
            buckets[i] = other.buckets[i];
        }
    }

    void free() {
        delete[] buckets;
    }

    unsigned getBucketIdx(unsigned n) const {
        return n / 8;
    }

public:
    DynamicSet() = default;

    DynamicSet(unsigned maxNum) : maxNum(maxNum) {
        bucketsCount = maxNum / 8 + 1;
        buckets = new uint8_t[bucketsCount];
    }

    DynamicSet(const DynamicSet& other) {
        copyFrom(other);
    }

    DynamicSet& operator=(const DynamicSet& other) {
        if (this != &other) {
            free();
            copyFrom(other);
        }

        return *this;
    }

    ~DynamicSet() {
        free();
    }

    void add(unsigned n) {
        if (n > maxNum) {
            return;
        }

        unsigned bucketsIdx = getBucketIdx(n);
        unsigned bitIdx = n % 8;

        uint8_t mask = 1;
        mask <<= bitIdx;

        buckets[bucketsIdx] |= mask;
    }

    void remove(unsigned n) {
        if (n > maxNum) {
            return;
        }

        unsigned bucketsIdx = getBucketIdx(n);
        unsigned bitIdx = n % 8;

        uint8_t mask = 1;
        mask <<= bitIdx;

        buckets[bucketsIdx] &= (~mask);
    }

    bool isInSet(unsigned n) const {
        if (n > maxNum) {
            return;
        }

        unsigned bucketsIdx = getBucketIdx(n);
        unsigned bitIdx = n % 8;

        uint8_t mask = 1;
        mask <<= bitIdx;

        return buckets[bucketsIdx] & mask;
    }

    void printNumbers() const {
        std::cout << "{ ";
        for (int i = 0; i <= N; i++) {
            if (isInSet(i)) {
                std::cout << i << " ";
            }
        }

        std::cout << "}" << std::endl;
    }

    friend DynamicSet UnionOfSets(const DynamicSet& lhs, const DynamicSet& rhs) {
        DynamicSet result(std::max(lhs.maxNum, rhs.maxNum));

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

    friend DynamicSet IntersectionOfSets(const DynamicSet& lhs, const DynamicSet& rhs) {
        DynamicSet result(std::min(lhs.maxNum, rhs.maxNum));

        unsigned minBucketsCount = std::min(lhs.bucketsCount, rhs.bucketsCount);

        for (int i = 0; i < minBucketsCount; i++) {
            result.buckets[i] = lhs.buckets[i] & rhs.buckets[i];
        }

        return result;
    }
};


int main()
{
    
}

