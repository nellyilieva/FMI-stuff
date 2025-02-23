﻿#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)
#include "Date.h"

bool Date::isLeapYear() const {
	if (year <= 1916) {
		return year % 4 == 0;
	}
	else {
		return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	}
}
bool Date::validateDate() {
	isDateInValidState = !((month == 0 || month > 12) ||
		(day == 0 || day > MAX_DAYS[month - 1]) ||
		(year == 0) ||
		(year == 1916 && month == 4 && day < 14));
}

Date::Date(unsigned day, unsigned month, unsigned year) {
	setDay(day);
	setMonth(month);
	setYear(year);
}

unsigned Date::getDay() const {
	if (!good()) return 0;
	return day;
}

unsigned Date::getMonth() const {
	if (!good()) return 0;
	return month;
}

unsigned Date::getYear() const {
	if (!good()) return 0;
	return year;
}

void Date::setDay(unsigned day) {
	if (!good()) return;
	this->day = day;
	isModified = true;
	validateDate();
}

void Date::setMonth(unsigned month) {
	if (!good()) return;
	this->month = month;
	isModified = true;
	validateDate();
}

void Date::setYear(unsigned year) {
	if (!good()) return;
	this->year = year;
	if (isLeapYear())
		MAX_DAYS[1] = 29;
	else
		MAX_DAYS[1] = 28;

	isModified = true;
	validateDate();
}

void Date::print() const {
	if (!good()) return;
	std::cout << day << "." << month << "." << year << std::endl;
}

void Date::goToNextDay() {
	if (!good()) return;
	if (year == 1916 && month == 3 && day == 31) //Julian to the Gregorian calendar
	{
		day = 14;
		month = 4;
	}
	else
	{
		day++;
		if (day > MAX_DAYS[month - 1])
		{
			day = 1;
			setMonth(month == 12 ? 1 : (month + 1));
			if (month == 1)
				setYear(year + 1);
		}
	}
	isModified = true;
}

int Date::getDayOfWeek() const {
	if (!good()) return -1;
	if (!isModified)
		return dayOfWeek;

	Date d(1, 1, 1);
	int day = 5; //0 for monday, 6 for sunday (We know that 1.1.1 is saturday)

	while (compareBulgarianDates(d, *this) != 0)  //very simple (but dumb) algorithm
	{
		d.goToNextDay();
		day++;
		day %= 7;
	}
	dayOfWeek = day + 1; //1 for monday, 7 fo sunday
	isModified = false;
	return dayOfWeek;
}

bool Date::good() const {
	return isDateInValidState;
}

void Date::clear() {
	isDateInValidState = true;
	day = month = year = 1;
}

int compareBulgarianDates(const Date& lhs, const Date& rhs) {
	if (lhs.getYear() < rhs.getYear())
	{
		return -1;
	}
	else if (lhs.getYear() > rhs.getYear())
	{
		return 1;
	}
	else
	{ // years are equal, compare months
		if (lhs.getMonth() < rhs.getMonth())
		{
			return -1;
		}
		else if (lhs.getMonth() > rhs.getMonth())
		{
			return 1;
		}
		else
		{ // months are equal, compare days
			if (lhs.getDay() < rhs.getDay())
			{
				return -1;
			}
			else if (lhs.getDay() > rhs.getDay())
			{
				return 1;
			}
			else
			{
				return 0; // All are equal
			}
		}
	}
}

int main () {
	
}
