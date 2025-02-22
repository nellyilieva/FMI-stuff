#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)
#include "Complex.h"

Complex::Complex() : real(0), im(0) {}

Complex::Complex(double real, double im) : real(real), im(im) {}

double Complex::getReal() const {
	return real;
}

double Complex::getIm() const {
	return im;
}

void Complex::setReal(double real) {
	this->real = real;
}

void Complex::setIm(double im) {
	this->im = im;
}

Complex Complex::getConjugated() const {
	Complex result(*this);

	result.im *= -1;

	return result;
}

Complex& Complex::operator+=(const Complex& other) {
	real += other.real;
	im += other.im;

	return *this;
}

Complex& Complex::operator-=(const Complex& other) {
	real -= other.real;
	im -= other.im;

	return *this;
}

Complex& Complex::operator*=(const Complex& other) {
	double oldReal = real;
	real = real * other.real - im * other.im;
	im = oldReal * other.im + im * other.real;

	return *this;
}

Complex& Complex::operator/=(const Complex& other) {
	Complex Conjugated = other.getConjugated();

	Complex otherCopy(other);

	*this *= Conjugated;
	otherCopy *= Conjugated;

	if (otherCopy.real != 0) {
		real /= otherCopy.real;
		im /= otherCopy.real;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Complex& c) {
	return os << c.real << " " << c.im << 'i';
}

std::istream& operator>>(std::istream& ifs, Complex& r) {
	return ifs >> r.real >> r.im;
}

Complex operator+(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs);

	result += rhs;

	return result;
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs);

	result -= rhs;

	return result;
}

Complex operator*(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs);

	result *= rhs;

	return result;
}

Complex operator/(const Complex& lhs, const Complex& rhs) {
	Complex result(lhs);

	result /= rhs;

	return result;
}

bool operator==(const Complex& lhs, const Complex& rhs) {
	return lhs.getReal() == rhs.getReal() && lhs.getIm() == rhs.getIm();
}

bool operator!=(const Complex& lhs, const Complex& rhs) {
	return !(lhs == rhs);
}

int main() {
	

}