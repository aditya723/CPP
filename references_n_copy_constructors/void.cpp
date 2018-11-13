#include <iostream>

using namespace std;

struct a{
        int a;  int b;
};

struct b{
        long int a;  long int b;
};

int main(void)
{
        struct a *a;
        struct b *b;
        void *v;

       // a = b; allowed in c but not in cpp as cpp compiler does strict type checking
        v = a;

        return 0;
}
