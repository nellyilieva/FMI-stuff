#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#pragma warning (disable: 4996)

constexpr unsigned int MAX_SIZE = 30;

class Student {
private:
	char* name = nullptr;
	int* grades = nullptr;
	size_t gradesCount = 0;
	char quote[MAX_SIZE + 1] = "";

	void copyFrom(const Student& other);
	void free();

public:
	Student() = default;
	Student(const char* name, const int* grades, size_t gradesCount, const char* quote);

	Student(const Student& other);
	Student& operator=(const Student& other);

	~Student();

	const char* getName() const;
	const int* getGrades() const;
	const char* getQuote() const;
	const size_t getGradesCount() const;

	void setName(const char* newValue);
	void setGrades(const int* newValue, size_t newCount);
	void setQuote(const char* newValue);
};