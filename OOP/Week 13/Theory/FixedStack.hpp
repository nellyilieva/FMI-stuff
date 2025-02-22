#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)

//Релизирайте структурата от данни FixedLengthStack
//
//Пример :
//
//int main() {
//    FixedLengthStack<int, 5> st;
//
//    for (size_t i = 0; i < 5; ++i) { // if i < 6 it should throw an error
//        st.push(i);
//    }
//
//    Stack st1 = st;
//    Stack st2;
//    st2 = st1;
//    Stack st3 = std::move(st1);
//
//    while (!st2.empty()) {
//        std::cout << st2.pop() << ' ';
//    }
//    std::cout << std::endl;
//    return 0;
//}

template <class T, const size_t S>   //S is capacity
class FixedStack {
private:
	T* data[S];
	size_t size = 0;

public:
	void push(const T& obj);
	void push(T&& obj);

	const T& peek() const;       //look at the last added => first out

	void pop();

	bool isEmpty() const;
	bool isFull() const;

	void clear();
};

template <class T, const size_t S>
void FixedStack<T, S>::push(const T& obj) {
	if (size == S) {
		return;
	}

	data[size++] = obj;
}

template <class T, const size_t S>
void FixedStack<T, S>::push(T&& obj) {
	if (size == S) {
		return;
	}

	data[size++] = std::move(obj);
}

template <class T, const size_t S>
const T& FixedStack<T, S>::peek() const {
	if (isEmpty()) {
		throw std::out_of_range("Error!");
	}

	return data[size - 1];
}

template <class T, const size_t S>
void FixedStack<T, S>::pop() {
	if (isEmpty()) {
		throw std::out_of_range("Error!");
	}

	size--;
}

template <class T, const size_t S>
bool FixedStack<T, S>::isEmpty() const {
	return size == 0;
}

template <class T, const size_t S>
bool FixedStack<T, S>::isFull() const {
	return size == S;
}

template <class T, const size_t S>
void FixedStack<T, S>::clear() {
	size = 0;
}