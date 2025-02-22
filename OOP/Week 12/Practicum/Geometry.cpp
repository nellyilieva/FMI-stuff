#include "Geometry.h"

int Geometry::gradeToPass() {
	return (getScore() * 0.75);
}

Subject* Geometry::clone() const {
	return new Geometry(*this);
}

bool Geometry::interactWith(const Subject* other) const {
	return other->interactWithGeometry(this);
}

bool Geometry::interactWithDis(const Dis* other) const {
	//sth
}
bool Geometry::interactWithOOP(const OOP* other) const {
	//sth
}

bool Geometry::interactWithGeometry(const Geometry* other) const {
	//sth
}
