#include <iostream>

namespace ComplexNumbers {
    struct Complex {
        double real;
        double imaginary;
    };

    Complex sum(const Complex& first, const Complex& second) {

        return Complex{ first.real + second.real, first.imaginary + second.imaginary };
    }

    Complex multiply(const Complex& first, const Complex& second) {

        return Complex{ first.real * second.real - first.imaginary * second.imaginary,
                        first.real * second.imaginary + first.imaginary * second.real };
    }

    void printComplex(const Complex& c) {
        std::cout << c.real << " + i." << c.imaginary << "\n";
    }

};


namespace Groups {

    const int MAX_LENGTH = 50;

    enum class Major{ SI, IS, KN, PM, M, INF };

    struct Student {
        double grade;
        int fn;
        char name[MAX_LENGTH + 1];
        Major major;
    };

    struct Group {
        Student* arrS;
        double avgGrade;
        size_t numOfStudents;
    };

    double findSum(const Student* s, size_t numStudents) {
        double sum = 0;

        for (size_t i = 0; i < numStudents; i++) {
            sum += s[i].grade;
        }

        return sum;
    }

    void createGroup(Group& g) {
        for (size_t i = 0; i < g.numOfStudents; i++) {
            std::cin >> g.arrS[i].fn;
            std::cin >> g.arrS[i].name;
            std::cin.ignore();
            std::cin >> g.arrS[i].grade;
        }

        g.avgGrade = findSum(g.arrS, g.numOfStudents) / g.numOfStudents;
    }

    int numToGetScolarship(const Group& g, double minGrade) {
        int counter = 0;

        for (size_t i = 0; i < g.numOfStudents; i++) {
            if (g.arrS[i].grade >= minGrade) {
                counter++;
            }
        }

            return counter;
    }

    Major returnMajor(int m) {
        switch (m) {
        case 0: return Major::SI;
        case 1: return Major::IS;
        case 2: return Major::KN;
        case 3: return Major::PM;
        case 4: return Major::M;
        case 5: return Major::INF;
        }
    }
 
    void printMajor(Major m) {
        switch (m) {
        case Major::SI: std::cout << "SI"; break;
        case Major::IS: std::cout << "IS"; break;
        case Major::KN: std::cout << "KN"; break;
        case Major::PM: std::cout << "PM"; break;
        case Major::M: std::cout << "M"; break;
        case Major::INF: std::cout << "INF"; break;
        default: std::cout << "Unknown"; break;
        }
        std::cout << "\n";
    }

    void printStudent(const Student& s) {
        std::cout << s.fn << " " << s.name << " ";
        printMajor(s.major);
        std::cout << " " << s.grade << "\n";
    }

    void sortGroup(Group& gr, bool (*pred) (const Student& lhs, const Student& rhs)) {
        for (int i = 0; i < gr.numOfStudents - 1; i++) {
            int minInd = i;
            for (int j = i; j < gr.numOfStudents; j++) {
                if (pred(gr.arrS[j], gr.arrS[minInd]))
                    minInd = j;
            }

            if (minInd != i) {
                std::swap(gr.arrS[minInd], gr.arrS[i]);
            }
        }
    }

    void printAllScholarshipsSorted(Group& gr, double minGrade) {
        sortGroup(gr, [](const Student& lhs, const Student& rhs) {return lhs.grade > rhs.grade; });
        for (int i = 0; i < gr.numOfStudents; i++) {
            if (gr.arrS[i].grade < minGrade)
                break;

            printStudent(gr.arrS[i]);
        }
    }
};

int main()
{

    using namespace ComplexNumbers;

    Complex complexOne = { 1, 2 };
    Complex complexTwo = { 3, 4 };

    Complex complexResult = sum(complexOne, complexTwo);

    printComplex(complexResult);



}

