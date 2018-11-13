#include <stdio.h>

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

        a = b;
        v = a;

        return 0;
}
