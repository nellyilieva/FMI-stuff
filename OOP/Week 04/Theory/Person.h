#pragma once
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

constexpr int MIN_NAME = 2;
constexpr int MAX_NAME = 20;
constexpr int MIN_AGE = 5;
constexpr int MAX_AGE = 90;

bool isSmallLetter(char ch);
bool isCapitalLetter(char ch);
bool containsOnlySmallChars(const char* str);


class Person {
private:
	char name[MAX_NAME + 1] = "";
	int age = MIN_AGE;

	bool isValidAge(int age);
	bool isValidName(const char* name);

public:
	Person() = default;
	Person(const char* name, int age);
	
	int getAge() const;
	const char* getName() const;

	void setAge(int age);
	void setName(const char* name);
};
