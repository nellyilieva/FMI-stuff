#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#pragma warning (disable: 4996)

//we have abstract class Shape in which we have (protected) stuct Point (def const, const with param, getDistance method)
//arr of ppoints to construct the shape
//Big 6 for Shape and constructor with count !! virtual destructor !!
//setPoints
//to show polymorphism -> pure virtual functions for area, perimetar, isPointIn

class Shape {
protected:
	struct Point {
		int x = 0;
		int y = 0;

		Point();
		Point(int x, int y);

		double getDistance(const Point& other) const;
	};

	const Point& getPointAtIndex(size_t idx) const;

private:
	//we have array of points and for every shape we save how many points we will use (0, 4, 3)
	Point* points;
	size_t count;

	void copyFrom(const Shape& other);
	void moveFrom(Shape&& other);
	void free();

public:
	Shape(size_t count);

	Shape(const Shape& other);
	Shape& operator=(const Shape& other);

	Shape(Shape&& other) noexcept;
	Shape& operator=(Shape&& other) noexcept;

	virtual ~Shape();

	void setPoints(size_t pointIdx, int x, int y);

	virtual double getArea() const = 0;
	virtual double getPerimeter() const = 0;
	virtual bool isPointIn(int x, int y) const = 0;

};

//we create circle(with radius), triangle, rectangle


//constructor and virtual functions
class Circle : public Shape {
private:
	double radius;

public:
	Circle(int x, int y, double radius);

	double getArea() const override;
	double getPerimeter() const override;
	bool isPointIn(int x, int y) const override;
};

class Rectangle : public Shape {
public:
	Rectangle(int x1, int y1, int x3, int y3);
	double getArea() const override;
	double getPerimeter() const override;
	bool isPointIn(int x, int y) const override;
};

class Triangle : public Shape {
public:
	Triangle(int x1, int y1, int x2, int y2, int x3, int y3);
	double getArea() const override;
	double getPerimeter() const override;
	bool isPointIn(int x, int y) const override;
};