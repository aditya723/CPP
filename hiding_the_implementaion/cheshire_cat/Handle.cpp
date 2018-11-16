// Handle implementation
#include "Handle.h"
// Define Handle's implementation:


/*
If you change the elements of Cheshire, the only file that must be recompiled is Handle.cpp because the header file is untouched.
otherwise, if Cheshire would have declared in Handle.h all the file where Handle.h is included will be compiled which will unnecessary consume time
*/
struct Handle::Cheshire {
  int i;
};

void Handle::initialize() {
  smile = new Cheshire;
  smile->i = 0;
}

void Handle::cleanup() {
  delete smile;
}

int Handle::read() {
  return smile->i;
}

void Handle::change(int x) {
  smile->i = x;
} ///:~

