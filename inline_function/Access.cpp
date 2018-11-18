// Inline access functions
// Same as normal call, no surprise here
class Access {
  int i;
public:
  int read() const { return i; }
  void set(int ii) { i = ii; }
};
int main() {
  Access A;
  A.set(100);
  int x = A.read();
} ///:~
