//{T} TStackTest.cpp
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

template<class T>
class Stack {
        struct Link {
                T* data;
                Link* next;
                Link(T* dat, Link* nxt):
                        data(dat), next(nxt) {}
        }* head;
        public:
        Stack() : head(0) {}
        ~Stack(){
                while(head)
                        delete pop();
        }
        void push(T* dat) {
                head = new Link(dat, head);
        }
        T* peek() const {
                return head ? head->data : 0;
        }
        T* pop(){
                if(head == 0) return 0;
                T* result = head->data;
                Link* oldHead = head;
                head = head->next;
                delete oldHead;
                return result;
        }
};

class X {
        public:
                virtual ~X() { cout << "~X " << endl; }
};

int main(int argc, char* argv[]) {
        ifstream in("TStackTest.cpp");
        Stack<string> textlines;
        string line;

        // Read file and store lines in the Stack:
        while(getline(in, line))
                textlines.push(new string(line));

        // Pop some lines from the stack:
        string* s;
        for(int i = 0; i < 10; i++) {
                if((s = (string*)textlines.pop())==0) break; cout << *s << endl;
                delete s;
        } // The destructor deletes the other strings.
        // Show that correct destruction happens:
        Stack<X> xx;
        for(int j = 0; j < 10; j++)
                xx.push(new X);
} ///:~
