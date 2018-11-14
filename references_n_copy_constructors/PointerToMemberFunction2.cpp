#include <iostream>
using namespace std;


class Widget {
        void f(int) const { cout << "Widget::f()\n"; }
        void g(int) const { cout << "Widget::g()\n"; }
        void h(int) const { cout << "Widget::h()\n"; }
        void i(int) const { cout << "Widget::i()\n"; }
        enum {cnt = 4};
        void (Widget::*fp[cnt])(int)const;
        public:
        Widget() {
                fp[0] = &Widget::f; // Should confer to the pointer to member syntax
                fp[1] = &Widget::g; // fp[1] = &g should not work even though it is a member function
                fp[2] = &Widget::h;
                fp[3] = &Widget::i;
        }
        void select(int i, int j) {
                if (i < 0 || i >= cnt) return;
                (this->*fp[i])(j); // this is necessary here as the syntax requires that pointer to member always bound to an object when it is dereferenced
        }
        int count() {return cnt;};
};

int main(int argc, const char *argv[]) {
        Widget w;
        for(int i = 0; i < w.count(); i++) {
                w.select(i, 47);
        }
}
