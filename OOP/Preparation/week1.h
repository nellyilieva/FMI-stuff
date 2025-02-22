#pragma once
#include <iostream>

class Rational {
private:
    int nom;
    int denom;

public:

    Rational();
    Rational(int newNom, int newDenom);

    int getNom() const;
    int getDenom() const;

    void setNom(int newnom);
    void setDenom(int newDenom);

    void rationalize();

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);

    friend std::ostream& operator<< (std::ostream& os, const Rational& rat);
    friend std::istream& operator>> (std::istream& is, Rational& rat);
};

bool isValidDenom(int denom);
unsigned getGcd(unsigned a, unsigned b);

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);


