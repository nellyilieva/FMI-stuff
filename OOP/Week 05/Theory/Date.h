#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#pragma warning (disable: 4996)

class Date {
private:
	unsigned MAX_DAYS[12] = { 31,28,31,30,31, 30, 31, 31, 30, 31, 30, 31 };

	unsigned day = 1;
	unsigned month = 1;
	unsigned year = 1;

	bool isDateInValidState = true;
	mutable bool isModified = true;
	mutable int dayOfWeek = -1;

	bool isLeapYear() const;
	bool validateDate();

public:
	Date() = default;
	Date(unsigned day, unsigned month, unsigned year);

	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

	void setDay(unsigned day);
	void setMonth(unsigned month);
	void setYear(unsigned year);

	void print() const;
	void goToNextDay();
	int getDayOfWeek() const;

	bool good() const;
	void clear();
};

int compareBulgarianDates(const Date& lhs, const Date& rhs);