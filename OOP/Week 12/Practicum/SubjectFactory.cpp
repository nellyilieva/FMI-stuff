#include "SubjectFactory.h"
#include "Dis.h"
#include "OOP.h"
#include "Geometry.h"

Subject* create(SubjectType type) {
	switch (type) {
	case SubjectType::Dis: return new Dis();
		break;
	case SubjectType::OOP: return new OOP();
		break;
	case SubjectType::Geometry: return new Geometry();
		break;
	}

	throw std::invalid_argument("Invalid animal type");
}