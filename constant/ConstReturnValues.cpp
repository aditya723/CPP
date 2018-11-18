#include <iostream>
// Constant return by value
// Result cannot be used as an lvalue
class X {
        int i;
        public:
        X(int ii = 0);
        void modify();
        void print() {std::cout << "data is: " << i << "\n";}
};

X::X(int ii) { i = ii; }

void X::modify() { i++; }

X f5() {
        return X();
}

const X f6() {
        return X();
}

void f7(X& x) { // Pass by non-const reference
        x.modify();
}

int main() {
        f5() = X(1); // OK -- non-const return value
        f5().print(); // data is: 0
        f5().modify(); // OK
        f5().print(); // data is: 0
        // f5( ) returns an X object, and for the compiler to satisfy the above expressions it must create a temporary to hold that return value and as soon as the expression is over the temporary is cleaned up. As a result, the modifications are lost so this code is probably a bug – but the compiler doesn’t tell you anything about it.


        // Causes compile-time errors:
         // f7(f5()); // no matching function for call to 'f7',candidate function not viable: expects an l-value for 1st argument
         // The reason this won’t compile in C++ is because of the creation of a temporary, the compiler must manufacture a temporary object to hold the return value of f5( ) so it can be passed to f7( ). This would be fine if f7( ) took its argument by value; then the temporary would be copied into f7( ) and it wouldn’t matter what happened to the temporary X. However, f7( ) takes its argument by reference, which means in this example takes the address of the temporary X. Since f7( ) doesn’t take its argument by const reference, it has permission to modify the temporary object.


        //!  f6() = X(1); // f6() returns as a const value hence the object returned can't be used as lvalue.
        //!  f6().modify(); // const object can  not modify anything
        //!  f7(f6()); // conflict as f6() returns a const value but f7() takes a non const object
} ///:~
