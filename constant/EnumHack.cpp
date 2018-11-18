#include <iostream>
using namespace std;

class Bunch {
  enum { size = 1000 }; // act as compile time constant, do not occupy space in object and local to class. Absolutely same as, static const int size = 100;
  int i[size];
};

int main() {
     cout << "sizeof(Bunch) = " << sizeof(Bunch)
          << ", sizeof(i[1000]) = "
          << sizeof(int[1000]) << endl;
} ///:~
