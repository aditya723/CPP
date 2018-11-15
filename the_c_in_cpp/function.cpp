#include <iostream>
using namespace std;

void f(int);

// unnamed argument is allowed in c++ but not allowed in c.
// if defined so, actual argument passed to function is not used in function defination
void f(int) {
        cout << "In side func" << endl;
}

int main(int argc, const char *argv[]) {
        f(1);
}
