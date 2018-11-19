#include <iostream>
using namespace std;

/* The names in this space are automatically available in that translation unit without qualification. It is guaranteed that an unnamed space is unique for each translation unit. If you put local names in an unnamed namespace, you don’t need to give them internal linkage by making them static.*/
namespace {
        class Arm  { /* ... */ };
        class Leg  { /* ... */ };
        class Head { /* ... */ };
        class Robot {
                Arm arm[4];
                Leg leg[16];
                Head head[3];
                // ...
        } xanthan;
        int i, j, k;
}

int main() {

        Arm two; // available without qualification
        i = 10; // available without qualification

        cout << "Hello, it is amazing!" << endl;
} ///:~
