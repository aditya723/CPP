// Constructors & destructors
#include <iostream>
using namespace std;

class Tree {
        int height;
        public:
        Tree(int h);// constructor
        ~Tree(); // Destructor
        void grow(int size);
        void printsize();
};

Tree::Tree(int i) {
        cout << "inside Tree constructor" << endl;
        height = i;
}

Tree::~Tree() {
        cout << "inside Tree destructor" << endl;
        printsize();
}

void Tree::grow(int years) {
        height += years;
}

void Tree::printsize() {
        cout << "Tree height is " << height << endl;
}

int main() {
        cout << "before opening brace" << endl;
        {
                Tree t(12);
                cout << "after Tree creation" << endl;
                // t.Tree(2); // can not call a constructor directly 
                t.printsize();
                t.grow(4);
                cout << "before closing brace" << endl;
        }
        cout << "after closing brace" << endl;

} ///:~

