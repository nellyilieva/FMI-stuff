#include<iostream>
#include<fstream>


void printSumFromFile(const char* fileName) {
    std::ifstream file("test.txt");

    if (!file.is_open()) {
        std::cout << "The file could not open!" << std::endl;
        return;
    }

    int a;
    int sum = 0;

    while (!file.eof()) {
        file >> a;
        sum += a;
    }

    std::cout << sum;

    file.close();
}

unsigned findMaxNumFromFile(const char* file) {
    std::ifstream myFile("test.txt");

    if (!myFile.is_open()) {
        std::cout << "The file could not open!" << std::endl;
        return 0;
    }

    unsigned int a;
    unsigned int maxNum = 0;

    while (!myFile.eof()) {
        myFile >> a;
        if (a > maxNum) {
            maxNum = a;
        }
    }

    return maxNum;

    myFile.close();
  
}


unsigned getCharCountFromFile(std::ifstream& ifs, char ch) {
    
    if (!ifs.is_open())
        return 0;

    unsigned int count = 0;

    while (true)
    {
        char current = ifs.get();
        if (ifs.eof())
            break;

        if (current == ch)
            count++;
    }

    return count;
}

unsigned getLinesCount(const char* fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "The file could not open!" << std::endl;
        return 0;
    }
    
    return getCharCountFromFile(file, '\n') + 1;

    file.close();
}



const int MAX_PAIRS = 25;

struct Pair {
    unsigned int a;
    unsigned int b;
};

struct Relation {
    Pair pairs[MAX_PAIRS];
    int currSize;
};

void initPair(Pair& p, unsigned int a, unsigned int b) {
    p = Pair{ a, b };
}

void createPair(Pair& p) {
    unsigned int a;
    unsigned int b;

    std::cin >> a;
    std::cin >> b;

    initPair(p, a, b);

}

void printPair(const Pair& p) {
    std::cout << p.a << " " << p.b << "\n";
}

void readPairFromFile(std::ifstream& ifs, Pair& p) {
    int a, b;
    ifs >> a >> b;
    initPair(p, a, b);
}

void writePairToFile(std::ofstream& ofs, const Pair& p) {
    ofs << p.a << " " << p.b << "\n";
}

void readRelationFromFile(const char* fileName, Relation& r) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "The file could not open!" << std::endl;
        return;
    }

    for (int i = 0; i < MAX_PAIRS && !file.eof(); i++) {
        readPairFromFile(file, r.pairs[i]);
        r.currSize++;
    }

    file.close();
}

void writeRelationToFile(const char* fileName, const Relation& r) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        std::cout << "The file could not open!" << std::endl;
        return;
    }

    for (int i = 0; i < r.currSize; i++) {
        writePairToFile(file, r.pairs[i]);
    }

    file.close();
}

void addPairToRelation(Relation& r, const char* fileName) {
    Pair p;

    createPair(p);

    if (r.currSize >= MAX_PAIRS) {
        std::cout << "not enough space";
        return;
    }
    else {
        r.pairs[r.currSize] = p;
        r.currSize++;
    }

    writeRelationToFile(fileName, r);
}


int main() {

}