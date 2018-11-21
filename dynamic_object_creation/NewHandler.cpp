// Changing the new-handler
#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

int aditya = 0;
void out_of_memory() {
        cerr << "memory exhausted after " << aditya
                << " allocations!" << endl;
        exit(1);
}
int main() {
        set_new_handler(out_of_memory);
        while(1) {
                aditya++;
                int *a = new int[1000]; // Exhausts memory
                cout << "a: " << a[0] << endl;
        }
};
