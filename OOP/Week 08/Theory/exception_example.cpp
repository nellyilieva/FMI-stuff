#include <iostream>
#include <cstring>
#pragma warning (disable: 4996)

class X {
public:
    X() {
        std::cout << "X()" << std::endl;
    }

    ~X() {
        std::cout << "~X()" << std::endl;
    }
};

class A {
public:
    A() {
        std::cout << "A()" << std::endl;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }
};

class B {
public:
    B() {
        std::cout << "B()" << std::endl;
    }

    ~B() {
        std::cout << "~B()" << std::endl;
    }
};

class C {
public:
    C() {
        std::cout << "C()" << std::endl;
    }

    ~C() {
        std::cout << "~C()" << std::endl;
    }
};


void g() {
    X x;
    throw std::runtime_error("Throw random exception");
}

void f() {
    A obj1;
    B obj2;
    g();
    C obj3;
}



int main() {
    try {
        f(); // ~X() ~B() ~A()
    }
    catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }
    catch (...) {

    }
}