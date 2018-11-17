// Unions with constructors and member functions

#include<iostream>
using namespace std;

// int and float are overlaid on the same piece of storage
union U {
        private: //Access control
        int i;
        float f;
        public:
                U(int a): i(a) { cout << "Constructor" << __func__ << endl;}
                U(float b): f(b) { cout << " Constructor" << __func__ << endl; }
                ~U() { cout << "Destructor" << __func__ << endl; }
                int read_int() { return i;}
                float read_float() { return f;}
};

int main(int argc, const char *argv[]) {
        U X(12), Y(1.9F);

        cout << X.read_int() << endl;
        cout << Y.read_float() << endl;

        return 0;
}
