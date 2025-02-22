#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)
#include "Interval.h"


bool isPrime(int num) {
	if (num == 2) {
		return true;
	}

	if (num < 2 || num % 2 == 0) {
		return false;
	}

	for (int i = 3; i < sqrt(num); i++) {
		if (num % i == 0) {
			return false;
		}
	}
	return true;
}

int reverseNum(int num) {
	int result = 0;

	while (num != 0) {
		int lastDigit = num % 10;
		result = result * 10 + lastDigit;
		num /= 10;
	}

	return result;
}

bool isPalindrom(int num) {
	return num == reverseNum(num);
}

bool hasDiffDigits(int num) {
	bool digitsCount[10] = {};

	while (num != 0) {
		bool digit = num % 10;
		if (digitsCount[digit]) {
			return false;
		}

		digitsCount[digit] = true;
		num /= 10;
	}

	return true;
}

bool isPow(int n) {
	if (n <= 0) {
		return false;
	}

	return (n & n - 1) == 0;
}


Interval::Interval() : a(0), b(0) {}

Interval::Interval(int _a, int _b) : a(_a), b(_b) {
	if (_a > _b) {
		a = b = 0;
	}
}

int Interval::getStart() const {
	return a;
}

int Interval::getEnd() const {
	return b;
}

void Interval::setStart(int a) {
	if (a > b) {
		return;
	}
	this->a = a;

}

void Interval::setEnd(int b) {
	if (b < a) {
		return;
	}

	this->b = b;
}

int Interval::getLength() const {
	return b - a + 1;
}

bool Interval::isInInterval(int n) const {
	return a <= n && n <= b;
}

int Interval::countOfPrime() const {
	int count = 0;

	for (int i = a; i <= b; i++) {
		if (isPrime(i)) {
			count++;
		}
	}

	return count;
}

int Interval::countOfPalindrom() const {
	int count = 0;

	for (int i = a; i <= b; i++) {
		if (isPalindrom(i)) {
			count++;
		}
	}

	return count;
}

int Interval::countOfUnique() const {
	int count = 0;

	for (int i = a; i <= b; i++) {
		if (hasDiffDigits(i)) {
			count++;
		}
	}

	return count;
}

bool Interval::isPowOfTwo() const {
	int count = 0;

	for (int i = a; i <= b; i++) {
		if (isPow(i)) {
			count++;
		}
	}

	return count;
}

Interval Interval::intersectoin(const Interval& interval) const {
	int maxStart = std::max(a, interval.a);
	int minEnd = std::min(b, interval.b);

	return Interval(maxStart, minEnd);
}

bool Interval::isSubInterval(const Interval& interval) const {
	return a <= interval.getStart() && interval.getEnd() <= b;
}

int main() {

	
}