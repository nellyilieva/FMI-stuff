#pragma once
#include "Vector.hpp"
#include "MyString.h"

class Dis;
class OOP;
class Geometry;

enum class SubjectType {
	Dis = 0,
	OOP = 1,
	Geometry = 2
};

class Subject {
private:
	MyString nameSub = nullptr;
	MyString nameLector = nullptr;
	Vector <MyString> assistants;
	int score = 0;
	SubjectType type;

public:
	Subject() = default;
	Subject(MyString _nameSub, MyString _nameLector, Vector<MyString> _assistants, int _score);
	virtual int gradeToPass() = 0;
	virtual ~Subject() = default;

	void printSubjectName() const;

	const MyString& getNameSub() const;
	const MyString& getNameLector() const;
	int getScore() const;

	virtual Subject* clone() const = 0;

	SubjectType getType() const;


	virtual bool interactWith(const Subject* other) const = 0;

	virtual bool interactWithDis(const Dis* other) const = 0;
	virtual bool interactWithOOP(const OOP* other) const = 0;
	virtual bool interactWithGeometry(const Geometry* other) const = 0;
};