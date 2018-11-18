class X {
        int i;
        public:
        X(int ii);
        int f() const; // const member function
        int f1() ; // non const member function
};

X::X(int ii) : i(ii) {}

int X::f() const { return i; }

int X::f1() { return i; }

int main() {
        X x1(10);
        x1.f(); //! Ok,  non const object calling non const member
        x1.f1(); //! Ok, non const object calling const member function

        const X x2(20);
        x2.f(); //! Ok, const object calling const member function
 //       x2.f1(); //! Error, const object calling non const member function
} ///:~
