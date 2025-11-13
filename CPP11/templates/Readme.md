# Template #
- Templates allow using types(built-in and non built-in) as parameters. The type must support the operations that the template actually uses.
- Duck typing : If it looks like a duck and quacks like a duck, the template will accept it. In the below example, T and U only need to support the + operator. They don’t need to inherit from each other, or from a common parent.

```CPP
template <typename T, typename U>
auto add(const T& a, const U& b) {
    return a + b;
}
```

- C++ templates allow you to parameterize your code — meaning you can write a class, function, or type alias where some part of it is left unspecified, and can be filled in later with:
   - A type (e.g., int, std::string, or a user-defined class), or
   - A value (e.g., an integer constant, a pointer, a reference, a boolean), depending on the template kind.

**Type parameters**

```cpp
template <typename T> // Here, T is a type parameter.
class Vector {
    T* data;
};
Vector<int> v1;
```

**Value (non-type) parameters**

```cpp
template <int N>
struct Array {
    int data[N];
};
Array<4> a;
```

When you write a template like:
```cpp
template <typename T>
T add(T a, T b) {
    return a + b;
}
```
There is no place in the code where you explicitly say:
- T must support the + operator
- T must be copyable
- T must be default-constructible

Instead, the compiler only checks these requirements when the template is instantiated, not when it is defined. If you pass a type that doesn’t support +, you get a long, cryptic template error. CPP20 solves this problem.

```cpp
//CPP20
template <std::integral T> // This forces T to be of type std::integral
T add(T a, T b) { return a + b; }
```

