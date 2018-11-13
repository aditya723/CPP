#include <iostream>
using namespace std;

class Data {
        public:
                int a, b, c;
                void print() const {
                        cout << "a = " << a << ", b = " << b << ", c = " << c << endl;
                } 
};

int main()
{
        Data d, *dp = &d;
        int Data::*pmint = &Data::a;
        dp->*pmint = 47;

        pmint = &Data::b;
        d.*pmint = 48;
        
        pmint = &Data::c;
        dp->*pmint = 49;

        dp->print();
}
