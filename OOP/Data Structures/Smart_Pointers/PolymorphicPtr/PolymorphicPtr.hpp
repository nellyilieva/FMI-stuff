#pragma once
#include <iostream>

template <class T>
class PolymorphicPtr {
private:
	T* ptr = nullptr;

	void copyFrom(const PolymorphicPtr<T>& other);
	void moveFrom(PolymorphicPtr<T>&& other);
	void free();

public:
	PolymorphicPtr();
	PolymorphicPtr(T* _ptr);

	PolymorphicPtr(const PolymorphicPtr<T>& other);
	PolymorphicPtr& operator=(const PolymorphicPtr<T>& other);

	PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept;
	PolymorphicPtr& operator=(PolymorphicPtr<T>&& other) noexcept;

	~PolymorphicPtr();

	const T* operator->() const;   //the raw pointer; access to the object using ->
	T* operator->();

	const T& operator*() const;  //ref to the object being pointed to => smart pointer like regular pointer
	T& operator*();

};

template <class T>
void PolymorphicPtr<T>::copyFrom(const PolymorphicPtr<T>& other) {
	ptr = other.ptr->clone(); //clone function in the base and der classes!!!!
}

template <class T>
void PolymorphicPtr<T>::moveFrom(PolymorphicPtr<T>&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;
}

template <class T>
void PolymorphicPtr<T>::free() {
	delete ptr;
	ptr = nullptr;
}

template <class T>
PolymorphicPtr<T>::PolymorphicPtr() : ptr(nullptr) {} //= default

template <class T>
PolymorphicPtr<T>::PolymorphicPtr(T* _ptr) : ptr(_ptr) {}

template <class T>
PolymorphicPtr<T>::PolymorphicPtr(const PolymorphicPtr<T>& other) {
	copyFrom(other);
}

template <class T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(const PolymorphicPtr<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
PolymorphicPtr<T>::PolymorphicPtr(PolymorphicPtr<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template <class T>
PolymorphicPtr<T>& PolymorphicPtr<T>::operator=(PolymorphicPtr<T>&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <class T>
PolymorphicPtr<T>::~PolymorphicPtr() {
	free();
}

template <class T>
const T* PolymorphicPtr<T>::operator->() const {
	return ptr;
}

template <class T>
T* PolymorphicPtr<T>::operator->() {
	return ptr;
}

template <class T>
const T& PolymorphicPtr<T>::operator*() const {
	return *ptr;
}

template <class T>
T& PolymorphicPtr<T>::operator*() {
	return *ptr;
}