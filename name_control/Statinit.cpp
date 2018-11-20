// Scope of static initializer
#include <iostream>
using namespace std;

int x = 100;

class WithStatic {
        static int x;
        static int y;
        public:
        void print() const {
                cout << "WithStatic::x = " << x << endl;
                cout << "WithStatic::y = " << y << endl;
        }
};

int WithStatic::x = 1; // Even though x is private, it can be initialized this way

int WithStatic::y = x + 1; // this x belongs to class Withstatic not with global x.
// WithStatic::x NOT ::x
int main() {
        WithStatic ws;
        ws.print();

        cout << "x = " << x << endl;
} ///:~
