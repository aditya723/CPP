// Inheritance & composition
#include <iostream>
using namespace std;

class A {
        int i;
        public:
        A(int ii) : i(ii) { cout << "Constructor of A" << endl;}
        ~A() { cout << "Destructor of A" << endl;}
        void f() const {}
};

class B {
        int i;
        public:
        B(int ii) : i(ii) { cout << "Constructor of B" << endl;}
        ~B() { cout << "Destructor of B" << endl;}
        void f() const {}
};

class C : public B { // Inheritance
        A a; // Composition
        public:
        /*If we do not specifically call constructor than default constructors will get call automatically by compiler */
        C(int ii) : a(ii), B(ii) { cout << "Constructor of C" << endl;} // constructor call sequence is B->A->C, even though a's constructor is called explicitly before b's.
        ~C() { cout << "Destructor of C" << endl;} // Calls ~A() and ~B()
        /*you never need to make explicit destructor calls because there’s only one destructor for any class, and it doesn’t take any arguments.*/
        void f() const {  // Redefinition
                a.f();
                B::f(); }
};

int main() {
        C c(47);
} ///:~
