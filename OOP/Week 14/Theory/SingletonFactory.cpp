#include "SingletonFactory.h"

SingletonFactory::SingletonFactory() {
	std::ifstream ifs("test.txt");

	if (!ifs.is_open()) {
		throw std::exception("Could not open test.txt");
	}

	ifs >> numbersSize;

	numbers = new size_t[numbersSize];
	size_t idx = 0;

	while (!ifs.eof()) {
		ifs >> numbers[idx++];
	}
}

SingletonFactory::~SingletonFactory() {
	delete[] numbers;
}

Base* SingletonFactory::create() {    //here is our facotry
	if (current >= numbersSize) {
		return nullptr;
	}
	
	if (numbers[current++] % 2 == 0) {
		return new A();
	}

	else {
		return new B();
	}
}

SingletonFactory& SingletonFactory::getInstance() {   //we have one instance for every object
	static SingletonFactory instance;
	return instance;
}

int main() {
	SingletonFactory& sf = SingletonFactory::getInstance();

	sf.create();
	sf.create();
	sf.create();
	sf.create();
}
