#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)
#include "Person.h"


bool isSmallLetter(char ch) {
	return 'a' <= ch && ch <= 'z';
}

bool isCapitalLetter(char ch) {
	return 'A' <= ch && ch <= 'Z';
}

bool containsOnlySmallChars(const char* str) {
	while (*str) {
		if (!isSmallLetter(*str)) {
			return false;
		}

		str++;
	}

	return true;
}

bool Person::isValidAge(int age) {
	return MIN_AGE <= age && age <= MAX_AGE;
}

bool Person::isValidName(const char* name) {
	if (!name) {
		return false;
	}

	size_t nameLen = strlen(name);

	if (nameLen <= MIN_NAME || nameLen >= MAX_NAME) {
		return false;
	}

	if (!isCapitalLetter(*name)) {
		return false;
	}

	return containsOnlySmallChars(name + 1);
}

Person::Person(const char* name, int age) {
	setName(name);
	setAge(age);
}

int Person::getAge() const {
	return age;
}
const char* Person::getName() const {
	return name;
}

void Person::setAge(int age) {
	if (isValidAge(age)) {
		this->age = age;
	}
	else {
		this->age = MIN_AGE;
	}
}

void Person::setName(const char* name) {
	if (isValidName(name)) {
		strcpy(this->name, name);
	}
	else {
		strcpy(this->name, "Unknown");
	}
}

int main() {

	
}