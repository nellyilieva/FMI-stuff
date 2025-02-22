#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

struct Student {
	char* name;
	int age;
	int fn;
};

Student init(const char* name, int age, int fn) {
	Student st;
	st.name = new char[strlen(name) + 1];
	strcpy(st.name, name);
	st.age = age;
	st.fn = fn;

	return st;
}

void freeStudent(Student& st) {
	delete[] st.name;
	st.age = st.fn = 0;
}

void writeStudentToBinary(std::ofstream& ofs, const Student& st) {
	int nameSize = strlen(st.name);

	ofs.write((const char*)&nameSize, sizeof(int));
	ofs.write(st.name, nameSize + 1);

	ofs.write((const char*)&st.age, sizeof(int));
	ofs.write((const char*)&st.fn, sizeof(int));
}

void readStudentFromBinary(std::ifstream& ifs, Student& st) {
	int nameSize;
	ifs.read((char*)&nameSize, sizeof(int));
	st.name = new char[nameSize + 1];
	ifs.read(st.name, nameSize + 1);

	ifs.read((char*)&st.age, sizeof(int));
	ifs.read((char*)&st.fn, sizeof(int));
}

void writeArrayOfStudentsToBinary(std::ofstream& ofs, const Student* students, int size) {
	ofs.write((const char*)&size, sizeof(size));

	for (int i = 0; i < size; i++) {
		writeStudentToBinary(ofs, students[i]);
	}
}

void readArrayOfStudentsFromBinary(std::ifstream& ifs, Student*& students, int& size) {
	ifs.read((char*)&size, sizeof(size));

	students = new Student[size];

	for (int i = 0; i < size; i++) {
		readStudentFromBinary(ifs, students[i]);
	}
}

int main() {
	
	std::ofstream ofs("test.bin", std::ios::out | std::ios::binary);

	if (!ofs.is_open()) {
		return 0;
	}

	Student arr[3];

	arr[0] = init("Ivan", 10, 20);
	arr[1] = init("Peter", 41, 44);
	arr[2] = init("Nikolay", 99, 0);

	writeArrayOfStudentsToBinary(ofs, arr, 3);

	freeStudent(arr[0]);
	freeStudent(arr[1]);
	freeStudent(arr[2]);

	ofs.close();

	std::ifstream ifs("test.bin", std::ios::in | std::ios::binary);

	if (!ifs.is_open()) {
		return 0;
	}

	Student* arr1;
	int size;

	readArrayOfStudentsFromBinary(ifs, arr1, size);

	for (int i = 0; i < size; i++) {
		std::cout << arr1[i].name << " " << arr1[i].age << " " << arr1[i].fn << std::endl;
	}

	for (int i = 0; i < size; i++) {
		freeStudent(arr1[i]);
	}

	ifs.close();
}