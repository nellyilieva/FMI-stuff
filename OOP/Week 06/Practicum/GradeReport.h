#pragma once
#include <iostream>

class GradeReport {
private:
	int* grades = nullptr;
	unsigned gradesCount = 0;
	char* name = nullptr;

	void copyFrom(const GradeReport& data);
	void free();

public:
	GradeReport();
	GradeReport(const int* grades, unsigned gradesCount, const char* name);
	~GradeReport();

	GradeReport(const GradeReport& other);
	GradeReport& operator=(const GradeReport& other);

	int countGrades() const;
	void printName() const;
};
