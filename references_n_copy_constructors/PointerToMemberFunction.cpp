#include <iostream>

using namespace std;

class Widget {
        public:
                void f(int) const { cout << "Widget::f()\n"; }
                void g(int) const { cout << "Widget::g()\n"; }
                void h(int) const { cout << "Widget::h()\n"; }
                void i(int) const { cout << "Widget::i()\n"; }
};

int main(int argc, const char *argv[]) {
        Widget w;
        Widget *wp = &w;

        void (Widget::*pmem)(int)const = &Widget::f;
        (w.*pmem)(1);
        (wp->*pmem)(2);

        pmem = &Widget::h;
        (w.*pmem)(3);
        (wp->*pmem)(4);
}
