#include <iostream>
using namespace std;

class X {
        int i;
        public:
        X() { i = 0; }
        void set(int ii) { i = ii; }
        int read() const { return i; }
        int permute() { return i = i * 47; }
};

// the base class is preceded by public. During inheritance, everything defaults to private. If the base class were not preceded by public, it would mean that all of the public members of the base class would be privatein the derived class.
//class Y : X {
class Y : public X {
        int i; // Different from X's i
        public:
        Y() { i = 0; }
        int change() {
                i = permute(); // Different name call,  The derived class has direct access to all the public base-class functions.
                return i; }
        void set(int ii) { // set function is also present in base class hence this set will overwrite the base class one
                i = ii;
                X::set(ii); // Same-name function call, this is how you call the base class function
        }
};

int main() {
        cout << "sizeof(X) = " << sizeof(X) << endl;
        cout << "sizeof(Y) = "<< sizeof(Y) << endl; // sizeof Y is same as size of X + size of Y
        Y D;
        D.change();
        // X function interface comes through:
        D.read();
        D.permute();
        // Redefined functions hide base versions:
        D.set(12);
} ///:~

