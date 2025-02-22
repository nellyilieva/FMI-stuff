#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)

enum class AnimalType {
	Dog,
	Cat,
	Cow
};

class Animal {
private:
	AnimalType type;

public:
	Animal(AnimalType type);
	virtual void roar() const = 0;
	virtual Animal* clone() const = 0;  //the clone is to copy without asking for the type; clone return copy of the object(of this)
	AnimalType getType() const;   //we have a problem, the parent knows about its children (pure virtual getType method)

	virtual ~Animal() = default;
};


class Cat : public Animal {
public:
	Cat();
	void roar() const override;
	Animal* clone() const override;
};

class Dog : public Animal {
public:
	Dog();
	void roar() const override;
	Animal* clone() const override;
};

class Cow : public Animal {
public:
	Cow();
	void roar() const override;
	Animal* clone() const override;
};

//to create different objects -> factory

Animal* animalFactory(AnimalType type);

//polymorphic container
//big 6; getTypeByIdx; roar all; add animal with type and with object
class Farm {
	Animal** animals;  //Animals* directly -> we assign der obj to base obj and base obj can only hold the base part (cus of size...)
	size_t size;
	size_t capacity;

	void resize(unsigned newCapacity);

	void copyFrom(const Farm& other);
	void moveFrom(Farm&& other);
	void free();

public:
	Farm();

	Farm(const Farm& other);
	Farm& operator=(const Farm& other);

	Farm(Farm&& other) noexcept;
	Farm& operator=(Farm&& other) noexcept;

	~Farm();

	AnimalType getTypeByIndex(unsigned index) const;

	void addAnimal(AnimalType animalType);
	void addAnimal(const Animal& animal);
	void roarAll() const;
};