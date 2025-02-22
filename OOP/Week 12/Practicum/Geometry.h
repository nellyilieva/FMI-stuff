#pragma once
#include "Subject.h"

class Geometry : public Subject {
public:
	int gradeToPass() override;

	Geometry() = default;

	Subject* clone() const override;


	bool interactWith(const Subject* other) const override;

	bool interactWithDis(const Dis* other) const override;
	bool interactWithOOP(const OOP* other) const override;
	bool interactWithGeometry(const Geometry* other) const override;
};
