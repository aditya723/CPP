#include <iostream>

// Operator mistakes
int main() {
        int a = 1, b = 0;


        // as b is 0, so this loop will not execute
        while(a = b) {
                std::cout << "This print should not come\n";
                // .... 
        }

        b = 1;
        // this loop will execute indefinitely
        while(a = b) {
                // .... 
        }
}
