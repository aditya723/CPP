// "Casting away" constness
class Y {
        int i;
        public:
                Y();
                void f() const;
                void g();
};

Y::Y() { i = 0; }

void Y::f() const {
        // Inside a const function this pointer will be equal to constant pointer to constant data.

        //!  i++; // Error -- const member function

        ((Y*)this)->i++; // OK: cast away const-ness // Better: use C++ explicit cast syntax: (const_cast<Y*>(this))->i++;
}

void Y::g() {
        int i;
        // this = &i; // this is constant pointer i.e. it can not be assigned to another address
}

int main() {
        const Y yy;
        yy.f(); // Actually changes it!
} ///:~
