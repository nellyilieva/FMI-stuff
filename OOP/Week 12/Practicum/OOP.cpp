#include "OOP.h"

OOP::OOP(int _bonus) : Subject(), bonus(_bonus) {}

int OOP::getBonus() const {
	return bonus;
}

int OOP::gradeToPass() {
	return (getScore() * 0.8 + getBonus());
}

Subject* OOP::clone() const {
	return new OOP(*this);
}


bool OOP::interactWith(const Subject* other) const {
	return other->interactWithOOP(this);
}

bool OOP::interactWithDis(const Dis* other) const {
	//sth
}
bool OOP::interactWithOOP(const OOP* other) const {
	//sth
}

bool OOP::interactWithGeometry(const Geometry* other) const {
	//sth
}