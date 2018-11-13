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
                fp[0] = &Widget::f;
                fp[1] = &Widget::g;
                fp[2] = &Widget::h;
                fp[3] = &Widget::i;
        }
        void select(int i, int j) {
                if (i < 0 || i >= cnt) return;
                (this->*fp[i])(j);
        }
        int count() {return cnt;};
};

int main(int argc, const char *argv[]) {
        Widget w;
        for(int i = 0; i < w.count(); i++) {
                w.select(i, 47);
        }
}
