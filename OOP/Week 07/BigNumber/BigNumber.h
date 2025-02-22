#pragma once
#include <iostream>
#include <fstream>

class BigNumber {
private:
	char* number = nullptr;
	bool isPositiveNumber = true;
	size_t size = 0;

	void resize();
	void copyFrom(const BigNumber& other);
	void free();

public:
	BigNumber();
	BigNumber(const char* _number);
	BigNumber(long long int _number);

	BigNumber(const BigNumber& other);
	BigNumber& operator=(const BigNumber& other);

	~BigNumber();

	void setNumber(const char* n);

	bool operator == (const BigNumber& other) const;
	bool operator != (const BigNumber& other) const;
	bool operator < (const BigNumber& other) const;
	bool operator > (const BigNumber& other) const;

	BigNumber& operator += (const BigNumber& other);
	BigNumber operator + (const BigNumber& other) const;
	BigNumber& operator -= (const BigNumber& other);
	BigNumber operator - (const BigNumber& other) const;
	BigNumber& operator *= (const BigNumber& other);
	BigNumber operator * (const BigNumber& other) const;

	BigNumber& operator ++ ();
	BigNumber operator ++ (int);

	BigNumber& operator -- ();
	BigNumber operator -- (int);

	BigNumber& operator - ();

	BigNumber& operator /= (const BigNumber& other);
	BigNumber operator / (const BigNumber& other) const;
	BigNumber& operator %= (const BigNumber& other);
	BigNumber operator % (const BigNumber& other) const;

	friend std::istream& operator>>(std::istream& is, BigNumber& n);
	friend std::ostream& operator<<(std::ostream& os, const BigNumber& n);

};

bool isNumber(char ch);
bool containsOnlyNumbers(const char* str);
