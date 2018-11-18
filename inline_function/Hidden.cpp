// Hidden activities in inlines
#include <iostream>
using namespace std;

class Member {
        int i, j, k;
        public:
        Member(int x = 0) : i(x), j(x), k(x) { cout << "Member" << endl;}
        ~Member() { cout << "~Member" << endl; }
};
class WithMembers {
        Member q, r, s; // Have constructors
        int i;
        public:
        WithMembers(int ii) : i(ii) { cout << "WithMembers" << endl;} // Trivial?
        ~WithMembers() {
                cout << "~WithMembers" << endl;
        }
};
int main() {
        WithMembers wm(1);
} ///:~
