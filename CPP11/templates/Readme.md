# Template #
- Templates allow using types(built-in and non built-in) as parameters. The type must support the operations that the template actually uses.
```cpp
template <typename T>
auto display(const T& a) {
 std::cout << a << std::endl;
}
```
-After its introduction, T is used exactly like other type names. The scope of T extends to the end of the declaration prefixed by template<typename T>. In abpve example, T is valid only for display the function. Outside display, T does not exist.
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
- Using a template can lead to a decrease of code generated because code for a member function of a class template is only generated if that member is used.
- Templates can also be defined as aliases.This is like creating a shortcut or rename for a template instantiation pattern. Shorter, cleaner, and hides the implementation.
  ```
  cpp
template <typename Key, typename Value>
using Hash = std::unordered_map<Key, Value>;
...
...
Hash<std::string, int> frequency;
  ```
> **💡 TIP:** When designing a class template, it is usually a good idea to debug a particular class, such as `String`, before turning it into a template such as `String<C>`.
