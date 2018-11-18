// Using static const to create a
// compile-time constant inside a class
#include <string>
#include <iostream>
using namespace std;

class StringStack {
        static const int size = 100; // a member of a class which is constant, and which cannot change from one object of the class to another. This way we can make a compile time constant in c++ in inside a class. It do not occupy storage inside the class.
        const string* stack[size];
        int index;
        public:
        StringStack();
        void push(const string* s);
        const string* pop();
};

StringStack::StringStack() : index(0) {
        memset(stack, 0, size * sizeof(string*));
}

void StringStack::push(const string* s) {
        if(index < size)
                stack[index++] = s;
}

const string* StringStack::pop() {
        if(index > 0) {
                const string* rv = stack[--index];
                stack[index] = 0;
                return rv;
        }
        return 0; }
        string iceCream[] = {
                "pralines & cream",
                "fudge ripple",
                "jamocha almond fudge",
                "wild mountain blackberry",
                "raspberry sorbet",
                "lemon swirl",
                "rocky road",
                "deep chocolate fudge"
};

const int iCsz =  sizeof iceCream / sizeof *iceCream;

int main() {
        StringStack ss;
        for(int i = 0; i < iCsz; i++)
                ss.push(&iceCream[i]);
        const string* cp;
        while((cp = ss.pop()) != 0)
                cout << *cp << endl;
} ///:~
