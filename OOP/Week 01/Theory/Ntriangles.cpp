#include <iostream>

namespace Points {
	struct Point {
		int x = 0;
		int y = 0;
	};

	void readPoint(Point& point) {
		std::cin >> point.x >> point.y;
	}

	double getDistance(const Point& first, const Point& second) {
		int dx = first.x - second.x;
		int dy = first.y - second.y;

		return sqrt(dx * dx + dy * dy);
	}

	void printPoint(const Point& point) {
		std::cout << "( " << point.x << " " << point.y << ") ";
	}
}

namespace Figures {
	using namespace Points;

	struct Triangle {
		Point p1;
		Point p2;
		Point p3;
	};

	void readTriangle(Triangle& triangle) {
		readPoint(triangle.p1);
		readPoint(triangle.p2);
		readPoint(triangle.p3);
	}

	double getArea(const Triangle& triangle) {
		double sideA = getDistance(triangle.p1, triangle.p2);
		double sideB = getDistance(triangle.p2, triangle.p3);
		double sideC = getDistance(triangle.p1, triangle.p3);

		double hafPer = (sideA + sideB + sideC) / 2;

		return sqrt(hafPer * (hafPer - sideA) * (hafPer - sideB) * (hafPer - sideC));
	}

	void sortByArea(Triangle* triangles, int size) {
		double* areas = new double[size];

		for (int i = 0; i < size; i++) {
			areas[i] = getArea(triangles[i]);
		}

		for (int i = 0; i < size; i++) {
			int minIdx = i;

			for (int j = i + 1; j < size; j++) {
				if (areas[minIdx] > areas[j]) {
					minIdx = j;
				}
			}

			if (minIdx != i) {
				std::swap(triangles[i], triangles[minIdx]);
				std::swap(areas[i], areas[minIdx]);
			}
		}

		delete[] areas;
	}

	void printTrinagle(const Triangle& triangle) {
		printPoint(triangle.p1);
		printPoint(triangle.p2);
		printPoint(triangle.p3);
		std::cout << std::endl;
	}
}


int main() {
	int n;
	std::cin >> n;

	Figures::Triangle* trinagles = new Figures::Triangle[n];

	for (int i = 0; i < n; i++) {
		Figures::readTriangle(trinagles[i]);
	}

	Figures::sortByArea(trinagles, n);

	for (int i = 0; i < n; i++) {
		Figures::printTrinagle(trinagles[i]);
	}

	delete[] trinagles;
	
}