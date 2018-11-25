class X {
        int i;
        public:
        X() { i = 0; }
        void set(int ii) { i = ii; }
        int read() const { return i; }
        int permute() { return i = i * 47; }
};

class Y {
        int i;
        public:
        X x; // Embedded object, composition
        Y() { i = 0; }
        void f(int ii) { i = ii; }
        int g() const { return i; }
};

int main() {
        Y y;
        y.f(47);
        y.x.set(37); // Access the embedded object
} ///:~
