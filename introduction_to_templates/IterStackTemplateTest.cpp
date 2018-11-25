#include <iostream>
#include <fstream>
#include <string>
using namespace std;

template<class T, int ssize = 100>
class StackTemplate {
        T stack[ssize];
        int top;
        public:
        StackTemplate() : top(0) {}
        void push(const T& i) {
                stack[top++] = i;
        }
        T pop() {
                return stack[--top];
        }
        class iterator; // Declaration required
        friend class iterator; // Make it a friend
        class iterator { // Now define it
                StackTemplate& s;
                int index;
                public:
                iterator(StackTemplate& st): s(st),index(0){} // To create the "end sentinel" iterator: 
                iterator(StackTemplate& st, bool)
                        : s(st), index(s.top) {}
                T operator*() const { return s.stack[index];} T operator++() { // Prefix form
                        return s.stack[++index];
                }
                T operator++(int) { // Postfix form
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
                friend std::ostream& operator<<(
                                std::ostream& os, const iterator& it) {
                        return os << *it;
                }
        };
        iterator begin() { return iterator(*this); }
        // Create the "end sentinel":
        iterator end() { return iterator(*this, true);}
};

int main() {
        StackTemplate<int> is;
        for(int i = 0; i < 20; i++)
                is.push(i);
        // Traverse with an iterator:
        cout << "Traverse the whole StackTemplate\n"; 
        StackTemplate<int>::iterator it = is.begin(); 
        while(it != is.end())
                cout << it++ << endl;
        cout << "Traverse a portion\n";
        StackTemplate<int>::iterator
                start = is.begin(), end = is.begin();
        start += 5, end += 15;
        cout << "start = " << start << endl;
        cout << "end = " << end << endl;
        while(start != end)
                cout << start++ << endl;
        ifstream in("IterStackTemplateTest.cpp"); 
        string line;
        StackTemplate<string> strings; while(getline(in, line))
                strings.push(line);
        StackTemplate<string>::iterator
                sb = strings.begin(), se = strings.end();
        while(sb != se)
                cout << sb++ << endl;
} ///:~
