#include <iostream>
#include "BigNumber.h"

bool containsOnlyNumbers(const char* str) {
    if (str[0] == '-') {
        for (size_t i = 1; str[i] != '\0'; i++) {
            if (!isNumber(str[i]))
                return false;
        }
        return true;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (!isNumber(str[i]))
            return false;
    }
    return true;
}

bool isNumber(char ch) {
	return (ch >= '0' && ch <= '9');
}

void BigNumber::setNumber(const char* n) {
    if (!n || !containsOnlyNumbers(n)) {
        throw std::runtime_error("Error");
    }

    free();
    number = new char[strlen(n) + 1];
    strcpy(number, n);
    size = strlen(n);
    isPositiveNumber = (n[0] != '-');
}

void BigNumber::resize() {

}

void BigNumber::copyFrom(const BigNumber& other) {
    size = other.size + 1;
    isPositiveNumber = other.isPositiveNumber;
    number = new char[other.size + 1];
    strcpy(number, other.number);

}

void BigNumber::free() {
    delete[] number;
    number = nullptr;
    size = 0;
    isPositiveNumber = true;
}


BigNumber::BigNumber() : number(0) {}

BigNumber::BigNumber(const char* _number) {
    setNumber(_number);
}

BigNumber::BigNumber(long long int _number) {

}

BigNumber::BigNumber(const BigNumber& other) {
	copyFrom(other);
}

BigNumber& BigNumber::operator=(const BigNumber& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	*this;
}

BigNumber::~BigNumber() {
	free();
}

bool BigNumber::operator == (const BigNumber& other) const {

}

bool BigNumber::operator != (const BigNumber& other) const {

}

bool BigNumber::operator < (const BigNumber& other) const {

}

bool BigNumber::operator > (const BigNumber& other) const {

}

BigNumber& BigNumber::operator += (const BigNumber& other);
BigNumber BigNumber::operator + (const BigNumber& other) const;
BigNumber& BigNumber::operator -= (const BigNumber& other);
BigNumber BigNumber::operator - (const BigNumber& other) const;
BigNumber& BigNumber::operator *= (const BigNumber& other);
BigNumber BigNumber::operator * (const BigNumber& other) const;

BigNumber& BigNumber::operator ++ ();
BigNumber BigNumber::operator ++ (int);

BigNumber& BigNumber::operator -- ();
BigNumber BigNumber::operator -- (int);

BigNumber& BigNumber::operator - ();

BigNumber& BigNumber::operator /= (const BigNumber& other);
BigNumber BigNumber::operator / (const BigNumber& other) const;
BigNumber& BigNumber::operator %= (const BigNumber& other);
BigNumber BigNumber::operator % (const BigNumber& other) const;

std::istream& operator>>(std::istream& is, BigNumber& n);
std::ostream& operator<<(std::ostream& os, const BigNumber& n);

int main() {

}
