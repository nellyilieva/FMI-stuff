#include <iostream>
#include "StringVector.h"

void StringVector::resize(unsigned newCapacity) {
	MyString* newData = new MyString[newCapacity];  //create new

	for (size_t i = 0; i < size; i++) {
		newData[i] = strings[i];
	}

	delete[] strings;
	strings = newData;
	capacity = newCapacity;

}

void StringVector::copyFrom(const StringVector& other) {
	size = other.size;
	capacity = other.capacity;

	strings = new MyString[other.capacity];
	
	for (size_t i = 0; i < size; i++) {
		strings[i] = other.strings[i];
	}
}

void StringVector::free() {
	delete[] strings;
	size = capacity = 0;
}

StringVector::StringVector() : strings(nullptr), size(0), capacity(8) {}

StringVector::StringVector(const StringVector& other) {
	copyFrom(other);
}

StringVector& StringVector::operator=(const StringVector& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

StringVector::~StringVector() {
	free();
}

size_t StringVector::getSize() const {
	return size;
}

size_t StringVector::getCapacity() const {
	return capacity;
}

void StringVector::push_back(const MyString& str) {
	if (size >= capacity) {
		resize(capacity * 2);
	}

	strings[size++] = str;
}

void StringVector::pop_back() {
	if (empty()) {
		throw std::runtime_error("Already empty!");
	}

	else {
		size--;
	}
}

void StringVector::insert(const MyString& str, size_t idx) {
	if (size >= capacity) {
		resize(capacity * 2);
	}

	if (0 <= idx && idx <= size) {

		for (size_t i = size; i > idx; i--) {
			strings[i] = strings[i - 1];
		}

		strings[idx] = str;
		size++;
	}
	else {
		throw std::out_of_range("Index out of range!");
	}
}

void StringVector::erase(size_t idx) {
	if (0 <= idx && idx <= size) {

		for (int i = idx; i < size - 1; i++) {
			strings[i] = strings[i + 1];
		}

		size--;
	}
	else {
		throw std::out_of_range("Index out of range!");
	}
}

void StringVector::clear() {
	free();
}

MyString& StringVector::operator[] (size_t idx) {
	if (idx < 0 || idx >= size) {
		throw std::out_of_range("Index out of range!");
	}

	return strings[idx];
}

const MyString& StringVector::operator[](size_t idx) const {
	if (idx < 0 || idx >= size) {
		throw std::out_of_range("Index out of range!");
	}

	return strings[idx];
}

bool StringVector::empty() const {
	return size == 0;
}

std::ostream& operator<<(std::ostream& os, const StringVector& data) {
	for (size_t i = 0; i < data.getSize(); i++) {
		if (i > 0) {
			os << " ";
		}
		os << data.strings[i];
	}

	return os;
}

std::istream& operator>>(std::istream& is, StringVector& data) {
	MyString buff;

	while (is >> buff) {
		data.push_back(buff);
	}

	return is;
}