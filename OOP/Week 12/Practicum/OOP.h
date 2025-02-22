#pragma once
#include "Subject.h"

class OOP : public Subject {
private:
	int bonus = 0;
public:
	int gradeToPass() override;

	OOP() = default;
	OOP(int _bonus);

	int getBonus() const;

	Subject* clone() const override;


	bool interactWith(const Subject* other) const override;

	bool interactWithDis(const Dis* other) const override;
	bool interactWithOOP(const OOP* other) const override;
	bool interactWithGeometry(const Geometry* other) const override;
};