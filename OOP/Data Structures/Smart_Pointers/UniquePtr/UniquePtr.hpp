﻿#pragma once
#include <iostream>

//точно 1 указател към точно 1 обект
// function T* get(); const T* get() const
//function bool() to check if ptr == nullptr

template <class T>
class UniquePtr {
private:
	T* ptr = nullptr;

	void moveFrom(UniquePtr<T>&& other);
	void free();

public:
	UniquePtr();
	UniquePtr(T* _ptr);

	UniquePtr(const UniquePtr<T>& other) = delete;
	UniquePtr& operator=(const UniquePtr<T>& other) = delete;

	UniquePtr(UniquePtr<T>&& other) noexcept;
	UniquePtr& operator=(UniquePtr<T>&& other) noexcept;

	~UniquePtr();

	const T* operator->() const;
	T* operator->();

	const T& operator*() const;
	T& operator*();

};

template <class T>
void UniquePtr<T>::moveFrom(UniquePtr<T>&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;
}

template <class T>
void UniquePtr<T>::free() {
	delete ptr;
	ptr = nullptr;
}

template <class T>
UniquePtr<T>::UniquePtr() : ptr(nullptr) {} //= default

template <class T>
UniquePtr<T>::UniquePtr(T* _ptr) : ptr(_ptr) {}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept {
	moveFrom(std::move(other));
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

template <class T>
UniquePtr<T>::~UniquePtr() {
	free();
}

template <class T>
const T* UniquePtr<T>::operator->() const {
	return ptr;
}

template <class T>
T* UniquePtr<T>::operator->() {
	return ptr;
}

template <class T>
const T& UniquePtr<T>::operator*() const {
	return *ptr;
}

template <class T>
T& UniquePtr<T>::operator*() {
	return *ptr;
}