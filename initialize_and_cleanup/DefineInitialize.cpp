// Defining variables anywhere
#include <iostream>
#include <cassert>
#include <string>
using namespace std;

class G {
        int i;
        public:
        G(int ii);
};

G::G(int ii) { i = ii; }

int main() {
        cout << "initialization value? ";
        int retval = 0;
        cin >> retval;
        assert(retval != 0);
        int y = retval + 3;
        G g(y);
} ///:~

