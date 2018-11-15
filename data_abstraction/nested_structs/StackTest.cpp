//{L} Stack
//{T} StackTest.cpp
// Test of nested linked list
#include "Stack.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
        ifstream in("StackTest.cpp");

        Stack textline;

        textline.initialize();

        string line;
        // Read file and store lines in the Stack:
        while (getline(in, line)) {
                textline.push(new string(line));
        }

        // Pop the lines from the Stack and print them:
        string *s;
        while ((s = (string*)textline.pop()) != 0) {
               cout << *s << endl;
               delete s;
        }
        textline.cleanup();
}
