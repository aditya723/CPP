namespace U {
        inline void f() {}
        inline void g() {}
}
namespace V {
        inline void f() {}
        inline void g() {}
}
namespace Q {
        using U::f;
        using V::g;
        // ...
}
void m() {
        using namespace Q;
        f(); // Calls U::f();
        g(); // Calls V::g();
}
int main() {} ///:~
