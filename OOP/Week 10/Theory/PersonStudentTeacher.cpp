#include "PersonStudentTeacher.h"

void Person::copyFrom(const Person& other) {
	name = new char[strlen(other.name)+ 1];
	strcpy(name, other.name);

	age = other.age;
}

void Person::moveFrom(Person&& other) {
	name = other.name;
	age = other.age;

	other.name = nullptr;
	other.age = 0;
}

void Person::free() {
	delete[] name;
	name = nullptr;
	age = 0;
}

void Person::setName(const char* newValue) {  //!!!
	if (!newValue || name == newValue) {
		return;
	}

	delete[] name;
	name = new char[strlen(newValue) + 1];
	strcpy(name, newValue);

}

void Person::setAge(int newValue) {
	age = newValue;
}

Person::Person(const char* name, int age) {
	setName(name);
	setAge(age);
}

Person::Person(const Person& other) {
	copyFrom(other);
}

Person& Person::operator=(const Person& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Person::Person(Person&& other) noexcept {
	moveFrom(std::move(other));
}

Person& Person::operator=(Person&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Person::~Person() {
	free();
}

const char* Person::getName() const {
	return name;
}

int Person::getAge() const {
	return age;
}

void Person::print() const {
	std::cout << name << " " << age << std::endl;
}



Student::Student(const char* name, int age, size_t fn) : Person(name, age) {
	setFn(fn);
}

size_t Student::getFn() const {
	return fn;
}

void Student::setFn(size_t newValue) {
	if (newValue < 100) {
		fn = 100;
	}

	fn = newValue;
}


void Teacher::copyFrom(const Teacher& other) {
	subjects = new char* [other.count];

	for (int i = 0; i < other.count; i++) {
		subjects[i] = new char[strlen(other.subjects[i]) + 1];
		strcpy(subjects[i], other.subjects[i]);
	}

	count = other.count;
}

void Teacher::moveFrom(Teacher&& other) {
	subjects = other.subjects;
	count = other.count;

	other.subjects = nullptr;
	other.count = 0;
}

void Teacher::free() {
	for (int i = 0; i < count; i++) {
		delete subjects[i];
	}

	delete[] subjects;

	count = 0;
}

Teacher::Teacher(const char* name, int age, const char* const* subjects, size_t count) : Person(name, age) {
	this->subjects = new char* [count];

	for (int i = 0; i < count; i++) {
		this->subjects[i] = new char[strlen(subjects[i]) + 1];
		strcpy(this->subjects[i], subjects[i]);
	}

	this->count = count;
}

Teacher::Teacher(const Teacher& other) : Person(other) {
	copyFrom(other);
}

Teacher& Teacher::operator=(const Teacher& other) {
	if (this != &other) {
		Person::operator=(other);
		free();
		copyFrom(other);
	}

	return *this;
}

Teacher::Teacher(Teacher&& other) noexcept : Person(std::move(other)) {
	moveFrom(std::move(other));
}

Teacher& Teacher::operator=(Teacher&& other) noexcept {
	if (this != &other) {
		Person::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Teacher::~Teacher() {
	free();
}

int main()
{

}