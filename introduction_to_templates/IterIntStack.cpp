#include <iostream>
using namespace std;
class IntStack {
        enum { ssize = 100 };
        int stack[ssize];
        int top;
        public:
        IntStack() : top(0) {}
        void push(int i) {
                stack[top++] = i;
        }
        int pop() {
                return stack[--top];
        }
        friend class IntStackIter; // iterator class is friend of this class
};

class IntStackIter {
        IntStack& s;
        int index;
        public:
        IntStackIter(IntStack& is) : s(is), index(0) {}
        int operator++() { // Prefix
                return s.stack[++index];
        }
        int operator++(int) { // Postfix
                return s.stack[index++];
        } };
int main() {
        IntStack is; 
        for(int i = 0; i < 20; i++)
                is.push(i);

        // Traverse with an iterator:
        IntStackIter it(is);
        for(int j = 0; j < 20; j++)
                cout << it++ << endl;
} ///:~
