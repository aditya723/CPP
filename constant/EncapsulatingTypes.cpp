#include <iostream>
using namespace std;
class Integer {
  int i;
public:
  Integer(int ii = 0);
  void print();
};

/*It’s often useful to encapsulate a built-in type inside a class to guarantee initialization with the constructor.*/
Integer::Integer(int ii) : i(ii) {}

void Integer::print() { cout << i << ' '; }

int main() {
     Integer i[100];
     /*The array of Integers in main( )are all automatically initialized to zero. This initialization isn’t necessarily more costly than a for loop or memset( ). Many compilers easily optimize this to a very fast process.*/
     for(int j = 0; j < 100; j++)
       i[j].print();
   } ///:~
