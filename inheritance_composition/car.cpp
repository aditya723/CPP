// Public composition

// The is-a relationship is expressed with inheritance, and the has-a relationship is expressed with composition.

class Engine {
        public:
                void start() const {}
                void rev() const {}
                void stop() const {}
};

class Wheel {
        public:
                void inflate(int psi) const {}
};

class Window {
        public:
                void rollup() const {}
                void rolldown() const {}
};

class Door {
        public:
                Window window; // Composition is generally used when you want the features of an existing class inside your new class, but not its interface.
                void open() const {}
                void close() const {}
};

class Car {
        public:
                Engine engine;
                Wheel wheel[4];
                Door left, right; // 2-door
};

int main() {
        Car car;
        car.left.window.rollup();
        car.wheel[0].inflate(72);
} ///:~
