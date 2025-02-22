#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)

//we have circular queue -> the last position is connected to the first forming a circle
//when you add an element using push, it goes to the put position, and put moves forward.
//when you remove an element using pop, it removes the element from the get position, and get moves forward.
//when size == capacity, the queue is full and we return put to 0
//FIFO

template <typename T>
class Queue {
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 8;

	size_t get = 0;  //idx to track position of where to pop next element (delete)
	size_t put = 0;  //idx to track position of where to push next elemenet (add)

	void resize();

	void copyFrom(const Queue<T>& other);
	void moveFrom(Queue<T>&& other);
	void free();

public:
	Queue();

	Queue(const Queue<T>& other);
	Queue& operator=(const Queue<T>& other);

	Queue(Queue<T>&& other) noexcept;
	Queue& operator=(Queue<T>&& other) noexcept;

	~Queue();

	void push(const T& obj);
	void push(T&& obj);

	void pop();

	const T& peek() const;

	bool isEmpty() const;

};

template <typename T>
void Queue<T>::resize() {
	T* temp = new T[capacity * 2];

	for (int i = 0; i < size; i++) {
		temp[i] = data[get];
		(++get) %= capacity;
	}
	delete[] data;
	data = temp;

	capacity *= 2;
	get = 0;      //nex element to delete is first element => 0
	put = size;  //we have increased the capacity, so the next element to add will be at idx size
}

template <typename T>
void Queue<T>::copyFrom(const Queue<T>& other) {
	size = other.size;
	capacity = other.capacity;

	data = new T[other.capacity];
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}

	get = other.get;
	put = other.put;
}

template <typename T>
void Queue<T>::moveFrom(Queue<T>&& other) {
	data = other.data;
	size = other.size;
	capacity = other.capacity;
	put = other.put;
	get = other.get;

	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
	other.get = other.push = 0;
}

template <typename T>
void Queue<T>::free() {
	delete[] data;
}

template <typename T>
Queue<T>::Queue() {
	capacity = 8;
	size = 0;

	get = put = 0;

	data = new T[capacity];
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other) {
	copyFrom(other);
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
Queue<T>::Queue(Queue<T>&& other) {
	moveFrom(std::move(other));
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
Queue<T>::~Queue() {
	free();
}

template <typename T>
void Queue<T>::push(const T& obj) {
	if (size == capacity) {
		resize();
	}

	data[put] = obj;
	(++put) %= capacity;
	size++;
}

template <typename T>
void Queue<T>::push(T&& obj) {
	if (size == capacity) {
		resize();
	}

	data[put] = td::move(obj);
	(++put) %= capacity;
	size++;
}

template <typename T>
void Queue<T>::pop() {
	if (isEmpty()) {
		throw std::logic_error("Empty queue!");
	}

	(++get) %= capacity;
	size--;
}

template <typename T>
const T& Queue<T>::peek() const {
	if (isEmpty()) {
		throw std::logic_error("Empty queue!");
	}

	return data[get];
}

template <typename T>
bool Queue<T>::isEmpty() const {
	return size == 0;
}