#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)
#include "Student.h"

void Student::copyFrom(const Student& other) {
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	grades = new int[other.gradesCount];
	for (int i = 0; i < other.gradesCount; i++) {
		grades[i] = other.grades[i];
	}

	gradesCount = other.gradesCount;

	strcpy(quote, other.quote);
}

void Student::free() {
	delete[] name;
	delete[] grades;
}

Student::Student(const char* name, const int* grades, size_t gradesCount, const char* quote) {
	setName(name);
	setGrades(grades, gradesCount);
	setQuote(quote);
}

Student::Student(const Student& other) {
	copyFrom(other);
}

Student& Student::operator=(const Student& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Student::~Student() {
	free();
}

const char* Student::getName() const {
	return name;
}

const int* Student::getGrades() const {
	return grades;
}

const char* Student::getQuote() const {
	return quote;
}

const size_t Student::getGradesCount() const {
	return gradesCount;
}

void Student::setName(const char* newValue) {
	if (!newValue || newValue == name) {
		return;
	}

	delete[] name;

	name = new char[strlen(newValue) + 1];
	strcpy(name, newValue);
}

void Student::setGrades(const int* newValue, size_t newCount) {
	if (!newValue || newValue == grades) {
		return;
	}

	delete[] grades;

	grades = new int[newCount];
	for (int i = 0; i < newCount; i++) {
		grades[i] = newValue[i];
	}

	gradesCount = newCount;
}

void Student::setQuote(const char* newValue) {
	if (!newValue || newValue == quote) {
		return;
	}

	strcpy(quote, newValue);
}

int main () {
	int grades[] = { 3,3,4,4,5,5 };

	Student s1("Ivan", grades, 6, "Quote");

	Student s2 = s1;   //from copy constructor
	s2.setName("Petur");

	Student s3("Martin", grades, 6, "Quote");
	s3 = s1;      //from operator =

}  //call destructor
