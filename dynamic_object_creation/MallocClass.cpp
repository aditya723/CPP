// Malloc with class objects
// What you'd have to do if not for "new"
#include <cstdlib> // malloc() & free()
#include <cstring> // memset()
#include <iostream>
using namespace std;
class Obj {
        int i, j, k;
        enum { sz = 100 };
        char buf[sz];
        public:
        void initialize() { // Can't use constructor to initialize as constructors can not be called directly using object, same applies for destructors.
                cout << "initializing Obj" << endl;
                i = j = k = 0;
                memset(buf, 0, sz);
        }
        void destroy() const { // Can't use destructor
                cout << "destroying Obj" << endl;
        } };
int main() {
        Obj* obj = (Obj*)malloc(sizeof(Obj));
        obj->initialize();
        // ... sometime later:
        obj->destroy();
        free(obj);
} ///:~

