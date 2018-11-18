// Returning consts by value
// has no meaning for built-in types

int f3() { return 1; }

const int f4() { return 1; }

// since, the data is pass by value hence const has no use here
void func(const int a) {
}

int main() {
        func(2);
        const int j = f3(); // Works fine
        int k = f4(); // But this works fine too!
        k = 5;
        /*The reason const has no meaning when you’re returning a built-in type by value is that the compiler already prevents it from being an lvalue (because it’s always a value, and not a variable).*/
} ///:~

