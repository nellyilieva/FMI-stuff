#include "MyString.h"

static unsigned roundToPowerOfTwo(unsigned v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	return v++;
}

static unsigned dataToAllocByGivenSize(unsigned strSize) {
	return std::max(roundToPowerOfTwo(strSize + 1), 16u);
}


//все едно прехвърляме data/size/capacity; we don't change anything in the string; we change the pointer
void MyString::resize(unsigned newCapacity) {
	char* temp = new char[newCapacity + 1];
	std::strcpy(temp, data);

	delete[] data;
	data = temp;
	capacity = newCapacity;
}

void MyString::copyFrom(const MyString& other) {
	capacity = other.capacity;

	data = new char[other.capacity];
	std::strcpy(data, other.data);

	size = other.size;
}

void MyString::moveFrom(MyString&& other) {
	data = other.data;
	capacity = other.capacity;
	size = other.size;

	other.data = nullptr;
	other.capacity = other.size = 0;
}

void MyString::free() {
	delete[] data;
	size = capacity = 0;
}

//size = 0
MyString::MyString(size_t size) {
	capacity = dataToAllocByGivenSize(size);
	data = new char[capacity];
	size = 0;
	data[0] = '\0';
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* str) {
	size = std::strlen(str);
	capacity = dataToAllocByGivenSize(size);

	data = new char[capacity];
	std::strcpy(data, str);
}

MyString::MyString(const MyString& other) {
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MyString::MyString(MyString&& other) noexcept {
	moveFrom(std::move(other));
}

MyString& MyString::operator=(MyString&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

MyString::~MyString() {
	free();
}

size_t MyString::getSize() const {
	return size;
}

size_t MyString::getCapacity() const {
	return capacity;
}

const char* MyString::c_str() const {
	return data;
}

char& MyString::operator[](size_t idx) {
	return data[idx];
}

const char& MyString::operator[](size_t idx) const {
	return data[idx];
}

MyString& MyString::operator+=(const MyString& obj) {
	if (getSize() + obj.getSize() + 1 > capacity) {
		resize(dataToAllocByGivenSize(getSize() + obj.getSize()));
	}
	
	std::strncat(data, obj.data, obj.getSize());

	size = getSize() + obj.getSize();

	return *this;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
	MyString result(lhs.getSize() + rhs.getSize());

	result += lhs;
	result += rhs;

	return result;
}

//write; to read the obj
std::ostream& operator<<(std::ostream& os, const MyString& obj) {
	return os << obj.c_str();
}

//read -> create the obj; to write into the obj
std::istream& operator>>(std::istream& is, MyString& obj) {
	char buff[1024];
	is >> buff;

	size_t buffSize = std::strlen(buff);

	if (buffSize > obj.getCapacity()) {
		obj.resize(buffSize);
	}

	std::strcpy(obj.data, buff);
	obj.size = buffSize;

	return is;
}

bool operator==(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

bool operator<(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator>=(const MyString& lhs, const MyString& rhs) {
	return std::strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}