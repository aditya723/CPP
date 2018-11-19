namespace X {
        class Y {
                static int i;
                public:
                void f();
        };
        class Z;
        void func();
}

int X::Y::i = 9; // definition of static variable declared in class Y namespace X

class X::Z { // definition of class Z, declared in namespace X
        int u, v, w;
        public:
        Z(int i);
        int g();
};

X::Z::Z(int i) { u = v = w = i; }

int X::Z::g() { return u = v = w = 0; }

void X::func() {

        X::Z a(1);

        a.g();
}

int main(){} ///:~
