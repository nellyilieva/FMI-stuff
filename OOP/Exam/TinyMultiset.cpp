#include <iostream>

//class MultiSet {
//public:
//    virtual unsigned operator() (unsigned num) const = 0;
//    virtual ~MultiSet() = default;
//    virtual MultiSet* clone() const = 0;
//};

//0 to 31
constexpr int MAX_NUM = 31;

const unsigned MAX_OCCURANCES = 3;
const unsigned MAX_IN_BUCKET = 4;

class TinyMultiset {
private:
    uint8_t buckets[8] = { 0 };

    unsigned getBucketIdx(unsigned n) const {
        return n / MAX_IN_BUCKET;
    }

    unsigned getBitIdx(unsigned n) const {
        return (n % MAX_IN_BUCKET) * 2;
    }

public:
    unsigned operator() (unsigned num) const {
        if (num > MAX_NUM) {
            return -1;
        }

        unsigned bucketIdx = getBucketIdx(num);
        unsigned bitIdx = getBitIdx(num);

        uint8_t mask = 1;
        mask <<= bitIdx;

        uint8_t curr = buckets[bucketIdx];

        bool isFirstUp = ((curr & mask) == mask);
        mask <<= 1;
        bool isSecondUp = ((curr & mask) == mask);

        return (isFirstUp * 1) + (isSecondUp * 2);
    }

    void add(unsigned num) {
        if (num > MAX_NUM) {
            return;
        }

        unsigned occur = (*this)(num);

        unsigned bucketIdx = getBucketIdx(num);
        unsigned bitIdx = getBitIdx(num);

        uint8_t mask = 1;
        mask <<= bitIdx;

        uint8_t& curr = buckets[bucketIdx];

        switch (occur) {
        case 1: {
            mask = ~mask;
            curr &= mask;
            mask = ~mask;
            mask <<= 1;
            curr |= mask;
            break;
        }
        case 0:
        case 2: {
            curr |= mask;
            break;
        }
        }
    }

    void remove(unsigned num) {
        if (num > MAX_NUM) {
            return;
        }

        unsigned occur = (*this)(num);

        unsigned bucketIdx = getBucketIdx(num);
        unsigned bitIdx = getBitIdx(num);

        uint8_t mask = 1;
        mask <<= bitIdx;

        uint8_t& curr = buckets[bucketIdx];

        switch (occur) {
        case 2: {
            curr |= mask;
            mask <<= 1;
            mask = ~mask;
            curr &= mask;
            break;
        }
        case 1:
        case 3: {
            mask = ~mask;
            curr &= mask;
            break;
        }
        }

    }
};

template <typename M1, typename M2>
class Union {
private:
    const M1* first;         //we use const and pointer to make sure that the class will not change the sets;
    const M2* second;        //if we use &, we will not be able to chsnge the object we point to

public:
    MultiSetIntersection(const M1*& multiset1, const M2*& multiset2) : first(multiset1), second(multiset2) {}

    unsigned operator()(int num) const override {
        return (*first)(num) + (*second)(num);
    }
    
    void setFirst(const M1*& multiset1) {
        first = multiset1;
    }

    void setSecond(const M2*& multiset2) {
        second = multiset2;
    }
};

int main()
{
    
}

