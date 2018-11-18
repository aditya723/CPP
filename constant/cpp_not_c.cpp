#include <iostream>

const int bufsize = 10;
// The C compiler cannot treat a const as a compile-time constant. 
//  In C, if write below statement you will get an error, even though it seems like a rational thing to do. Because bufsize occupies storage somewhere, the C compiler cannot know the value at compile time.
char buf[bufsize];

// You can optionally say
//const int bufsize1; // not allowed on cpp
const int bufsize1 = 0;
// in C, but not in C++, and the C compiler accepts it as a declaration indicating there is storage allocated elsewhere. Because C defaults to external linkage for consts, this makes sense. C++ defaults to internal linkage for consts so if you want to accomplish the same thing in C++, you must explicitly change the linkage to external using extern:

extern const int bufsize; // Declaration only
// This line also works in C.In C++, a const doesn’t necessarily create storage. In C a const always creates storage. 

int main() {}
