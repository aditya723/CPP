namespace U {
        inline void f() {}
        inline void g() {}
}
namespace V {
        inline void f() {}
        inline void g() {}
}
void h() {
        using namespace U; // Using directive
        using V::f; // Using declaration
        f(); // Calls V::f();
        U::f(); // Must fully qualify to call
}
int main() {} ///:~
