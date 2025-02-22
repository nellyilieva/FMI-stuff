#pragma once
#include <iostream>

struct Counter {              //!!!!!
	int useCount = 0;
	int weakCount = 0;

	void addSharedPtr() {
		useCount++;

		if (useCount == 1) {
			weakCount++;
		}
	}

	void removeSharedPtr() {
		useCount--;

		if (useCount == 0) {
			weakCount--;
		}
	}

	void addWeakPtr() {
		weakCount++;
	}

	void removeWeakPtr() {
		weakCount--;
	}
};

template <class T>
class SharedPtr {
private:

	template <class T>
	friend class WeakPtr;

	T* ptr = nullptr;
	Counter* counter = nullptr;

	void copyFrom(const SharedPtr<T>& other);
	void moveFrom(SharedPtr<T>&& other);
	void free();

public:
	SharedPtr();
	SharedPtr(T* _ptr);

	SharedPtr(const SharedPtr<T>& other);
	SharedPtr& operator=(const SharedPtr<T>& other);

	SharedPtr(SharedPtr<T>&& other) noexcept;
	SharedPtr& operator=(SharedPtr<T>&& other) noexcept;

	~SharedPtr();

	const T* operator->() const;
	T* operator->();

	const T& operator*() const;
	T& operator*();

	bool isInitialized() const;
	operator bool() const;

};

template <class T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)	 { 
	ptr = other.ptr;
	counter = other.counter;

	if (counter) {
		counter->addSharedPtr();
	}
}

template <class T>
void SharedPtr<T>::moveFrom(SharedPtr<T>&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;

	counter = other.counter;
	other.counter = nullptr;
}

template <class T>
void SharedPtr<T>::free() {  //!!!!!
	if (ptr == nullptr && counter == nullptr) {
		return;
	}

	if (counter->useCount == 0) {
		delete ptr;
	}

	if (counter->weakCount == 0) {
		delete counter;
	}
}

template <class T>
SharedPtr<T>::SharedPtr() = default;

template <class T>
SharedPtr<T>::SharedPtr(T* _ptr) : ptr(_ptr) {
	if (ptr) {
		counter = new Cointer();
		counter->addSharedPtr();
	}
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other)
{
	copyFrom(other);
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <class T>
SharedPtr<T>::~SharedPtr() {
	free();
}

template <class T>
bool SharedPtr<T>::isInitialized() const {
	return ptr != nullptr;
}

template <class T>
SharedPtr<T>::operator bool() const {
	return ptr != nullptr;
}

template <class T>
const T* SharedPtr<T>::operator->() const {
	return ptr;
}

template <class T>
T* SharedPtr<T>::operator->() {
	return ptr;
}

template <class T>
const T& SharedPtr<T>::operator*() const {
	return *ptr;
}

template <class T>
T& SharedPtr<T>::operator*() {
	return *ptr;
}