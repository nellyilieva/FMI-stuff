#pragma once
#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

bool isPrime(int num);
int reverseNum(int num);
bool isPalindrom(int num);
bool hasDiffDigits(int num);
bool isPow(int n);


class Interval {
private:
	int a;
	int b;

public:
	Interval();
	Interval(int _a, int _b);

	int getStart() const;
	int getEnd() const;

	void setStart(int a);
	void setEnd(int b);

	int getLength() const;
	bool isInInterval(int n) const;

	int countOfPrime() const;
	int countOfPalindrom() const;
	int countOfUnique() const;
	
	bool isPowOfTwo() const;

	Interval intersectoin(const Interval& interval) const;
	bool isSubInterval(const Interval& interval) const;
};