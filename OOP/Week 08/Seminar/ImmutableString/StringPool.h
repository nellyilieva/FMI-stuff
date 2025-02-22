#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)

//При използване на класа String можем да достигнем до следния случай :
//
//string str1 = "Hello";
//string str2 = "Hello";
// 
//В този случай двата стринга пазят памет с една и съща стойност.
//В класическата имплементация на string, използвана от стандартната библиотека на C++ това поведение е по подразбиране.
//Всеки низ пази своята памет.
//
//Съществува алтернативна имплементация, която ни ограничава, но е по ефикасна от към памет.
//Имплементацията забранява промяната на низовете, но низовете с еднаква стойност споделят паметта си.
//
//Този начин на реализация на класа String използва идеята за StringPool - обект,
//който разпределя паметта между инстанциите на класа string.
//
//Да се реализира клас ImmutableString, който реализира описаната схема за работа с паметта.
// 
//За тази цел ще се наложи да реализираме клас StringPool, който да пази паметта.
//Класът StringPool съдържа следния публичен интерфейс :
//
//getString(const char*) - връща указател към низа ако съществува. B противен случай го създава и връща указател към него.
//removeString(const char*) - сигнализира, че един от потребителите на низа е спрял да го използва.
// 
//Ако низа няма никакви потребители той се изтрива.
//Класът няма горна граница за низовете които може да поддържа.


//the point of this class is to save the information about a string -> what is the string and how many times it is refered to
//we use struct StringData for that and we create array of structs with of course size (which is count of unique strings) and capacity
//resize function Big 4(what do we need from it and why???)
//functions to save new string, find string, remove string (string record)
//and functions to return the string and to remove it
//we keep in mind that we have refCount and according to it (if it is 0 or more) we should do different things !!!

class StringPool {
private:
	struct StringData {
		char* str = nullptr;
		unsigned refCount = 0;
	};

	StringData* stringRecords;
	size_t size = 0;
	size_t capacity = 0;

	void resize(unsigned newCapacity);

	//we return the positin of the string in the array
	unsigned allocateString(const char* str);
	int findString(const char* str) const;

	void removeRecord(unsigned idx);

public:
	StringPool();

	StringPool(const StringPool& other) = delete;
	StringPool& operator=(const StringPool& other) = delete;

	~StringPool();

	const char* getString(const char* str);
	void removeString(const char* str);
};