// Navigating class hierarchies with static_cast
#include <iostream>
#include <typeinfo>
using namespace std;

class Shape { public: virtual ~Shape() {}; };
class Circle : public Shape {};
class Square : public Shape {};
class Other {};

int main(int argc, const char *argv[]) {
        
        Circle c;
        Shape *s = &c; // Upcast, just normal things

        s = static_cast<Shape *>(&c); // More explicit but unnecessary, Since upcasting is such a safe and common operation, the cast becomes cluttering)
        Circle *cp = 0;
        Square *sp = 0;
        // Static Navigation of class hierarchies requires extra type information:
        if (typeid(s) == typeid(cp))
                cp = static_cast<Circle *>(s);
        if (typeid(s) == typeid(sp))
                sp = static_cast<Square *>(s);

        if (cp != 0)
                cout << "It is a circle!" << endl;

        if (sp != 0)
                cout << "It is a square!" << endl;

        // Static navigation is ONLY an efficiency hack; // dynamic_cast is always safer. However:
//        Other *op = static_cast<Other *>(s); //static_cast won’t allow you to cast out of the hierarchy, as the traditional cast will, so it’s safer.
        // Conveniently gives an error message, while
        Other *op = (Other *)s;
        // does not

        Other *Op = dynamic_cast<Other *>(s); // static_cast will also allow you to cast out of the hierarchy, same as traditional cast, so it’s not safer.
        cout << "Op = " << (long)Op << endl;

return 0;
}
