#include <iostream>
using namespace std;

class aditya {
        int a;
        static int objcout;
        public:
//                aditya(int i = 19): a(i){ cout << "Default constructor: "<< ++objcout << endl;}
                aditya(int i = 10): a(i) { cout << "default Argument constructor: " << ++objcout <<endl;}
                void print(void) {
                        cout << "a: " << a << endl;
                }
                ~aditya () {cout << "destructor" << --objcout << endl;}
};

int aditya::objcout = 0;

int main(int argc, const char *argv[]) {

        aditya *a = new aditya(2); // one object is created whose data is initialized to 2
        aditya *b = new aditya[100]; // can allocates array of 100 objects, objects can not be initialized here;

        delete a; // delete a

//        delete b; // not the desired result.
        delete []b; // desired result, no need to give size of array compiler automatically does it.
        return 0;
}
