#include <iostream>

// array size must be a constant, If the expression is a constant expression, it shall have a value greater than zero.
// As a special case, the last element of a structure with more than one named member may have an incomplete array type; this is called a flexible array member.
// In Standard C and C++, zero-size array is not allowed..
// If you're using GCC, compile it with -pedantic option. It will give warning, saying:
// warning: ISO C forbids zero-size array 'a' [-pedantic]
// In case of C++, it gives similar warning.
// https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Zero-Length.html
// https://stackoverflow.com/questions/9722632/what-happens-if-i-define-a-0-size-array-in-c-c

struct s {
        int a;
        int arr[0]; // zero length array, sizeof returns 0;
        // http://embarc.org/man-pages/gcc/Zero-Length.html
}a;

struct t {
        int a;
        int arr[]; // flexible array, sizeof won't work here
}b;


int arr[0];

int main(int argc, const char *argv[]) {
        std::cout << "sizeof arr: " << sizeof arr << "\n";
        std::cout << "sizeof a.arr: " << sizeof a.arr << "\n";
      //  std::cout << "sizeof b.arr: " << sizeof b.arr << "\n";
}
