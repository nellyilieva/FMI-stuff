#include "GradeReport.h"
#pragma once
#pragma warning(disable : 4996)


void GradeReport::copyFrom(const GradeReport& other) {
    grades = new int[other.gradesCount];
    for (int i = 0; i < other.gradesCount; i++)
        grades[i] = other.grades[i];
    gradesCount = other.gradesCount;

    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

void GradeReport::free() {
    delete[] grades;
    delete[] name;
}

GradeReport::GradeReport() {
    grades = nullptr;
    gradesCount = 0;
    name = nullptr;
}

GradeReport::GradeReport(const int* grades, unsigned gradesCount, const char* name) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);

    this->gradesCount = gradesCount;
    this->grades = new int[gradesCount];
    for (int i = 0; i < gradesCount; i++)
        this->grades[i] = grades[i];
}

GradeReport::~GradeReport() {
    free();
}

GradeReport::GradeReport(const GradeReport& other) {
    copyFrom(other);
}

GradeReport& GradeReport::operator=(const GradeReport& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

int GradeReport::countGrades() const {
    return gradesCount;
}

void GradeReport::printName() const {
    std::cout << name << std::endl;
}

int main()
{
    int grades[] = { 2, 4, 7 };
    GradeReport report(grades, 3, "Ivan");
    report.printName();

}
