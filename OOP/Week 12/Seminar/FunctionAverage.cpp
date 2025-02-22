#include "OOP_second.h"

class NumberInFile {
private:
	int* data = nullptr;
	size_t size = 0;
	bool loaded = false;

	static unsigned getFileSize(std::ifstream& ifs) {
		size_t currPos = ifs.tellg();
		ifs.seekg(0, std::ios::end);
		size_t size = ifs.tellg();
		ifs.seekg(currPos, std::ios::beg);

		return size;
	}

	void deserialize(const char* fileName) {
		std::ifstream ifs(fileName, std::ios::binary);

		if (!ifs.is_open()) {
			return;
		}

		size = getFileSize(ifs) / sizeof(int);
		data = new int[size];
		ifs.read((char*)data, sizeof(int) * size);
		loaded = true;
	}

	void copyFrom(const NumberInFile& other) {
		size = other.size;
		data = new int[size];

		for (int i = 0; i < size; i++) {
			data[i] = other.data[i];
		}
	}

	void free() {
		delete[] data;
	}

public:
	NumberInFile(const char* filePath) {
		deserialize(filePath);
	}

	NumberInFile(const NumberInFile& other) {
		copyFrom(other);
	}

	NumberInFile& operator=(const NumberInFile& other) {
		if (this != &other) {
			free();
			copyFrom(other);
		}
		return *this;
	}

	~NumberInFile() {
		free();
	}

	int operator()(int x) const {   //check if number exist in file; we overload operator() => this class behaves like function which takes int
		for (int i = 0; i < size; i++) {
			if (x == data[i]) {
				return x;
			}
		}

		return 0;
	}

	bool good() const {
		return loaded;
	}
};


int main() {
	char filePath[1024]{};
	std::cin.getline(filePath, 1024);

	NumberInFile func(filePath);  //we use operator() to act like function

	if (func.good()) {
		std::cout << "Loaded!" << std::endl;
	}

	else {
		std::cout << "Invalid file path";
		return 1;
	}

	//int (*)(int) -> function pointer of type int that takes int

	FunctionsAverage<NumberInFile, int (*)(int)> f(func, [](int x) -> int { return x; });  //create instance of the class

	while (true) {
		int num;
		std::cin >> num;
		std::cout << "Average: " << f.average(num) << std::endl;  //it calls func(num) (acts like function) and the lambda with num
	}
}