// The "mutable" keyword
class Z {
        int i;
        mutable int j; // the mutable keyword in the class specify that a particular data member may be changed inside a const object.
        public:
        Z();
        void f() const;
};

Z::Z() : i(0), j(0) {}

void Z::f() const {
        //! i++; // Error -- const member function
        j++; // OK: mutable
}

int main() {
        const Z zz;
        zz.f(); // Actually changes it!
}
