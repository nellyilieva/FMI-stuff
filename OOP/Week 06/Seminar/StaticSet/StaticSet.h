#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>
#pragma warning (disable: 4996)

//Задача 1: Напишете клас Set, който съдържа множество от числа(без повторения) в диапазона от 0 до n - 1,
//където n е подадено в началото(1 <= n <= 1024).Класът трябва да пази дали съдържа дадено число в битове,
//т.е ако съдържа дадено число, съответвеният последователен бит ще бъде 1, в противен случай 0. Пример :
//
//{3, 4, 6} = > битове на множеството ще бъдат 00011010
//
//{1, 8, 9} = > 01000000 11000000
//
//Класът трябва да има следните функции.
//
//Добавяне на число
//Проверка дали съдържа число
//Принтиране на всички числа, които съдържа
//Принтиране на това как е представено в паметта
//Член - функция, която приема друго множество и връща тяхното обединение
//Член - функция, която приема друго множество и връща тяхното сечение
//Бонус 2 : Направете функция, която премахва дадено число от множеството.

constexpr unsigned MAX_NUM = 1023;
constexpr unsigned NUMBERS_COUNT = MAX_NUM + 1;
constexpr unsigned BUCKET_SIZE = sizeof(uint8_t) * 8;
constexpr unsigned BUCKETS_COUNT = NUMBERS_COUNT / BUCKET_SIZE + 1;


class StaticSet {
private:
	uint8_t bucket[BUCKETS_COUNT] = { 0 };

	unsigned getBucketIdx(unsigned n) const;
	unsigned getBitIdx(unsigned n) const;

public:
	StaticSet() = default;

	void add(unsigned n);
	void remove(unsigned n);

	bool isInSet(unsigned n) const;

	void printNumbers() const;
	void memoryView() const;

	StaticSet unionOfSets(const StaticSet& other);
	StaticSet intersectionOfSets(const StaticSet& other);
};