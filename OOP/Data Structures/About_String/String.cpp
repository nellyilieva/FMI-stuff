#include <iostream>
#include "String.h"

static unsigned roundToPowerOfTwo(unsigned v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}

static unsigned dataToAllocByStringLen(unsigned stringLength)
{
    return std::max(roundToPowerOfTwo(stringLength + 1), 16u);
}

String::String() : String("") {}

String::String(const char* newData) {
    size = std::strlen(newData);
    capacity = dataToAllocByStringLen(size);
    data = new char[capacity];
    std::strcpy(data, newData);
}

String::String(size_t size) {
    capacity = dataToAllocByStringLen(size);
    data = new char[capacity];
    size = 0;
    data[0] = '\0';
}

String::String(const String& other) {
    copyFrom(other);
}

String& String::operator=(const String& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }

    return *this;
}

String::String(String&& other) noexcept {
    moveFrom(std::move(other));
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }

    return *this;
}

String::~String() {
    free();
}

void String::copyFrom(const String& other) {
    capacity = other.capacity;
    size = other.size;

    data = new char[capacity];
    strcpy(data, other.data);
}

void String::moveFrom(String&& other) {
    size = other.size;
    other.size = 0;

    capacity = other.capacity;
    other.capacity = 8;

    data = other.data;
    other.data = nullptr;
}

void String::free() {
    delete[] data;
    data = nullptr;

    size = 0;
    capacity = 8;
}

void String::resize(size_t newCap) {
    char* newData = new char[newCap + 1];
    std::strcpy(newData, data);
    delete[] data;
    data = newData;
    capacity = newCap;
}

size_t String::getSize() const {
    return size;
}

size_t String::getCapacity() const {
    return capacity - 1;
}

const char* String::c_str() const {
    return data;
}

String::operator bool() const {
    return size == 0;
}

String& String::operator+=(const String& other) {
    size += other.size;

    if (size >= capacity) {
        resize(size);
    }

    std::strncat(data, other.data, size);
    return *this;
}

String& String::operator+=(char ch) {
    if (size == capacity) {
        resize(size + 1);
    }

    data[size] = ch;
    size++;

    return *this;
}

char& String::operator[](size_t idx) {
    //check idx
    return data[idx];
}

const char& String::operator[](size_t idx) const {
    //check idx
    return data[idx];
}

String operator+(const String& lhs, const String& rhs) {
    String result(lhs.getSize() + rhs.getSize());
    result += lhs;
    result += rhs;

    return result;
}

std::ostream& operator<<(std::ostream os, const String& obj) {
    return os << obj.c_str();
}

std::istream& operator>>(std::istream is, String& obj) {
    char buff[1024];
    is >> buff;

    size_t buffStringSize = std::strlen(buff);

    if (buffStringSize > obj.getCapacity())
        obj.resize(dataToAllocByStringLen(buffStringSize));

    strcpy(obj.data, buff);
    obj.size = buffStringSize;
    return is;
}

bool operator==(const String& lhs, const String& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const String& lhs, const String& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const String& lhs, const String& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const String& lhs, const String& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const String& lhs, const String& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const String& lhs, const String& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

int main() {

}