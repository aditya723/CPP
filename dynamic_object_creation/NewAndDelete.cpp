#include <iostream>

class Tree {
        int height;
        public:
        Tree(int treeHeight) : height(treeHeight) {} ~Tree() { std::cout << "*"; }
        /*Defining the friend function inline doesn't change the friend status or the fact that it's a global function and not a class member function */
        friend std::ostream&
                operator<<(std::ostream& os, const Tree* t) {
                        return os << "Tree height is: "
                                << t->height << std::endl;
                } };

using namespace std;

int main() {
        Tree* t = new Tree(40);
        cout << t;
        delete t;
} ///:~

