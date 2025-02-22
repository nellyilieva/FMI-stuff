#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)


//Задача 1: Реализирайте клас Nvector, който ще се използва за работа с математически вектор.
//Предефинирайте оператори със следната функционалност :
//
//Събиране на вектори.
//Изваждане на вектори.
//Умножение на вектор със скалар.
//Проверка дали два вектора са успоредни.
//Проверка дали два вектора са перпендикулярни.
//Взимане на дължина на вектор.
//Достъп до произволен елемент на вектор.
//Вход и изход от потоци.

class NVector {
private:
	int* data;
	size_t size;

	void copyFrom(const NVector& other);
	void free();

public:
	NVector(size_t size);

	NVector(const NVector& other);
	NVector& operator=(const NVector& other);

	~NVector();

	NVector& operator+=(const NVector& other);
	NVector& operator-=(const NVector& other);


	NVector& operator*=(size_t scalar);

	int& operator[](size_t); //get set
	int operator[](size_t) const; // get

	size_t operator~() const;// size;

	friend std::ostream& operator<<(std::ostream& os, const NVector& v);
	friend std::istream& operator>>(std::istream&, NVector& v);
};

NVector operator+(const NVector& lhs, const NVector& rhs);
NVector operator-(const NVector& lhs, const NVector& rhs);


//So it could be commutative:
NVector operator*(const NVector& lhs, size_t scalar);
NVector operator*(size_t scalar, const NVector& lhs);


//are parallel
bool operator||(const NVector& lhs, const NVector& rhs);


//scalar product
size_t operator%(const NVector& lhs, const NVector& rhs);


//are perpendicular
bool operator|=(const NVector& lhs, const NVector& rhs);