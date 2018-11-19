#include <iostream>

void func()
{ 
//        std::cout << i; // here i is declared as extern in main hence it is local to main.
}

int main() {
        extern int i; // an example of local extern
        std::cout << i;
} ///:~
