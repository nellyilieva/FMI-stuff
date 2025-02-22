#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#pragma warning (disable: 4996)

class SelfCounting {
private:
	const int const_val;

	static unsigned liveObjCount;
	static unsigned createdCount;

public:
	SelfCounting();
	SelfCounting(int val);
	SelfCounting(const SelfCounting& other);
	~SelfCounting();

	static unsigned getLiveObjectsCount();   //we can use only static variables, because static methods
	static unsigned getCreatedCount();
};