#include <iostream>
using namespace std;

namespace Me {
        class Us {
                int a;
                //...
                friend void you(); // visible in namespcae Me, instead of global namespace
                /* Now the function you( )is a member of the namespace Me. 
                If you introduce a friend within a class in the global namespace, the
                friend is injected globally. */
                public: int b;
                Us(int i, int j): a(i), b(j) {}
        };
        void you()
        {
                Us c(3, 4);

                cout << "Me Funk you: " << c.a << c.b << endl; // reading private data directly
        }
}

void you()
{
        cout << "Global Funk you" << endl;
}
int main() {

        you();
        Me::Us b(1, 2);
        Me::you();

} ///:~
