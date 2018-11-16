#include <iostream>
using namespace std;

// Friend allows special access

// Declaration (incomplete type specification): 
struct X;

struct Y {
        void f(X*);
};

struct X { // Definition
        private:
                int i;
        public:
                void initialize();
                friend void g(X*, int); // global friend function
                /*
                g(X*, int) is nowhere declared before! it turns out that friend can be used this way ti simultaneously declare the function and give it friend status.
                */
                friend void Y::f(X*); // struct member function
                friend struct Z; // Entire struct as friend
                /* Z is an incomplete type but with friend it is accepted */
                friend void h(); // another global fucntion
                /* same hack is applied as of g() */
};
/*
You can declare a global function as a friend, and you can also declare a member function of another structure, or even an entire structure, as a friend.
*/
void X::initialize() {i = 10;}

void g(X *x, int i)
{
        x->i = i;
}

void Y::f(X* x) {
        
        x->i = 47;
}

struct Z {
        private:
                int j;
        public:
                void initialize();
                void g(X* x);
};

void Z::initialize() {
        j = 99;
}

void Z::g(X* x) {
        x->i += j;
}

void h()
{
        X x;
        x.i = 100; // Direct data maipulation
}

int main(int argc, const char *argv[]) {
        X x;
        Z z;
        z.g(&x);

        return 0;
}
