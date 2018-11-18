#include <iostream>
using namespace std;

#define DEBUG(x) cout << #x " = " << x << endl

#define TRACE(s) cerr << #s " = " << s << endl;

#define FIELD(a) char* a##_string; int a##_size

class Record {
     FIELD(one);
     FIELD(two);
     FIELD(three);
     // ...
};

inline int f(int i) {
        return i;
}

int main(int argc, const char *argv[]) {
        for(int i = 0; i < 10; i++) {
                TRACE(f(i));
        }
}

