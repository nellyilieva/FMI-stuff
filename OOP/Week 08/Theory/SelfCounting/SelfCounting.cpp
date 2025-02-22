#include <iostream>
#include "SelfCounting.h"

//!!!!!!
unsigned SelfCounting::liveObjCount = 0;
unsigned SelfCounting::createdCount = 0;

SelfCounting::SelfCounting() : SelfCounting(42) {}

SelfCounting::SelfCounting(int val) : const_val(val) {
    liveObjCount++;
    createdCount++;
}

SelfCounting::SelfCounting(const SelfCounting& other) : const_val(other.const_val) {
    liveObjCount++;
    createdCount++;
}

SelfCounting::~SelfCounting() {
    liveObjCount--;
}

unsigned SelfCounting::getLiveObjectsCount() {
    return liveObjCount;
}

unsigned SelfCounting::getCreatedCount() {
    return createdCount;
}

int main() {
    SelfCounting s(4);
    SelfCounting s2(30);

    {
        SelfCounting s3(232);

        std::cout << SelfCounting::getCreatedCount() << " " << SelfCounting::getLiveObjectsCount() << std::endl;
    } // end of scoupe -> end of live of s3

    std::cout << SelfCounting::getCreatedCount() << " " << SelfCounting::getLiveObjectsCount() << std::endl;
}   