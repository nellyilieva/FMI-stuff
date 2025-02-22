#include "SubjectContainer.h"
#include "SubjectFactory.h"

void SubjectContainer::resize() {
	Subject** temp = new Subject * [capacity * 2];

	for (int i = 0; i < count; i++) {
		temp[i] = subjects[i];
	}

	delete[] subjects;
	subjects = temp;
}

void SubjectContainer::free() {
	for (int i = 0; i < count; i++) {
		delete subjects[i];
	}

	delete[] subjects;

	count = 0;
	capacity = 0;
}

void SubjectContainer::copyFrom(const SubjectContainer& other) {
	count = other.count;
	capacity = other.capacity;

	subjects = new Subject * [capacity];

	for (int i = 0; i < count; i++) {
		subjects[i] = other.subjects[i]->clone(); //pointer -> !!!!
	}
}

void SubjectContainer::moveFrom(SubjectContainer&& other) {
	subjects = other.subjects;
	count = other.count;
	capacity = other.capacity;

	other.subjects = nullptr;
	other.count = other.capacity = 0;
}

SubjectContainer::SubjectContainer() : count(0), capacity(8) {
	subjects = new Subject * [capacity];
}

SubjectContainer::SubjectContainer(const SubjectContainer& other) {
	copyFrom(other);
}

SubjectContainer::SubjectContainer(SubjectContainer&& other) noexcept {
	moveFrom(std::move(other));
}

SubjectContainer& SubjectContainer::operator=(const SubjectContainer& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

SubjectContainer& SubjectContainer::operator=(SubjectContainer& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

SubjectContainer::~SubjectContainer() {
	free();
}

size_t SubjectContainer::getCount() const {
	return count;
}

Subject* SubjectContainer::getSubject() const {
	if (count == 0) {
		return nullptr;
	}

	Subject* mostCommon = nullptr;
	int maxCount = 0;

	for (int i = 0; i < count; i++) {
		Subject* curr = subjects[i];
		int currCount = 0;

		for (int j = 0; j < count; j++) {
			if (subjects[j] == curr) {
				currCount++;
			}
		}

		if (currCount > maxCount) {
			mostCommon = curr;
			maxCount = currCount;
		}
	}

	return mostCommon;
}

void SubjectContainer::addSubject(SubjectType type) {
	if (count == capacity) {
		resize();
	}

	subjects[count++] = create(type);
}
