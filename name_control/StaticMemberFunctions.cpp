class X {
        int i;
        static int j;
        public:
        X(int ii = 0) : i(ii) {
                // Non-static member function can access
                // static member function or data:
                j = i; }
        int val() const { return i; }
        static int incr() {
                //! i++; // Error: static member function
                // cannot access non-static member data
                return ++j;
        }
        static int f() {
                //! val(); // Error: static member function
                // cannot access non-static member function
                return incr(); // OK -- calls static
        } };

/*
Because static member function have no this pointer, static member functions can neither access non-staticdata members nor call non-staticmember functions.
*/
int X::j = 0;

int main() {
        X x;
        X* xp = &x;
        x.f();
        xp->f();
        X::f(); // Only works with static members
} ///:~

