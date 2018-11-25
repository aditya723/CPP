// Object sizes with/without virtual functions
#include <iostream>
using namespace std;

// has size same as size of int
class NoVirtual {
        int a;
        public:
        void x() const {}
        int i() const { return 1; }
};

// has size as 1
class NoVirtual_nodata {
        public:
        void x() const {}
        int i() const { return 1; }
};

// has size same as size of pointer
class OneVirtual_nodata {
        public:
        virtual void x() const {}
        int i() const { return 1; }
};


// has size same as size of int + size of pointer + padding
class OneVirtual {
        int a;
        public:
        virtual void x() const {}
        int i() const { return 1; }
};

// has size same as size of int + size of pointer + padding
class TwoVirtuals {
        int a;
        public:
        virtual void x() const {}
        virtual int i() const { return 1; }
};

int main() {
        cout << "int: " << sizeof(int) << endl;

        cout << "NoVirtual: " << sizeof(NoVirtual) << endl;

        cout << "NoVirtual_nodata: " << sizeof(NoVirtual_nodata) << endl;

        cout << "void* : " << sizeof(void*) << endl;

        cout << "OneVirtual_nodata: " << sizeof(OneVirtual_nodata) << endl;

        cout << "OneVirtual: " << sizeof(OneVirtual) << endl;

        cout << "TwoVirtuals: " << sizeof(TwoVirtuals) << endl;
} ///:~
