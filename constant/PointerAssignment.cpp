int d = 1; // non const
const int e = 2; // const

int* u = &d; // OK -- d not const

//! int* v = &e; // Illegal -- e const
// you can’t assign the address of a const object to a non-const pointer because then you’re saying you might change the object via the pointer.

int* w = (int*)&e; // Legal but bad practice, explicit type cast

char* cp = "howdy"; // So character array literals are actually constant character arrays. cp is pointer to constant data

char cp1[] = "howdy"; // cp1 is constant pointer

int main() {} ///:~
