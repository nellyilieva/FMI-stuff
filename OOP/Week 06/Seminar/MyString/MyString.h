#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#pragma warning (disable: 4996)

//Реализирайте клас String, който се използва за работа с низове с произволна дължина.
//Трябва да поддържаме следния интерфейс :
//
//length - дължината на низа
//c_str - c style указател към низа


class MyString {
private:
	char* str = nullptr;
	size_t length = 0;

	void copyFrom(const MyString& other);
	void free();

	MyString(size_t length);

public:
	MyString();
	MyString(const char* str);

	MyString(const MyString& other);
	MyString& operator=(const MyString& other);

	~MyString();

	size_t getLength() const;
	const char* c_str() const;
};