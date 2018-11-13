#include <iostream>

using namespace std;

//void f(int& a) { const in func argument is especially important when you function receive a temporary object.
void f(const int& a) {
        cout << "Inside Function" << endl; 
}

int main(void)
{
        f(10);
}
