#include <iostream>
using namespace std;

template<class T> // template syntax
class Array {
        enum { size = 100 };
        T A[size];
        public:
        T& operator[](int index) { // Since it returns a reference so it can be used both as lvalue and rvalue.
                return A[index];
        }
};
int main() {
        Array<int> ia; // Array of integer 
        Array<float> fa; // Array of float
        for(int i = 0; i < 20; i++) {
                ia[i] = i * i;
                fa[i] = float(i) * 1.414;
        }
        for(int j = 0; j < 20; j++)
                cout << j << ": " << ia[j]
                        << ", " << fa[j] << endl;
} ///:~
