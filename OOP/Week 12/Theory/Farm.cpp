#include "Farm.h"

Animal::Animal(AnimalType type) : type(type) {}

AnimalType Animal::getType() const {
	return type;
}

Cat::Cat() : Animal(AnimalType::Cat) {}

void Cat::roar() const {
	std::cout << "Meow" << std::endl;
}

Animal* Cat::clone() const {
	return new Cat (*this);         //Animal* newObj = new  (std::nothrow)Cat(*this); //copy constr  return newObj;
}

Dog::Dog() : Animal (AnimalType::Dog) {}

void Dog::roar() const {
	std::cout << "Bau" << std::endl;
}

Animal* Dog::clone() const {
	return new Dog(*this);
}

Cow::Cow() : Animal(AnimalType::Cow) {}

void Cow::roar() const {
	std::cout << "Muu" << std::endl;
}

Animal* Cow::clone() const {
	return new Cow(*this);
}

Animal* animalFactory(AnimalType type) {
	switch (type) {
	case AnimalType::Dog: return new Dog(); break;
	case AnimalType::Cat: return new Cat(); break;
	case AnimalType::Cow: return new Cow(); break;
	}
	return nullptr;
}

void Farm::resize(unsigned newCapacity) {
	Animal** newCollection = new Animal * [newCapacity];
	for (size_t i = 0; i < size; i++) {
		newCollection[i] = animals[i];
	}

	delete[] animals;
	animals = newCollection;
	capacity = newCapacity;
}

void Farm::copyFrom(const Farm& other) {
	size = other.size;
	capacity = other.capacity;

	animals = new Animal * [other.capacity];

	for (int i = 0; i < size; i++) {
		animals[i] = other.animals[i]->clone();         //!!!
	}
}

void Farm::moveFrom(Farm&& other) {
	size = other.size;
	capacity = other.capacity;

	animals = other.animals;
	other.animals = nullptr;

	other.size = other.capacity = 0;
}

void Farm::free() {
	for (int i = 0; i < size; i++) {
		delete animals[i];
	}

	delete [] animals;

	size = capacity = 0;
}

Farm::Farm() : size(0), capacity(8) {
	animals = new Animal * [capacity];	
}

Farm::Farm(const Farm& other) {
	copyFrom(other);
}

Farm& Farm::operator=(const Farm& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Farm::~Farm() {
	free();
}

Farm::Farm(Farm&& other) noexcept {
	moveFrom(std::move(other));
}

Farm& Farm::operator=(Farm&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

AnimalType Farm::getTypeByIndex(unsigned index) const {
	if (index > size) {
		throw std::out_of_range("Invalid index");
	}

	return animals[index]->getType();
}

//use the factory to create the animal
void Farm::addAnimal(AnimalType animalType) {
	if (size >= capacity) {
		resize(capacity * 2);
	}

	animals[size++] = animalFactory(animalType);
}

void Farm::addAnimal(const Animal& animal) {
	if (size >= capacity) {
		resize(capacity * 2);
	}

	animals[size++] = animal.clone(); //!!!
}

void Farm::roarAll() const {
	for (int i = 0; i < size; i++) {
		animals[i]->roar();
	}
}