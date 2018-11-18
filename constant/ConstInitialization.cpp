// Initializing const in classes
#include <iostream>
using namespace std;

class Fred {
        const int size;
        const static int static_size = 10; //static data member can be initialized this way, as static_size will act as preprocessor constant
        // static int static_size1 = 10; //static data member can not be initialized this way, non-const static data member must be initialized out of line
        public:
        /*
        Thus, when you create an ordinary (non-static) const inside a class, you cannot give it an initial value. This initialization must occur in the constructor, of course, but in a special place in the constructor. Because a const must be initialized at the point it is created, inside the main body of the constructor the const must already be initialized. Otherwise you’re left with the choice of waiting until some point later in the constructor body, which means the const would be un-initialized for a while. Also, there would be nothing to keep you from changing the value of the const at various places in the constructor body.
        */
        Fred(int sz);
        void print();
};

Fred::Fred(int sz) : size(sz) {}

void Fred::print() { cout << size << " " << static_size << endl; }

int main() {
        Fred a(1), b(2), c(3);
        a.print(), b.print(), c.print();
} ///:~
