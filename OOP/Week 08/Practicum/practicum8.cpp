#include <iostream>
#include "practicum8.h";

const char* Student::getName() const {
	return name;
}

unsigned Student::getFn() const {
	return fn;
}

unsigned Student::getGroup() const {
	return group;
}

unsigned Student::getAvgGrade() const {
	return avgGrade;
}

void Student::copyFrom(const Student& other) {
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	unsigned fn = other.fn;
	unsigned group = other.group;
	unsigned avgGrade = other.avgGrade;
}

void Student::free() {
	delete[] name;
	name = nullptr;

	unsigned fn = 0;
	unsigned group = 0;
	unsigned avgGrade = 0;
}

Student::Student() : fn(0), group(0), avgGrade(0) {
	strcpy(name, " ");
}

Student::Student(const Student& other) {
	copyFrom(other);
}

Student& Student::operator=(const Student& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

Student::~Student() {
	free();
}

void Student::setName(const char* newName) {
	strcpy(name, newName);
}

void Student::setFn(unsigned newFn) {
	fn = newFn;
}

void Student::setGroup(unsigned newGroup) {
	group = newGroup;
}

void Student::setAvgGrade(unsigned newAvgGrade) {
	avgGrade = newAvgGrade;
}

std::istream& operator>>(std::istream& is, Student& s) {
	is >> s.name >> s.fn >> s.avgGrade >> s.group;
	return is;
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
	os << s.name << " " << s.fn <<  " " << s.avgGrade << " " << s.group;
	return os;
}

bool operator == (const Student& lhs, const Student& rhs) {
	if (strcmp(lhs.getName(), rhs.getName()) == 0) {  //plus other param
		return true;
	}

	return false;
}

bool operator != (const Student& lhs, const Student& rhs) {
	if (strcmp(lhs.getName(), rhs.getName()) != 0) {  //plus other param
		return true;
	}

	return false;
}

bool operator < (const Student& lhs, const Student& rhs) {
	if (lhs.getAvgGrade() < rhs.getAvgGrade()) {
		return true;
	}

	return false;
}

bool operator > (const Student& lhs, const Student& rhs) {
	if (lhs.getAvgGrade() > rhs.getAvgGrade()) {
		return true;
	}

	return false;
}


void University::resize() {
	capacity *= 2;
	Student** temp = new Student * [capacity] {};
	for (int i = 0; i < capacity; i++) {
		temp[i] = students[i];
	}

	delete students;
	students = temp;
}

void University::free() {
	for (int i = 0; i < count; i++) {
		delete students[i];
	}

	delete[] students;
	count = 0;
	capacity = 0;

}

void University::copyFrom(const University& other) {
	count = other.count;
	capacity = other.capacity;

	students = new Student * [capacity];

	for (int i = 0; i < other.count; i++) {
		students[i] = new Student(*other.students[i]); //pointers, and because of that
	}

}

University::University() : count(0), capacity(8) {
	students = new Student * [capacity];
}

University::University(const University& other) {
	copyFrom(other);
}

University& University::operator=(const University& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

University::~University() {
	free();
}

size_t University::getCount() const {
	return count;
}

void University::sort(bool(*cmp)(const Student&, const Student&)) {
	for (size_t i = 0; i < count - 1; i++) {
		for (size_t j = 0; j < count - i - 1; j++) {
			if (cmp(*students[j + 1], *students[j])) {
				Student* temp = students[j];
				students[j] = students[j + 1];
				students[j + 1] = temp;
			}
		}
	}
}

void University::filter(bool(*pred)(const Student&)) {
	for (int i = 0; i < count; i++) {
		if (pred(*students[i])) {
			std::cout << *students[i] << std::endl;
		}
	}
}

University& University::operator +=(const Student& st) {
	for (int i = 0; i < count; i++) {
		if (students[i]->getFn() == st.getFn()) {
			return *this;
		}
	}

	if (count == capacity) {
		resize();
	}

	students[count++] = new Student(st);
	return *this;
}

University& University::operator -=(int fn) {
	for (int i = 0; i < count; i++) {
		if (students[i]->getFn() == fn) {
			delete students[i];
			students[i] = students[count - 1];
			count--;
			return *this;
		}
	}
}

Student& University::operator[](size_t index) {
	//check for idx

	return *students[index];
}

const Student& University::operator[](size_t index) const {
	//check for idx

	return *students[index];
}

std::istream& operator>>(std::istream& is, University& u) {
	//
}

std::ostream& operator<<(std::ostream& os, const University& u) {
	os << u.count << std::endl;

	for (int i = 0; i < u.count; i++) {
		os << *u.students[i] << std::endl;
	}

	return os;
}