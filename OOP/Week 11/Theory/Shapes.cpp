#include "Shapes.h"

Shape::Point::Point() {}

Shape::Point::Point(int x, int y) : x(x), y(y) {}

double Shape::Point::getDistance(const Point& other) const {
	int dx = x - other.x;
	int dy = y - other.y;

	return sqrt(dx * dx + dy * dy);
}

const Shape::Point& Shape::getPointAtIndex(size_t idx) const {
	if (idx >= count) {
		throw std::out_of_range("Invalid point index");
	}

	return points[idx];
}

void Shape::copyFrom(const Shape& other) {
	points = new Point[other.count];

	for (int i = 0; i < other.count; i++) {
		points[i] = other.points[i];
	}

	count = other.count;
}

void Shape::moveFrom(Shape&& other) {
	points = other.points;
	count = other.count;

	other.points = nullptr;
	other.count = 0;
}

void Shape::free() {
	delete[] points;
	count = 0;
}

Shape::Shape(size_t count): count(count) {
	points = new Point[count]{};
}

Shape::Shape(const Shape& other) {
	copyFrom(other);
}

Shape& Shape::operator=(const Shape& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

Shape::Shape(Shape&& other) noexcept {
	moveFrom(std::move(other));
}

Shape& Shape::operator=(Shape&& other) noexcept {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}

	return *this;
}

Shape::~Shape() {
	free();
}

void Shape::setPoints(size_t pointIdx, int x, int y) {
	if (pointIdx >= count) {
		throw std::out_of_range("Invalid point index");
	}

	points[pointIdx].x = x;
	points[pointIdx].y = y;
}

//we use the constructor with count for Shape and then set the points!
Circle::Circle(int x, int y, double radius) : Shape(1), radius(radius) {
	setPoints(0, x, y);
}

double Circle::getArea() const {
	return 3.1415 * radius * radius;
}

double Circle::getPerimeter() const {
	return 2 * 3.1415 * radius;
}

//construct the point with point constructor
//return p.getDistance(getPointAtIndex(0)) <= radius; -> at index 0 is our Shape (index in the array)
bool Circle::isPointIn(int x, int y) const {
	Shape::Point p(x, y);
	return p.getDistance(getPointAtIndex(0)) <= radius;
}


Rectangle::Rectangle(int x1, int y1, int x3, int y3) : Shape(4) {
	setPoints(0, x1, y1);
	setPoints(1, x1, y3);
	setPoints(2, x3, y3);
	setPoints(3, x3, y1);
}

double Rectangle::getArea() const {
	const Shape::Point& p0 = getPointAtIndex(0);
	const Shape::Point& p1 = getPointAtIndex(1);
	const Shape::Point& p2 = getPointAtIndex(2);

	return p0.getDistance(p1) * p1.getDistance(p2);

}

double Rectangle::getPerimeter() const {
	const Shape::Point& p0 = getPointAtIndex(0);
	const Shape::Point& p1 = getPointAtIndex(1);
	const Shape::Point& p2 = getPointAtIndex(2);

	return 2 * (p0.getDistance(p1) + p1.getDistance(p2));
}

bool Rectangle::isPointIn(int x, int y) const {
	Shape::Point p(x, y);
	return p.x >= getPointAtIndex(0).x && p.x <= getPointAtIndex(2).x &&
		p.y >= getPointAtIndex(0).y && p.y <= getPointAtIndex(2).y;
}

Triangle::Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : Shape(3) {
	setPoints(0, x1, y1);
	setPoints(1, x2, y2);
	setPoints(2, x3, y3);
}

double Triangle::getArea() const {
	const Shape::Point& p0 = getPointAtIndex(0);
	const Shape::Point& p1 = getPointAtIndex(1);
	const Shape::Point& p2 = getPointAtIndex(2);

	return abs(p0.x * p1.y + p1.x * p2.y + p2.x * p0.y - p0.y * p1.x - p1.y * p2.x - p2.y * p0.x) / 2.00;
}

double Triangle::getPerimeter() const {
	const Shape::Point& p0 = getPointAtIndex(0);
	const Shape::Point& p1 = getPointAtIndex(1);
	const Shape::Point& p2 = getPointAtIndex(2);

	return p0.getDistance(p1) + p1.getDistance(p2) + p2.getDistance(p0);
}

bool Triangle::isPointIn(int x, int y) const {
	Shape::Point p(x, y);
	Triangle t1(getPointAtIndex(0).x, getPointAtIndex(0).y, getPointAtIndex(1).x, getPointAtIndex(1).y, p.x, p.y);
	Triangle t2(getPointAtIndex(2).x, getPointAtIndex(2).y, getPointAtIndex(1).x, getPointAtIndex(1).y, p.x, p.y);
	Triangle t3(getPointAtIndex(2).x, getPointAtIndex(2).y, getPointAtIndex(0).x, getPointAtIndex(0).y, p.x, p.y);

	return abs(t1.getArea() + t2.getArea() + t3.getArea() - getArea()) <= std::numeric_limits<double>::epsilon();
}


//we create array of shapes, we don't know what are the shapes
//for this functions we need type that has the used methods; this type is Shape
//because the functions are virtual, they do dynamic binding to choose which implementations of them to call (with vtable)
void printAreas(const Shape* const* shapes, size_t shapesCount)
{
	for (int i = 0; i < shapesCount; i++)
		std::cout << shapes[i]->getArea() << std::endl;
}
void printPers(const Shape* const* shapes, size_t shapesCount)
{
	for (int i = 0; i < shapesCount; i++)
		std::cout << shapes[i]->getPerimeter() << std::endl;
}

void checkPointIn(const Shape* const* shapes, size_t shapesCount, int x, int y)
{
	for (int i = 0; i < shapesCount; i++)
		std::cout << shapes[i]->isPointIn(x, y) << std::endl;
}

void freeCollection(Shape** shapes, size_t shapesCount)
{
	for (int i = 0; i < shapesCount; i++)
		delete shapes[i];
	delete[] shapes;
}

int main() {
	
	Shape** arr = new Shape * [4];

	/// <summary>
	/// 
	// FACTORY
	arr[0] = new Rectangle(3, 4, 6, 8);
	arr[1] = new Circle(3, 3, 4);
	arr[2] = new Circle(1, 4, 5);
	arr[3] = new Triangle(1, 1, 2, 2, 3, 3);
	/// <summary>
	/// //
	/// 
	/// </summary>
	/// <returns></returns>
	/// 
	/// 
	/// 
	/// 
	printAreas(arr, 4);
	std::cout << std::endl;
	printPers(arr, 4);
	std::cout << std::endl;

	checkPointIn(arr, 4, 3, 3);


	freeCollection(arr, 4);
}