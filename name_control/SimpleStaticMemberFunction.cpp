#include <iostream>

class x {
        public:
                static int func();
};

int x::func() {
        std::cout << "static func" << "\n";
        return 0;
}

int main(int argc, const char *argv[]) {
        x::func(); // no object is required
}
