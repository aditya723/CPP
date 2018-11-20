#include <iostream>
using namespace std;

class X {
        int i;
        public:
                X(int ii): i(ii) {}
                int pr(void) {
                        return i;
                }
};

class stat {
        // This doesn't work, although you might want it to
        //! static const X x(100);
        // Both const and non-const static class object must be initiated externally
        static X x2;
        static X xtable[];
        static const X x3;
        static const X xtable2[];
        #if 1
        public:
                void print() {
                        cout << "stat::x2 = " << x2.pr() << endl;
                        cout << "table[0] = " << xtable[0].pr() << endl;
                }
        #endif
};

X stat::x2(100);

X stat::xtable[] = {X(1), X(2), X(3), X(4)};

const X stat::x3(100);

const X stat::xtable2[] = {X(1), X(2), X(3), X(4)};

int main(int argc, const char *argv[]) {
        stat v;

        v.print();

        return 0;
}
