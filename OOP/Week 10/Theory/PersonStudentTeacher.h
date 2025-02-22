#include <iostream>

class Person {
private:
	char* name = nullptr;
	int age;

	void copyFrom(const Person& other);
	void moveFrom(Person&& other);

	void free();

protected: //!!!
	void setName(const char* newValue);
	void setAge(int newValue);

public:
	Person() = default;
	Person(const char* name, int age);

	Person(const Person& other);
	Person& operator=(const Person& other);

	Person(Person&& other) noexcept;
	Person& operator=(Person&& other) noexcept;

	~Person();

	const char* getName() const;
	int getAge() const;

	void print() const;
};


class Student : public Person {
private:
	size_t fn = 0;

public:
	Student() = default;
	Student(const char* name, int age, size_t fn);

	size_t getFn() const;
	void setFn(size_t newValue);
};

class Teacher : public Person {
private:
	char** subjects;
	size_t count;

	void copyFrom(const Teacher& other);
	void moveFrom(Teacher&& other);

	void free();

public:
	Teacher(const char* name, int age, const char* const* subjects, size_t count);  //!!!

	Teacher(const Teacher& other);
	Teacher& operator=(const Teacher& other);

	Teacher(Teacher&& other) noexcept;
	Teacher& operator=(Teacher&& other) noexcept;

	~Teacher();

};