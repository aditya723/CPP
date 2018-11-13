#include <iostream>
#include <string>

using namespace std;

class Howmany {
        static int objectCount;
        public:
                Howmany() {objectCount++; print("Howmany()");}
                static void print(const string& msg = "") {
                        if (msg.size() != 0) cout << msg << ";";
                        cout << "objectCount = " << objectCount << endl;
                }
                ~Howmany() {
                        objectCount--;
                        print("~Howmany()");
                }
};

int Howmany::objectCount = 0;

// Pass and return By value
Howmany f(Howmany x) {
        x.print("x argument inside f()");
        return x;
}

int main(void)
{
        Howmany h;
        h.print("After construction of h");

        Howmany h2 = f(h);
        h2.print("After call to f()");
        return 0;
}
