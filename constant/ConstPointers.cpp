const int* u;

// const int k; // must be initialized in cpp
const int k = 9;

int const* v;

int d = 1;
int* const w = &d; // w is a pointer, which is const, that points to an int. Because the pointer itself is now the const, the compiler requires that it be given an initial value that will be unchanged for the life of that pointer. It’s OK, however, to change what that value points to by saying

const int* const x = &d;  // neither the pointer nor the object can be changed. 
int const* const x2 = &d; // neither the pointer nor the object can be changed.

int main() {
*w = 2; // allowed
//w = &d; // error, cannot assign to variable 'w' with const-qualified type 'int *const'
}
