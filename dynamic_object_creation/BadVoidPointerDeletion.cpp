// Deleting void pointers can cause memory leaks
#include <iostream>
using namespace std;

class Object {
        void* data; // Some storage
        const int size;
        const char id;
        public:
        Object(int sz, char c) : size(sz), id(c) {
                data = new char[size];
                cout << "Constructing object " << id
                        << ", size = " << size << endl;
        }
        ~Object() {
                cout << "Destructing object " << id << endl;
                delete []data; // OK, just releases storage,
                // no destructor calls are necessary
        }
};

int main() {
        cout << "\nCreating and deleting a pointer of Object type" << endl;
        Object* a = new Object(40, 'a');
        delete a;

        cout << "\nCreating and deleting a pointer of void type" << endl;
        void* b = new Object(40, 'b');
        /*If you delete a void pointer, the only thing that happens is the memory gets released, because there’s no type information and no way for the compiler to know what destructor to call.*/
        delete b;
} ///:~
