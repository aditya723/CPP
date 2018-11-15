#include <iostream>

// void func(int arr[])
void func(int arr[])
{
       // sizeof on array function parameter will return size of 'int *' instead of 'int []'
        std::cout << "sizeof arr: " << sizeof arr << "\n";
}

int main(int argc, const char *argv[]) {
        int arr[10];

        func(arr);

        return 0;
}
