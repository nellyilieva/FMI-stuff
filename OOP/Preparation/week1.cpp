#include <iostream>
#include <fstream>
#include "week1.h"
#pragma warning (disable:4996)

Rational::Rational() { 
    nom = 0;
    denom = 1;
}

Rational::Rational(int newNom, int newDenom) {
    nom = newNom;
    denom = newDenom;
}

int Rational::getNom() const {
    return nom;
}

int Rational::getDenom() const {
    return denom;
}

void Rational::setNom(int newNom) {
    nom = newNom;
}

void Rational::setDenom(int newDenom) {
    if (isValidDenom(newDenom)) {
        denom = newDenom;
    }
}

void Rational::rationalize() {
    unsigned gcd = getGcd(nom, denom);
    
    nom /= gcd;
    denom /= gcd;

    if (nom < 0 && denom < 0 || nom > 0 && denom < 0) {
        nom *= -1;
        denom *= -1;
    }
}

Rational& Rational::operator+=(const Rational& other) {
    nom *= other.denom;
    nom += denom * other.nom;

    denom *= other.denom;

    rationalize();

    return *this;
}

Rational& Rational::operator-=(const Rational& other) {
    nom *= other.denom;
    nom -= denom * other.nom;

    denom *= other.denom;

    rationalize();

    return *this;
}

Rational& Rational::operator*=(const Rational& other) {
    nom *= other.nom;
    denom *= other.denom;

    rationalize();

    return *this;
}

Rational& Rational::operator/=(const Rational& other) {
    nom *= other.denom;
    denom *= other.nom;

    rationalize();

    return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);

    result += rhs;

    return result;

}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);

    result -= rhs;

    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);

    result *= rhs;

    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);

    result /= rhs;

    return result;
}

std::ostream& operator<<(std::ostream& os, const Rational& rat) {
    return os << rat.nom << "/" << rat.denom;
}

std::istream& operator>>(std::istream& is, Rational& rat) {
    return is >> rat.nom >> rat.denom;
}

bool operator==(const Rational& lhs, const Rational& rhs) {

    //we make copy in order to use the rationalize function

    /*Rational lhsRat = lhs;
    Rational rhsRat = rhs;

    lhsRat.rationalize();
    rhsRat.rationalize();

    return lhsRat.getNom() == rhsRat.getNom() && lhsRat.getDenom() == rhsRat.getDenom();*/

    return lhs.getNom() == rhs.getNom() && lhs.getDenom() == rhs.getDenom();
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

bool isValidDenom(int denom) {
    return denom != 0;
}

unsigned getGcd(unsigned a, unsigned b) {
    if (a < b) {
        std::swap(a, b);
    }

    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }

    return a;
}


const int MAX_NAME = 100;
const int MAX_SIZE = 30;

enum class Major {
    Undefined,
    Inf,
    Cs,
    Se,
    Si
};

struct Student {
    char name[MAX_NAME + 1] = "";
    unsigned fn = 0;
    int age = 0;
    Major major;
};

const char* getMajor(Major m) {
    switch (m) {
    case Major::Inf: return "inf";
    case Major::Cs: return "cs";
    case Major::Se: return "se";
    case Major::Si: return "si";

    }
    return "";
}

bool isLower(char ch) {
    return 'a' <= ch && ch <= 'z';
}

bool areAllLower(const char* str) {
    if (str == nullptr) {
        return false;
    }

    while (*str) {
        if (!isLower(*str)) {
            return false;
        }
        str++;
    }
    return true;
}

bool isNameValid(const char* name) {
    if (name == nullptr) {
        return false;
    }

    size_t nameSize = strlen(name);

    if (nameSize == 0 || nameSize > MAX_NAME) {
        return false;
    }

    return !isLower(*name) && areAllLower(name + 1);
}

void initStudent(Student& s, const char* name, unsigned fn, int age, Major major) {
    if (isNameValid(name)) {
        strcpy(s.name, name);
    }
    else {
        strcpy(s.name, "unknown");
    }

    s.fn = fn;
    s.age = age;
    s.major = major;
}

struct DataBase {
    unsigned count = 0;
    Student arrStudent[MAX_SIZE];
};

void serializeStudentTxt(std::ostream& os, const Student& st) {
    os << st.name << '/n' << st.age << '/n' << st.fn << '/n' << (int)st.major;
}

void serializeDataBaseTxt(std::ostream& os, const DataBase& db) {
    os << db.count << '/n';
    for (int i = 0; i < db.count; i++) {
        serializeStudentTxt(os, db.arrStudent[i]);
    }
}

void deserializeStudentTxt(std::istream& is, Student& st) {
    is.getline(st.name, 100);
    is >> st.age >> st.fn;
    int tempMajor;
    is >> tempMajor;
    st.major = (Major)tempMajor;
}

void deserializeDataBaseTxt(std::istream& is, DataBase& db) {
    is >> db.count;

    for (int i = 0; i < db.count; i++) {
        deserializeStudentTxt(is, db.arrStudent[i]);
    }
}

void writeToTxt(const char* fileName, const Student& st, const DataBase db) {
    //we have st or db

    std::ofstream ofs(fileName);

    if (!ofs.is_open()) {
        return;
    }

    serializeStudentTxt(ofs, st);
    serializeDataBaseTxt(ofs, db);

    ofs.close();
}


void readFromTxt(const char* fileName, Student& st, DataBase db) {
    //we create st or db

    std::ifstream ifs(fileName);

    if (!ifs.is_open()) {
        return;
    }

    deserializeStudentTxt(ifs, st);
    deserializeDataBaseTxt(ifs, db);

    ifs.close();
}


void serializeStudentBin(std::ostream& os, const Student& st) {
    os.write((const char*)&st, sizeof(Student));
}

void serializeDataBaseBin(std::ostream& os, const DataBase& db) {
    os.write((const char*)&db.count, sizeof(int));
    os.write((const char*)db.arrStudent, db.count * sizeof(Student));
    //count in the parameters?
}

void deserializeStudentBin(std::istream& is, Student& st) {
    is.read((char*)&st, sizeof(Student));
}

void deserializeDataBaseBin(std::istream& is, DataBase& db) {
    is.read((char*)&db.count, sizeof(int));
    is.read((char*)db.arrStudent, db.count * sizeof(Student));

    //if we do not have the size we find the size of file
    //we do not have special struct for the DataBase

    /*void readFromFile(Student * &ptr, size_t & studentsCount, ifstream & f)
    {
        size_t sizeOfFile = getFileSize(f);
        studentsCount = sizeOfFile / sizeof(Student);
        ptr = new Student[studentsCount];
        f.read((char*)ptr, sizeOfFile);
    }*/
}

void writeToBin(const char* fileName, const Student& st, const DataBase& db) {
    //we have st or db

    std::ofstream ofs(fileName, std::ios::binary);

    if (!ofs.is_open()) {
        return;
    }

    serializeStudentBin(ofs, st);
    serializeDataBaseBin(ofs, db);

    ofs.close();


    // in main()
    //constexpr size_t size = 4;
    //Student* arr = new Student[size];
    //initStudent(arr[0], "ivan", 44, 1234);
    //initStudent(arr[1], "petur", 12, 765);
    //initStudent(arr[2], "alex", 15, 44);
    //initStudent(arr[3], "katerina", 19, 12134);

    //ofstream file("students.dat", ios::binary);

    //if (!file.is_open())
    //{
    //    std::cout << "Error while opening the file!" << std::endl;
    //    delete[] arr; //!
    //    return -1;
    //}

    //saveToFile(arr, size, file);

    //delete[] arr;
}


void readFromBin(const char* fileName, Student& st, DataBase& db) {
    //we create st or db

    std::ifstream ifs(fileName);

    if (!ifs.is_open()) {
        return;
    }

    deserializeStudentBin(ifs, st);
    deserializeDataBaseBin(ifs, db);

    ifs.close();


    //in main()
    /* Student* arr;
    size_t count;
    ifstream file("students.dat");

    if (!file.is_open())
    {
        std::cout << "Error while opening the file!" << std::endl;
        return -1;
    }

    readFromFile(arr, count, file);

    for (int i = 0; i < count; i++)
        std::cout << "Name: " << arr[i].name << ", age: " << arr[i].age << ", fn: " << arr[i].fn << std::endl;

    delete[] arr;*/
}

//void sort(bool (*compare)(const Song& first, const Song& second)) {
//    for (int i = 0; i < countSongs; i++) {
//        int minIdx = i;
//
//        for (int j = i + 1; j < countSongs; j++) {
//            if (compare(songsArr[j], songsArr[minIdx])) {
//                minIdx = j;
//            }
//        }
//
//        if (i != minIdx) {
//            std::swap(songsArr[i], songsArr[minIdx]);
//        }
//    }
//}
//
//void sortByDuration() {
//    sort([](const Song& first, const Song& second) {return first.getDuration().getSecondsFromMidnight() < second.getDuration().getSecondsFromMidnight(); });
//}
//
//void sortByName() {
//    sort([](const Song& first, const Song& second) {return strcmp(first.getName(), second.getName()) < 0; });
//}



int main()
{

}