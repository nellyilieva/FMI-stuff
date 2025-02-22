#include <iostream>
#include "StringPool.h"

void StringPool::resize(unsigned newCapacity) {
    StringData* newData = new StringData[newCapacity]{};

    for (int i = 0; i < size; i++) {
        newData[i] = stringRecords[i];  //shallow copy, so we don't reallocate the strings
    }

    delete[] stringRecords;  //we delete the array, but not the strings, because the constructor of StringData doesn't delete the string
    stringRecords = newData;
    capacity = newCapacity;
}

//we allocate new string on the first free position (size++) (check for capacity) ; refCount = 0; return idx
unsigned StringPool::allocateString(const char* str) {
    if (size == capacity) {
        resize(capacity * 2);
    }

    unsigned firstFreeIdx = size++;
    stringRecords[firstFreeIdx].str = new char[strlen(str) + 1];
    strcpy(stringRecords[firstFreeIdx].str, str);

    stringRecords[firstFreeIdx].refCount = 0;

    return firstFreeIdx;
}


//cmp; return idx
int StringPool::findString(const char* str) const {
    for (int i = 0; i < size; i++) {
        if (strcmp(stringRecords[i].str, str) == 0) {
            return i;
        }
    }

    return -1;
}

//swap with last element and delete
void StringPool::removeRecord(unsigned idx) {
    std::swap(stringRecords[idx], stringRecords[size - 1]);

    delete[] stringRecords[size - 1].str;

    stringRecords[size - 1].str = nullptr;
    stringRecords[size - 1].refCount = 0;

    size--;
}

StringPool::StringPool() : size(0), capacity(8) {
    stringRecords = new StringData[capacity];
}

StringPool::~StringPool() {
    for (int i = 0; i < size; i++) {   //if the class is used correctly all strings will be deleted by this point
        delete stringRecords[i].str;
    }

    delete[] stringRecords;
}

const char* StringPool::getString(const char* str) {
    int idx = findString(str);

    if (idx != -1) {                        //we found string, refCount++ (new wanting of the string -> new reference), return it; 
        stringRecords[idx].refCount++;

        return stringRecords[idx].str;
    }

    else {                                  //we didn't found string; we should allocate it on the first free position; refCount++, return it
        unsigned index = allocateString(str);
        stringRecords[index].refCount++;
        return stringRecords[index].str;
    }
}

void StringPool::removeString(const char* str) {
    int idx = findString(str);

    stringRecords[idx].refCount--;        //we remove it from wanted

    if (stringRecords[idx].refCount == 0) {
        removeRecord(idx);
    }
}

int main() {
    
}   