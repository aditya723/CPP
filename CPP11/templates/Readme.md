- Templates allow using types as parameters. The type must support the operations that the template actually uses.
- Duck typing : If it looks like a duck and quacks like a duck, the template will accept it. In the below example, T and U only need to support the + operator. They don’t need to inherit from each other, or from a common parent.

```CPP
template <typename T, typename U>
auto add(const T& a, const U& b) {
    return a + b;
}
