#include <iostream>
using namespace std;

namespace ns {
        void func(int);
        void func(void);
}

void ns::func(int a)
{
        cout << "int args" << endl;
}

void ns::func(void)
{
        cout << "void args" << endl;
}

int main(int argc, const char *argv[]) {
        using ns::func; // using export all the overloaded version of function present in namespac

        func(1);
        func();

        return 0;
}
