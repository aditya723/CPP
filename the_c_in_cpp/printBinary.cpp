#include <iostream>

const int size = 1 << (sizeof(int) + 1);
//const int size = (sizeof(int));

void printBinary(const unsigned int val) {
        std::cout << size << "\n";
        for(int i = size; i >0; i--)
                if(val & (1 << i))
                        std::cout << "1";
                else
                        std::cout << "0";

                std::cout << "\n";
}

int main(int argc, const char *argv[]) {
        printBinary(100);
}
