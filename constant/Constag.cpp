// Constants and aggregates
const int i[] = { 1, 2, 3, 4 };
//! float f[i[3]]; // Illegal
//The value cannot be used at compile time because the compiler is not required to know the contents of the storage at compile time.
struct S { int i, j; };
const S s[] = { { 1, 2 }, { 3, 4 } };
//! double d[s[1].j]; // Illegal
//The value cannot be used at compile time because the compiler is not required to know the contents of the storage at compile time.

int main() {} ///:~
