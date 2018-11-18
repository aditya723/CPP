// Constant pointer arg/return
// Promotion is allowed but demotion isn't

void t(int*) {}

void u(const int* cip) {
        //!  *cip = 2; // Illegal -- modifies value
        int i = *cip; // OK -- copies value
        //!  int* ip2 = cip; // Illegal: non-const
}

const char* v() {
        // Returns address of static character array:
        return "result of function v()";
}

const int* const w() {
        static int i;
        return &i;
}

int main() {
        int x = 0;
        int* ip = &x;

        const int* cip = &x; // non const can be assigned to const but reverse is not true.

        t(ip);  // OK non const to non const

        //!  t(cip); // Not OK, const to non const

        u(ip);  // OK non, const to const

        u(cip); // Also OK, const to const

        //!  char* cp = v(); // Not OK, const to non const

        const char* ccp = v(); // OK const to const

        //!  int* ip2 = w(); // Not OK const to non const

        const int* const ccip = w(); // OK const to const

        const int* cip2 = w(); // OK const to const
        /* You would also expect that the compiler refuses to assign the return value of w( ) to a non-const pointer, and accepts a const int* const, but it might be a bit surprising to see that it also accepts a const int*, which is not an exact match to the return type. Once again, because the value (which is the address contained in the pointer) is being copied, the promise that the original variable is untouched is automatically kept.Thus, the second const in const int* const is only meaningful when you try to use it as an lvalue, in which case the compiler prevents you. */

        //!  *w() = 1; // Not OK  cost data pointer to data
} ///:~
