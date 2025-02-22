#include <iostream>

struct Rational {
	int nom;
	int denom;
};

void readRational(Rational& r) {
	std::cin >> r.nom >> r.denom;
}

bool isValid(const Rational& r) {
	return r.denom != 0;
}

void printRational(const Rational& r) {
	std::cout << r.nom << "/" << r.denom << std::endl;
}

int gcd(int a, int b) {
	if (a < b) {
		std::swap(a, b);
	}

	while (b != 0) {
		int temp = a % b;
		a = b;
		b = temp;
	}

	return a;
}

void rationalize(Rational& r) {
	if (!isValid(r)) {
		return;
	}

	int gcdValue = gcd(r.nom, r.denom);

	r.nom /= gcdValue;
	r.denom /= gcdValue;
}

Rational& plusEqual(Rational& lhs, const Rational& rhs) {
	lhs.nom *= rhs.denom;
	lhs.nom += rhs.nom * lhs.denom;
	lhs.denom *= rhs.denom;
	rationalize(lhs);
	return lhs;

}

Rational plusRational(const Rational& lhs, const Rational& rhs) {
	Rational result = lhs;
	plusEqual(result, rhs);
	return result;
}

Rational& minuseEqual(Rational& lhs, const Rational& rhs) {
	Rational negativeRhs = rhs;
	negativeRhs.nom = -rhs.nom;

	return plusEqual(lhs, negativeRhs);
}

Rational minusRational(const Rational& lhs, const Rational& rhs) {
	Rational result = lhs;
	minuseEqual(result, rhs);
	return result;
}

int main() {
	Rational r1{ 3, 4 };
	Rational r2{ 6, 7 };

	Rational r3 = plusRational(r1, r2);
	printRational(r3);

	plusEqual(r3, r1);
	printRational(r3);
}