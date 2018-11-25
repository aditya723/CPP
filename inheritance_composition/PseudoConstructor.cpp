#include <iostream>
using namespace std;

class X {
        int i;
        float f;
        char c;
        public:
        X() : i(7), f(1.4), c('x'){cout << "Base class constructor\n";}
};

class Y :public X{
        int i;
        public:
        Y() {cout << "Derived class constructor\n"; }// base class constructor call and y data member initialization will happen before current class constructor call
};

int main() {
        X x;

        Y y;
        int i(100);  // Applied to ordinary definition
        int* ip = new int(47);
} ///:~

