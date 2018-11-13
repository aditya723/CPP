#include <iostream>
#include <string>

using namespace std;

class Howmany2 {
        static int objectCount;
        public:
                Howmany2() {objectCount++; print("Howmany2()");}
                static void print(const string& msg = "") {
                        if (msg.size() != 0) cout << msg << ";";
                        cout << "objectCount = " << objectCount << endl;
                }
                ~Howmany2() {
                        objectCount--;
                        print("~Howmany2()");
                }
                Howmany2(const Howmany2& h) {
                        ++objectCount;
                        print("Howmany2_copy_constructor()");
                }
};

int Howmany2::objectCount = 0;

// Pass and return By value
Howmany2 f(Howmany2 x) {
        x.print("x argument inside f()");
        return x;
}

int main(void)
{
        Howmany2 h;
        h.print("After construction of h");

        Howmany2 h2 = f(h);
        h2.print("After call to f()");
        return 0;
}
