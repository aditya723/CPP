// Preventing copy-construction
#include <iostream>

class nocc {
        int i;
        nocc(const nocc&) {} // No definition
        public:
        nocc(int i=0): i(i) {}
};

void f(nocc);

int main(void)
{
        nocc n;
        //! f(n); // Error: copy-constructor called
        //! nocc n2 = n; // Error: c-c called
        //! nocc n3(n); // Error: c-c called
        return 0;
}
