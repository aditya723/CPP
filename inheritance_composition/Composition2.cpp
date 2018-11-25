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
        X x; // Embedded object
        public:
        Y() { i = 0; }
        void f(int ii) { i = ii; x.set(ii); }
        int g() const { return i * x.read(); }
        void permute() { x.permute(); }
};

int main() {
        Y y;
        y.f(47);
        y.permute();
} ///:~
