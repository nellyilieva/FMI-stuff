#pragma once
#include <iostream>
#include <utility>
#include <exception>
#include <fstream>

//Пример от конспект SingletonFactory
//
//На база поредно прочетено число от файл решаваме какъв обект да създадем.
//Защо да е Singleton, няма нужда всеки път да отворяме поток към файла само, 
//за да прочитаме едно число - зареждаме файла един път в началото и ползваме вече прочетен масив.

class Base {
public:
	virtual ~Base() = default;
};

class A : public Base {};
class B : public Base {};


class SingletonFactory {
private:
	size_t current = 0;
	size_t numbersSize = 0;
	size_t* numbers = nullptr;

	SingletonFactory();
	~SingletonFactory();

public:
	SingletonFactory(const SingletonFactory& other) = delete;
	SingletonFactory& operator=(const SingletonFactory& other) = delete;

	Base* create();

	static SingletonFactory& getInstance();
};