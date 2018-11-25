#include <iostream>
#include <string>

using namespace std;

void require(int c, string s)
{
        if (!c) {
                cout << s;
                exit(1);
        }
}

class IntStack {
        enum { ssize = 100 };
        int stack[ssize];
        int top;
        public:
        IntStack() : top(0) {}
        void push(int i) {
                require(top < ssize, "Too many push()es");
                stack[top++] = i;
        }
        int pop() {
                require(top > 0, "Too many pop()s");
                return stack[--top];
        }
};

int main() {
        IntStack is;
        // Add some numbers, for interest:
        for(int i = 0; i < 20; i++)
                is.push(i);
        // Pop & print them:
        for(int k = 0; k < 20; k++)
                cout << is.pop() << endl;
} ///:~
