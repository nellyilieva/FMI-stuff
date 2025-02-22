#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

int getFileSize(std::ifstream& ifs) {
	int curr = ifs.tellg();
	ifs.seekg(0, std::ios::end);
	int size = ifs.tellg();
	ifs.seekg(curr, std::ios::beg);

	return size;
}

struct Test {
	char ch;
	int a;
};

struct Student {
	char name[30];
	int age;
	int fn;
};


void initStudent(Student& st, const char* _name, int _age, int _fn) {
	strcpy(st.name, _name);
	st.age = _age;
	st.fn = _fn;
}

void writeArrayOfStudentsToFile(std::ofstream& ofs, const Student* students, int size) {
	ofs.write((const char*)students, sizeof(Student) * size);
}

void readArrayOfStudentsFromFile(std::ifstream& ifs, Student*& students, int& size) {
	int fileSize = getFileSize(ifs);
	size = fileSize / sizeof(Student);
	students = new Student[size];	
	ifs.read((char*)students, fileSize);

}

int main() {
	constexpr int SIZE = 5;

	Student* arr = new Student[SIZE];
	initStudent(arr[0], "ivan", 44, 1234);
	initStudent(arr[1], "petur", 12, 765);
	initStudent(arr[2], "alex", 15, 44);
	initStudent(arr[3], "katerina", 19, 12134);
	initStudent(arr[4], "anna", 19, 4546);

	std::ofstream ofs("test.bin", std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		delete[] arr;
		return 0;
	}

	writeArrayOfStudentsToFile(ofs, arr, SIZE);

	delete[] arr;
	ofs.close();

	Student* arr1;
	int count;
	std::ifstream ifs("test.bin", std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	readArrayOfStudentsFromFile(ifs, arr1, count);
	for (int i = 0; i < count; i++) {
		std::cout << "Name: " << arr1[i].name << ", age: " << arr1[i].age << ", fn: " << arr1[i].fn << std::endl;
	}

	delete[] arr1;

	Student s;
	strcpy(s.name, "Ivan");
	s.fn = 12345;
	s.age = 19;

	std::ofstream ofs("test.bin", std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		return 0;
	}

	ofs.write((const char*)&s, sizeof(s));

	ofs.close();

	Student st;

	std::ifstream ifs("test.bin", std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	ifs.read((char*)&st, sizeof(st));

	std::cout << st.name << " " << st.fn << " " << st.age;

	ifs.close();


	Test t = { 'A', 77 };

	std::ofstream ofs("test.bin", std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		return 0;
	}

	ofs.write((const char*)&t, sizeof(t));

	ofs.close();

	Test ts;

	std::ifstream ifs("test.bin", std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	ifs.read((char*)&ts, sizeof(ts));

	std::cout << ts.ch << " " << ts.a;

	ifs.close();

	
	constexpr int SIZE = 5;
	int arr[SIZE] = { 1, 2, 3, 4, 5 };

	std::ofstream ofs("test.bin", std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		return 0;
	}

	ofs.write((const char*)arr, sizeof(int) * SIZE);

	ofs.close();


	std::ifstream ifs("test.bin", std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	int fileSize = getFileSize(ifs);
	const int arrSize = fileSize / sizeof(int);

	int* arr1 = new int[arrSize];

	ifs.read((char*)arr1, fileSize);

	for (int i = 0; i < arrSize; i++) {
		std::cout << arr1[i] << " ";
	}

	delete[] arr1;
	ifs.close();


	int a = 7;

	std::ofstream ofs("test.bin", std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		return 0;
	}

	ofs.write((const char*)&a, sizeof(a));

	ofs.close();

	int n;

	std::ifstream ifs("test.bin", std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	ifs.read((char*)&n, sizeof(n));

	std::cout << n;

	ifs.close();

}
