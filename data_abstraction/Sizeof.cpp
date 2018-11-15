#include <iostream>
using namespace std;

struct A {
  int i[100];
};

struct B {
  void f();
};
/*
 in C++ we need the option of creating a struct whose sole task is to scope function names, so it is allowed.
 however, such structures are not allowed in c.
*/


void B::f() {}

int main() {
  cout << "sizeof struct A = " << sizeof(A)
       << " bytes" << endl;
 // size is same for both c and c++.

  cout << "sizeof struct B = " << sizeof(B)
        << " bytes" << endl;
 /*
 the result produced by the above statement is a somewhat surprising nonzero value. In early versions of the language, the size was zero, but an awkward situation arises when you create such objects: They have the same address as the object created directly after them, and so are not distinct. One of the fundamental rules of objects is that each object must have a unique address, so structures with no data members will always have some minimum nonzero size.
 */

  return 0;
} ///:~
