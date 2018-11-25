// Virtual functions restrict overloading
#include <iostream>
#include <string>
using namespace std;

class Base {
        public:
                virtual int f() const {
                        cout << "Base::f()\n";
                        return 1;
                }
                virtual void f(string) const {}
                virtual void g() const {}
};

class Derived1 : public Base {
        public:
                void g() const {}
};

class Derived2 : public Base {
        public:
                // Overriding a virtual function:
                int f() const {
                        cout << "Derived2::f()\n";
                        return 2; }
};

class Derived3 : public Base {
        public:
                // Cannot change return type: only allowed when f() is non virtual
                //! void f() const{ cout << "Derived3::f()\n";} 
};
class Derived4 : public Base {
        public:
                // Change argument list:
                int f(int) const {
                        cout << "Derived4::f()\n";
                        return 4; }
};

int main() {
        string s("hello");
        Derived1 d1;
        int x = d1.f();

        d1.f(s);

        Derived2 d2;
        x = d2.f();

        //!  d2.f(s); // string version hidden. Because you have override f() hence all overloaded version of base class are hidden.

        Derived4 d4;
        x = d4.f(1);

        //!  x = d4.f(); // f() version hidden
        //!  d4.f(s); // string version hidden

        Base& br = d4; // Upcast
        //!  br.f(1); // Derived version unavailable

        br.f(); // Base version available

        br.f(s); // Base version abailable
} ///:~
