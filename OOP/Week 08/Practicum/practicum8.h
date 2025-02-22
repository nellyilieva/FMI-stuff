#pragma once

#include <iostream>
#include <fstream>

class Student {
	char* name;
	unsigned fn;
	unsigned group;
	unsigned avgGrade;

	void copyFrom(const Student& other);
	void free();

public:
	Student();
	Student(const Student& other);
	Student& operator=(const Student& other);
	~Student();

	const char* getName() const;
	unsigned getFn() const;
	unsigned getGroup() const;
	unsigned getAvgGrade() const;

	void setName(const char* newName);
	void setFn(unsigned newFn);
	void setGroup(unsigned newGroup);
	void setAvgGrade(unsigned newAvgGrade);

	friend std::istream& operator>>(std::istream&, Student&);
	friend std::ostream& operator<<(std::ostream&, const Student&);
};

bool operator == (const Student& lhs, const Student& rhs);
bool operator != (const Student& lhs, const Student& rhs);
bool operator < (const Student& lhs, const Student& rhs);
bool operator > (const Student& lhs, const Student& rhs);


class University {
private:
	Student** students;
	size_t count;
	size_t capacity;

	void resize();

	void free();
	void copyFrom(const University& other);

public:
	University();
	University(const University& other);
	University& operator=(const University& other);
	~University();

	size_t getCount() const;

	void sort(bool(*cmp)(const Student&, const Student&));
	void filter(bool(*pred)(const Student&));

	University& operator +=(const Student& st);
	University& operator -=(int fn);

	Student& operator[](size_t index);
	const Student& operator[](size_t index) const;

	friend std::istream& operator>>(std::istream& is, University& u);
	friend std::ostream& operator<<(std::ostream& os, const University& u);
};