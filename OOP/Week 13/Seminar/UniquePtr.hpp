#pragma once
#include <iostream>
#include <utility>
#include <exception>
#include <fstream>

template<typename T>
class UniquePointer {
private:
	T* ptr;

public:
	UniquePointer(T* ptr);

	UniquePointer(const UniquePointer& other) = delete;
	UniquePointer& operator=(const UniquePointer& other) = delete;

	UniquePointer(UniquePointer&& other) noexcept;
	UniquePointer& operator=(UniquePointer&& other) noexcept;

	~UniquePointer();

	T& operator*();
	const T& operator*() const;

	T* operator->();
	const T* operator->() const;

};

template<typename T>
UniquePointer<T>::UniquePointer(T* ptr) : ptr(ptr) {}

template<typename T>
UniquePointer<T>::UniquePointer(UniquePointer&& other) {
	ptr = other.ptr;

	other.ptr = nullptr;
}

template<typename T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& other) {
	if (this != other) {
		delete ptr;

		ptr = other.ptr;
		other.ptr = nullptr;
	}

	return *this;
}

template<typename T>
UniquePointer<T>::~UniquePointer() {
	delete ptr;
}

template<typename T>
T& UniquePointer<T>::operator*() {
	return *ptr;
}

template<typename T>
const T& UniquePointer<T>::operator*() const {
	return *ptr;
}

template<typename T>
T* UniquePointer<T>::operator->() {
	return ptr;
}

template<typename T>
const T* UniquePointer<T>::operator->() const {
	return ptr;
}