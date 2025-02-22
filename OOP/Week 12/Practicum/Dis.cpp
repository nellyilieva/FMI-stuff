#include "Dis.h"

int Dis::gradeToPass() {
	return (getScore() * 0.7);
}

Subject* Dis::clone() const {
	return new Dis(*this);
}

bool Dis::interactWith(const Subject* other) const {
	return other->interactWithDis(this);
}

bool Dis::interactWithDis(const Dis* other) const {
	//sth
}
bool Dis::interactWithOOP(const OOP* other) const {
	//sth
}

bool Dis::interactWithGeometry(const Geometry* other) const {
	//sth
}