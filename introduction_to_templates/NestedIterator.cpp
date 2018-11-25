#include <iostream>
#include <string>
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
        class iterator;
        friend class iterator;
        class iterator {
                IntStack& s;
                int index;
                public:
                iterator(IntStack& is) : s(is), index(0) {}
                // To create the "end sentinel" iterator:
                iterator(IntStack& is, bool)
                        : s(is), index(s.top) {}
                int current() const { return s.stack[index]; }
                int operator++() { // Prefix
                        return s.stack[++index];
                }
                int operator++(int) { // Postfix
                        return s.stack[index++];
                }
                // Jump an iterator forward
                iterator& operator+=(int amount) {
                        index += amount;
                        return *this;
                }
                // To see if you're at the end:
                bool operator==(const iterator& rv) const {
                        return index == rv.index;
                }
                bool operator!=(const iterator& rv) const {
                        return index != rv.index;
                }
                friend ostream&
                        operator<<(ostream& os, const iterator& it) {
                                return os << it.current();
                        }
        };
        iterator begin() { return iterator(*this); }
        // Create the "end sentinel":
        iterator end() { return iterator(*this, true);}
};
int main() {
        IntStack is;
        for(int i = 0; i < 20; i++)
                is.push(i);
        cout << "Traverse the whole IntStack\n";
        IntStack::iterator it = is.begin();
        while(it != is.end())
                cout << it++ << endl;
        cout << "Traverse a portion of the IntStack\n";
        IntStack::iterator
                start = is.begin(), end = is.begin();
        start += 5, end += 15;
        cout << "start = " << start << endl;
        cout << "end = " << end << endl;
        while(start != end)
                cout << start++ << endl;
} ///:~

