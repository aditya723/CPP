// Testing the Mem class
//{L} Mem
#include "Mem.h"
#include <cstring>
#include <iostream>
using namespace std;

class MyString {
        Mem* buf;
        public:
        MyString(char* str = "");
        /* Constructor function is made as default argument constructor */
        /* Now this function is called as MyString() and MyString("somestring")*/
        ~MyString();
        void concat(char* str);
        void print(ostream& os);
};

//MyString::MyString() {  buf = 0; }

MyString::MyString(char* str) { 
        /* To differentiate if function is called as MyString() and MyString("somestring")*/
        if (!str) { // Pointer at an empty string
                buf = 0;
                return;
        }
        buf = new Mem(strlen(str) + 1);
        strcpy((char*)buf->pointer(), str);
}

void MyString::concat(char* str) {
        if(!buf) buf = new Mem;
        strcat((char*)buf->pointer(
                                buf->msize() + strlen(str) + 1), str);
}

void MyString::print(ostream& os) {
        if(!buf) return;
        os << buf->pointer() << endl;
}

MyString::~MyString() { delete buf; }

int main() {
        MyString s("My test string");
        s.print(cout);
        s.concat(" some additional stuff");
        s.print(cout);
        MyString s2;
        s2.concat("Using default argument constructor");
        s2.print(cout);
} ///:~
