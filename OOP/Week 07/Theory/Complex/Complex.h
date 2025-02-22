#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)


//Задача 2: Реализирайте клас ComplexNumber, който ще се използва за работа с комплексни числа.
//Предефинирайте оператори със следната функционалност :
//
//Събиране на комплексни числа.
//Изваждане на комплексни числа.
//Умножение на комплексни числа.
//Деление на комплексни числа
//Вход и изход от потоци.

class Complex {
private:
	double real;
	double im;

public:
	Complex();
	Complex(double real, double im);

	double getReal() const;
	double getIm() const;

	void setReal(double real);
	void setIm(double im);

	Complex getConjugated() const;

	Complex& operator+=(const Complex& other);
	Complex& operator-=(const Complex& other);
	Complex& operator*=(const Complex& other);
	Complex& operator/=(const Complex& other);

	friend std::ostream& operator<<(std::ostream& os, const Complex& c);
	friend std::istream& operator>>(std::istream& is, Complex& c);
};

Complex operator+(const Complex& lhs, const Complex& rhs);
Complex operator-(const Complex& lhs, const Complex& rhs);
Complex operator*(const Complex& lhs, const Complex& rhs);
Complex operator/(const Complex& lhs, const Complex& rhs);

bool operator==(const Complex& lhs, const Complex& rhs);
bool operator!=(const Complex& lhs, const Complex& rhs);