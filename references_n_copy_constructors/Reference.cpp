#include <iostream>

using namespace std;

int *f(int *x)
{
        static int a = 10; // static variable are not stored on function stack hence its address can be successfully returned from function stack.
        // However, below is not a good idea
        // int a = 10; // invalid as returning a stack variable is not a good idea.
        return &a;
//        (*x)++;
//        return x;
}

int& h()
{
//        int a = 10; // reference to stack memory associated with local variable 'a' returned.
        static int a = 10; // Safe as a being static stored outside this scope.
        return a;
}

int main(int argc, const char *argv[]) {

        int *a = f(NULL);
        cout << "a = " << *a << endl;

        int &b = h();
        cout << "b = " << b<< endl;
        return 0;
}
