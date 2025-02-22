#include "MyString.h"

static unsigned roundToPowOfTwo(unsigned v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;

	return v;
}

static unsigned dataToAllocBySize(unsigned sizeStr) {
	return std::max(roundToPowOfTwo(sizeStr + 1), 16u);
}

void MyString::resize(unsigned newCap) {
	char* temp = new char[newCap + 1];
	std::strcpy(temp, data);
	delete[] data;
	data = temp;
	capacity = newCap;
}

void MyString::copyFrom(const MyString& other) {
	capacity = other.capacity;
	size = other.size;

	data = new char[other.capacity];
	strcpy(data, other.data);
}

void MyString::moveFrom(MyString&& other) {
	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.capacity = other.size = 0;
}

void MyString::free() {
	delete[] data;
	size = capacity = 0;
}

MyString::MyString(size_t size) {
	capacity = dataToAllocBySize(size);

	data = new char[dataToAllocBySize(size)];
	data[0] = '\0';
	this->size = 0;
}

MyString::MyString() : MyString("") {}

MyString::MyString(const char* data) {
	size = std::strlen(data);
	capacity = dataToAllocBySize(size);

	this->data = new char[capacity];
	std::strcpy(this->data, data);
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

//!!!
MyString& MyString::operator+=(const MyString& obj) {
	if (getSize() + obj.getSize() + 1 > capacity) {
		resize(dataToAllocBySize(getSize() + obj.getSize()));
	}

	std::strncat(data, obj.data, obj.getSize());
	size = getSize() + obj.getSize();

	return *this;
}

char& MyString::operator[](size_t idx) {
	return data[idx];
}

const char& MyString::operator[](size_t idx) const {
	return data[idx];
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
	MyString result(lhs.getSize() + rhs.getSize());

	result += lhs;
	result += rhs;

	return result;
}

std::ostream& operator<<(std::ostream& os, const MyString& obj) {
	return os << obj.c_str();
}

std::istream& operator>>(std::istream& is, MyString& obj) {
	char buff[1024];
	is >> buff;

	size_t buffSize = std::strlen(buff);
	if (buffSize > obj.getCapacity()) {
		obj.resize(dataToAllocBySize(buffSize));
	}

	strcpy(obj.data, buff);
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

//!!!
MyString MyString::substr(size_t begin, size_t howMany) const {
	if (begin + howMany > size) {
		throw std::length_error("Substr out of range");
	}

	//size constructor
	MyString substr(howMany + 1);
	strncat(substr.data, data + begin, howMany);

	return substr;
}

int main() {

}
