#pragma once
#include <iostream>

//много указатели към 1 обект
//обектът се заделя при 1-вия указател и се изтрива при изтриването на последния

template <class T>
class SharedPtr {
private:
	T* ptr = nullptr;
	int* refCount = 0;  //!!!

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

};

template <class T>
void SharedPtr<T>::copyFrom(const SharedPtr<T>& other)	 { 
	ptr = other.ptr;
	refCount = other.refCount;

	if (refCount) {     //!!!!!
		refCount++:
	}
}

template <class T>
void SharedPtr<T>::moveFrom(SharedPtr<T>&& other) {
	ptr = other.ptr;
	other.ptr = nullptr;

	refCount = other.refCount;
	other.refCount = nullptr; //!!!
}

template <class T>
void SharedPtr<T>::free() {  //!!!!!
	if (ptr == nullptr && refCount == nullptr) {
		return;
	}

	if (*refCount == 1) {
		delete ptr;
		delete refCount;
	}
	else {
		(*refCount)--;
	}
}

template <class T>
SharedPtr<T>::SharedPtr() = default;

template <class T>
SharedPtr<T>::SharedPtr(T* _ptr) : ptr(_ptr) {  //!!!!!
	if (ptr) {
		refCount = new int(1);
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