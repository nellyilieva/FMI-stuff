#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)

template <typename T>
class Vector {
private:
	T* data;
	size_t size;
	size_t capacity;

	void resize(size_t newCap);

	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void free();

public:
	Vector();
	Vector(size_t capacity);

	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);

	Vector(Vector<T>&& other) noexcept;
	Vector<T>& operator=(Vector<T>&& other) noexcept;

	~Vector();

	size_t getSize() const;
	size_t getCapacity() const;

	void push_back(const T& element);
	void push_back(T&& element);

	void push_at(const T& element, size_t idx);
	void push_at(T&& element, size_t idx);

	T pop_back();
	T pop_at(size_t idx);

	bool empty() const;
	void clear();

	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;
};

template <typename T>
void Vector<T>::resize(size_t newCap) {
	T* temp = new T[newCap];

	for (int i = 0; i < size; i++) {
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;

	capacity = newCap;
}

template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
	size = other.size;
	capacity = other.capacity;

	data = new T[other.capacity];
	for (int i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}

}

template <typename T>
void Vector<T>::moveFrom(Vector<T>&& other) {
	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = other.capacity = 0;
}

template <typename T>
void Vector<T>::free() {
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

template<typename T>
Vector<T>::Vector() : Vector(8) { }

template<typename T>
Vector<T>::Vector(size_t capacity) : capacity(capacity) {
	data = new T[capacity];
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
	copyFrom(other);
}
template<typename T>
Vector<T>::Vector(Vector<T>&& other) {
	move(std::move(other));
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other) {
		free();
		move(std::move(other));
	}

	return *this;
}

template<typename T>
Vector<T>::~Vector() {
	free();
}

template<typename T>
size_t Vector<T>::getSize() const {
	return size;
}

template<typename T>
size_t Vector<T>::getCapacity() const {
	return capacity;
}

template<typename T>
void Vector<T>::push_back(const T& element) {
	if (size >= capacity) {
		resize();
	}

	data[size++] = element;
}

template<typename T>
void Vector<T>::push_back(T&& element) {
	if (size >= capacity) {
		resize();
	}

	data[size++] = std::move(element);
}

template<typename T>
void Vector<T>::push_at(const T& element, size_t idx) {
	if (idx >= size) {
		throw std::exception("Out of range");
	}

	if (size >= capacity) {
		resize();
	}

	for (int i = size; i > idx; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[idx] = element;
	size++;
}

template<typename T>
void Vector<T>::push_at(T&& element, size_t idx) {
	if (idx >= size) {
		throw std::exception("Out of range");
	}

	if (size >= capacity) {
		resize();
	}

	for (int i = size; i > idx; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[idx] = std::move(element);
	size++;
}

template<typename T>
T Vector<T>::pop_back() {
	if (empty()) {
		throw std::logic_error("empty");
	}

	return data[--size];
}

template<typename T>
T Vector<T>::pop_at(size_t idx) {
	if (idx >= size) {
		throw std::exception("Out of range");
	}

	T temp = data[idx];
	size--;

	for (int i = idx; i < size; i++) {
		data[i] = std::move(data[i + 1]);
	}

	return temp;
}

template<typename T>
bool Vector<T>::empty() const {
	return size == 0;
}

template<typename T>
void Vector<T>::clear() {
	size = 0;
}

template<typename T>
T& Vector<T>::operator[](size_t idx) {
	if (idx >= size) {
		throw std::exception("Out of range");
	}

	return data[idx];
}

template<typename T>
const T& Vector<T>::operator[](size_t idx) const {
	if (idx >= size) {
		throw std::exception("Out of range");
	}

	return data[idx];
}