// Automatic creation of the copy-constructor
#include <iostream>
#include <string>

using namespace std;

class Withcc {
        int a;
        public:
                Withcc() {}
                Withcc(const Withcc&) {
                        cout << "copy-constructor"<< endl;
                }
};

class Wocc {
        string id;
        public:
                Wocc(const string& ident = ""):id(ident) {}
                void print(const string& msg = "") const {
                        if(msg.size() != 0) cout << msg << ": ";
                                cout << id << endl;
                }
};

class Composit {
        Withcc withcc;
        Wocc wocc;
        public:
                Composit(): wocc("Composit()") {}
                void print(const string& msg = "") const {
                        wocc.print(msg);
                }
};

int main(int argc, const char *argv[]) {
        Composit c;
        c.print("Content of c");
        cout << "calling composit copy-constructor" << endl;
        Composit c2 = c; 
        c2.print("Content of c2");
        return 0;
}
