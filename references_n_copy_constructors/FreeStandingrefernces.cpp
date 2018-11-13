#include <iostream>

using namespace std;

int y;

int &r = y;

// When a reference is created, it must be initialized to a live object. However, you can also say:
const int& q = 12;
// Compiler allocates a piece of storage, initializes it with value of 12 and then ties the reference to that piece of storage.

//  References are tied to someone else's storage
int x = 0;
int &a = x;

int main(void)
{
        cout << "x = " << x << ", a = " << a << endl;
        ++a;
        cout << "x = " << x << ", a = " << a << endl;

        //  &x = y; // Reference can not be changed to refer to another object. It is a constant pointer i.e data_type * const ptr
        x = y;
        cout << "x = " << x << ", a = " << a << endl;

        // int &ref; // unlike pointers, declaration of reference variable 'ref' requires an initializer.

        // int &ref = NULL; // non-const lvalue reference to type 'int' cannot bind to a temporary of type 'long'
        return 0;
}
