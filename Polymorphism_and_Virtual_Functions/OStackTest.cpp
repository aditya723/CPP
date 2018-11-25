#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class Object {
        public:
                virtual ~Object() = 0;
};

// Required definition:
inline Object::~Object() {}

class Stack {
        struct Link {
                Object* data;
                Link* next;
                Link(Object* dat, Link* nxt) :
                        data(dat), next(nxt) {}
        }* head;
        public:
        Stack() : head(0) {}
        ~Stack(){
                while(head)
                        delete pop();
        }
        void push(Object* dat) {
                head = new Link(dat, head);
        }
        Object* peek() const {
                return head ? head->data : 0;
        }
        Object* pop() {
                if(head == 0) return 0;
                Object* result = head->data;
                Link* oldHead = head;
                head = head->next;
                delete oldHead;
                return result;
        }
};

// Use multiple inheritance. We want
// both a string and an Object:
class MyString: public string, public Object { public:
        ~MyString() {
                cout << "deleting string: " << *this << endl;
        }
        MyString(string s) : string(s) {}
};

int main(int argc, char* argv[]) {

        ifstream in("OStackTest.cpp");
        Stack textlines;
        string line;

        // Read file and store lines in the stack:
        while(getline(in, line))
                textlines.push(new MyString(line));

        // Pop some lines from the stack:
        MyString* s;
        for(int i = 0; i < 10; i++) {
                if((s=(MyString*)textlines.pop())==0) break;
                cout << *s << endl;
                delete s;
        }

        cout << "Letting the destructor do the rest:"
                << endl;
} ///:~
