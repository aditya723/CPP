// Inline evaluation order
   class Forward {
     int i;
   public:
     Forward() : i(0) {}
     // Call to undeclared function: This works because the language definition states that no inline functions in a class shall be evaluated until the closing brace of the class declaration.
     int f() const { return g() + 1; }
     int g() const { return i; }
};
   int main() {
     Forward frwd;
     frwd.f();
} ///:~
