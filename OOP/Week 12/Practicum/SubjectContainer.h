#pragma once
#include "Subject.h"

class SubjectContainer {
private:
	Subject** subjects = nullptr;
	size_t count;
	size_t capacity;

	void resize();

	void free();
	void copyFrom(const SubjectContainer& other);
	void moveFrom(SubjectContainer&& other);

public:
	SubjectContainer();

	SubjectContainer(const SubjectContainer& other);
	SubjectContainer(SubjectContainer&& other) noexcept;

	SubjectContainer& operator=(const SubjectContainer& other);
	SubjectContainer& operator=(SubjectContainer& other) noexcept;

	~SubjectContainer();

	size_t getCount() const;

	Subject* getSubject() const;

	void addSubject(SubjectType type);
};
