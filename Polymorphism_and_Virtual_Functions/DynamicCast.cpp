/* When you use dynamic_cast, you must be working with a true polymorphic hierarchy – one with virtual functions – because dynamic_cast uses information stored in the VTABLE to determine the actual type. */

#include <iostream>
using namespace std;

class Pet { public: virtual ~Pet(){}};
class Dog : public Pet {};
class Cat : public Pet {};

int main(void)
{
        Pet *b = new Cat; // Upcast

        Dog *d1 = dynamic_cast<Dog*>(b); // down casting to dog

        Cat *d2 = dynamic_cast<Cat*>(b); // down casting to cat

        cout << "d1 = " << (long)d1 << endl;
        cout << "d2 = " << (long)d2 << endl;
}
