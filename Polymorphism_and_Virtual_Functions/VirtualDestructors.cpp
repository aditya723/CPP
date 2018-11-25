// Behavior of virtual vs. non-virtual destructor 
#include <iostream>
using namespace std;

class Base1 {
        public:
                ~Base1() { cout << "~Base1()\n"; }
};

class Derived1 : public Base1 {
        public:
                ~Derived1() { cout << "~Derived1()\n"; }
};

class Base2 {
        public:
                virtual ~Base2() { cout << "~Base2()\n"; }
};

class Derived2 : public Base2 {
        public:
                ~Derived2() { cout << "~Derived2()\n"; }
};

int main() {
        Base1* bp = new Derived1; // Upcast
        delete bp; // only base class destructor will be called

        cout << "\n\n";
        Derived1 *dp = new Derived1;
        delete dp; // both base and derived class constructor will be called


        cout << "\n\n";
        Base2* b2p = new Derived2; // Upcast
        delete b2p; // both base and derived class constructor will be called
} ///:~
