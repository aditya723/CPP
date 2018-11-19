// Static object destructors
#include <fstream>
#include <iostream>
using namespace std;

class Obj {
        char c; // Identifier
        public:
        Obj(char cc) : c(cc) {
                cout << "Obj::Obj() for " << c << endl;
        }
        ~Obj() {
                cout << "Obj::~Obj() for " << c << endl;
        }
};

Obj a('a'); // Global (static storage)
static Obj c('d'); // Global (static storage)
// Constructor & destructor always called

void f() {
        static Obj b('b'); // constructor and destructors will be called only when f() is called
}

void g() {
        static Obj c('c'); // constructor and destructor will be called only when g() will be called
}

int main() {
        cout << "inside main()" << endl;
        f(); // Calls static constructor for b
        // g() not called
        cout << "leaving main()" << endl;
} ///:~
