#include <iostream>

const double EPSILON = 0.00001;

struct ThreeVector {
    int x;
    int y;
    int z;
};

ThreeVector addVectors(const ThreeVector& first, const ThreeVector& second) {
    ThreeVector newVector;
    newVector.x = first.x + second.x;
    newVector.y = first.y + second.y;
    newVector.z = first.z + second.z;

    return newVector;
}

void printCoordinates(const ThreeVector& vector) {
    std::cout << vector.x << " " << vector.y << " " << vector.z << "\n";
}

bool areLined(const ThreeVector& first, const ThreeVector& second) {
    double firstProp = double(first.x) / second.x;
    double secondProp = double(first.y) / second.y;
    double thirdProp = double(first.z) / second.z;

    return (abs(firstProp - secondProp)) <= EPSILON && (abs(firstProp - thirdProp)) <= EPSILON && (abs(secondProp - thirdProp)) <= EPSILON;
}


enum class Degree {
    Bachelor,
    Master,
    Doctor
};

struct Teacher {
    unsigned ID;
    Degree degree;
    unsigned failedStudents;
};

bool isValidID(unsigned ID) {
    return 10000 <= ID <= 99999;
}

bool isValidDegree(const char* degree) {
    return strcmp(degree, "Bachelor") == 0 ||
        strcmp(degree, "Master") == 0 ||
        strcmp(degree, "Doctor") == 0;
}

Teacher createTeacher(unsigned ID, const char* degree, unsigned failed) {
    Teacher newTeacher;

    if (isValidID(ID) && isValidDegree(degree)) {
        newTeacher.ID = ID;
        newTeacher.failedStudents = failed;

        if (strcmp(degree, "Bachelor") == 0) {
            newTeacher.degree = Degree::Bachelor;
        }
        else if (strcmp(degree, "Master") == 0) {
            newTeacher.degree = Degree::Master;
        }
        else if (strcmp(degree, "Doctor") == 0) {
            newTeacher.degree = Degree::Doctor;
        }

        return newTeacher;
    }
    else {
        std::cout << "Wrong data" << "\n";
        return { 0, Degree::Bachelor, 0 };
    }
}

const char* degreeToChar(Degree degree) {
    switch (degree){
        case Degree::Bachelor:
            return "Bachelor";
        case Degree::Master:
            return "Master";
        case Degree::Doctor:
            return "Doctor";
    }
}

void printTeacher(Teacher& teacher) {
    std::cout << teacher.ID << " " << degreeToChar(teacher.degree) << " " << teacher.failedStudents << "\n";
}


const int MAX_LENGTH = 50;
const int MAX_BOOKS = 100;

enum class Genre {
    Novel,
    Historical,
    Poetry,
    Other
};

struct Book {
    char title[MAX_LENGTH + 1];
    char author[MAX_LENGTH + 1];
    Genre genre;
    bool availability;
};

struct Libary {
    Book books[MAX_BOOKS];
    int numBooks;
};

Book createBook(const char* title, const char* author, const char* genre, bool availability) {
    Book b;
    strcpy(b.title, title);
    strcpy(b.author, author);

    if (strcmp(genre, "Novel") == 0) {
        b.genre = Genre::Novel;
    }
    else if (strcmp(genre, "Historical") == 0) {
        b.genre = Genre::Historical;
    }
    else if (strcmp(genre, "Poetry") == 0) {
        b.genre = Genre::Poetry;
    }
    if (strcmp(genre, "Other") == 0) {
        b.genre = Genre::Other;
    }

    b.availability = availability;

    return b;
}

void addBookInLibrary(Libary& l, const Book& b) {
    if (l.numBooks < MAX_BOOKS) {
        l.books[l.numBooks++] = b;
    }
    else {
        std::cout << "Not enough space";
    }
}

Book findBookByTitle(Libary& l, const char* title) {
    for (int i = 0; i < l.numBooks; i++) {
        if (strcmp(l.books[i].title, title) == 0) {
            return l.books[i];
        }
    }
}

void returnBookByTitle(Libary& l, const char* title) {
    Book b = findBookByTitle(l, title);
    b.availability = true;
}

void infoAboutBooks(const Libary& l) {
    for (int i = 0; i < l.numBooks; i++) {
        std::cout << "....";
    }
}


struct Student {
    unsigned FN;
    unsigned course;
    double avgGrade;
};

void initStudent(Student& s, unsigned fn, unsigned course, double avgGrade) {
    if (10000 <= fn && fn <= 99999) {
        s.FN = fn;
    }

    if (1 <= course && course <= 4) {
        s.course = course;
    }

    s.avgGrade = avgGrade;
}

void printStudent(const Student& s) {
    std::cout << s.FN << " " << s.course << " " << s.avgGrade << "\n";
}

const int MAX_STUDENTS = 20;

struct Group {
    int numStudents;
    Student S[MAX_STUDENTS];
    double avgGradeGroup;
};

double findSum(const Student* s, int numStudents) {
    double sum = 0;
    for (int i = 0; i < numStudents; i++) {
        sum += s[i].avgGrade;
    }

    return sum;
}

void createGroup(Group& g) {
    for (int i = 0; i < g.numStudents; i++) {
        std::cin >> g.S[i].FN;
        std::cin >> g.S[i].course;
        std::cin >> g.S[i].avgGrade;
    }

    g.avgGradeGroup = findSum(g.S, g.numStudents) / g.numStudents;
}

int numberOfStudentsTakingScholarship(const Group& g, const double minGrade) {
    int counter = 0;

    for (int i = 0; i < g.numStudents; i++) {
        if (g.S[i].avgGrade >= minGrade) {
            counter++;
        }
    }

    return counter;
}

void sortStudentsByGrade(Student* students, const int size) {
    for (int i = 0; i < size - 1; i++) {
        size_t minIndex = i;

        for (int j = i + 1; j < size; j++) {
            if (students[j].avgGrade < students[minIndex].avgGrade) {
                minIndex = j;
            }
        }

        if (minIndex != i) {
            std::swap(students[minIndex], students[i]);
        }
    }

}

void printStudent(const Student& student) {
    std::cout << "Faculty number: " << student.FN <<
        ", Course: " << student.course << std::endl;
}

void sortStudnets(Group& g, const double minGrade) {
    int numberOfStudents = numberOfStudentsTakingScholarship(g, minGrade);
    sortStudentsByGrade(g.S, g.numStudents);

    for (int i = g.numStudents - 1; i >= g.numStudents - numberOfStudents; i--) {
        printStudent(g.S[i]);
    }

}


int main()
{
    ThreeVector first = { 1, 2, 3 };
    ThreeVector second = { 2, 4, 6 };

    ThreeVector third = addVectors(first, second);
    printCoordinates(third);
    std::cout << areLined(first, second);


    Teacher t;
    t = createTeacher(12345, "Master", 2);

    printTeacher(t);

    unsigned id;
    char degreestr[20];
    unsigned failed;

    std::cin >> id;
    std::cin >> degreestr;
    std::cin >> failed;

    Teacher t;
    t = createTeacher(id, degreestr, failed);

    printTeacher(t);

}