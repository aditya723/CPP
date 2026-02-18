# CPP11 #

Reference: The C++ Programming Language Fourth Edition Bjarne Stroustrup and Internet(GFG etc.).

The C++ language features most directly support four programming styles:

_Procedural programming_

_Data abstraction_: This is programming focused on the design of interfaces, hiding implementation details in general and representations in particular. The facilities for defining classes with private implementation details, constructors and destructors, and associated operations directly support this. The notion of an abstract class provides direct support for complete data hiding.

_Object-oriented programming_: This is programming focused on the design, implementation, and use of class hierarchies. Class hierarchies provide run-time polymorphism and encapsulation.

_Generic programming_: This is programming focused on the design, implementation, and use of general algorithms. Templates provide (compiletime) parametric polymorphism.

## Introduction ##

### The Basics ###

**Constness**

Constness improves the performance.

_const_: I promise not to change this value

_constexpr_: To be evaluated at compile time
  - For a function to be usable in a constant expression, that is, in an expression that will be evaluated by the compiler, it must be defined constexpr.
  - A constexpr function can be used for non-constant arguments, but when that is done the result is not a constant expression.

```cpp

constexpr double square(double x) { return x * x;}
const int dmv = 17;   // dmv is a named constant
int var = 17;         // var is not a constant

// Compile-time evaluation
constexpr double max1 = 1.4 * square(dmv);   // OK if square(17) is constexpr
// constexpr double max2 = 1.4 * square(var);  // ERROR: var is not a constant expression

// Runtime evaluation allowed
const double max3 = 1.4 * square(var);      // OK, may be evaluated at run time

double sum(const vector<double>&);  // sum will not modify its argument (§2.2.5)

vector<double> v {1.2, 3.4, 4.5};   // v is not a constant

const double s1 = sum(v);          // OK: evaluated at run time
// constexpr double s2 = sum(v);   // ERROR: sum(v) is not a constant expression
```

  - A constexpr function can be called with non-constant-expression arguments in contexts that do not require constant expressions, so that we don’t have to define essentially the same function twice:
    - Once for compile-time evaluation
    - Once for runtime evaluation

```cpp
constexpr int square(int x) {
    return x * x;
}

int var = 5;

constexpr int a = square(3);  // Compile-time evaluation
int b = square(var);          // Runtime evaluation (allowed)

Here:
- `square(3)` → evaluated at compile time
- `square(var)` → evaluated at runtime

The same function works in both contexts.
```
---

**Enumerations**

By default, an enum class has only assignment, initialization, and comparisons (e.g., == and <;) defined. However, an enumeration is a user-defined type so we can define operators for it

```cpp
enum class Color { red, blue , green };
enum class Traffic_light { green, yellow, red };

Note that enumerators (e.g., red) are in the scope of their enum class, so that they can be used repeatedly in different enum classes without confusion. For example, Color::red is Color’s red which is different from Traffic_light::red.

Color x = red; // error : which red?
Color y = Traffic_light::red; // error : that red is not a Color
Color z = Color::red; // OK

int i = Color::red; // error : Color ::red is not an int
Color c = 2; // error : 2 is not a Color
```

If you don’t want to explicitly qualify enumerator names and want enumerator values to be ints (without the need for an explicit conversion), you can remove the class from enum class to get a ‘‘plain enum’’

**Namespaces**

A mechanism for expressing that some declarations belong together and that their names shouldn’t clash with other names.


**Exceptions**

Exceptions report errors found at run time.

```CPP
try { // exceptions here are handled by the handler defined below
  vec[vec.siz e()] = 7; // try to access beyond the end of v
}
catch (out_of_rang e) { // oops: out_of_range error
// ... handle range error ...
}
//
```

**Invariants**

A statement of what is assumed to be true for a class is called a class invariant, or simply an invariant. For example size of vector should not be -ive. Verify invariant and throw exception from the class.

**Static Assertions**

Static assertion checks for errors at compile time. The static_assert mechanism can be used for anything that can be expressed in terms of constant expressions. The most important uses of static_assert come when we make assertions about types used as parameters in generic programming.

```CPP
constexpr double C = 299792.458;
double speed = 10;
static_assert(speed<C,"can't go that fast"); // error : speed must be a constant

static_assert(A,S) prints S as a compiler error message if A is not true.
```

### Abstraction Mechanisms ###

**Classes**

A class is a user-defined type provided to represent a concept, idea, entity, in the code of a program.

_Concrete classes_: Fully implemented classes that can be instantiated and directly used to create objects.

_Abstract classes_: Classes containing at least one pure virtual function (=0), cannot be instantiated directly.

_Classes in class hierarchies_: Related classes organized via inheritance, enabling polymorphism, specialization, and shared interface behavior. A class hierarchy offers two kinds of benefits
  - Interface inheritance
  - Implementation inheritance

**Container**

A container is an object holding a collection of elements.

**Virtual Functions**

A *virtual function* is a member function declared using the `virtual` keyword  that enables *runtime polymorphism*. It allows a derived class to override a base class function, and ensures the correct function is called based on the *actual object type*, not the pointer type.

<img width="800" height="400" alt="image" src="https://github.com/user-attachments/assets/92530c04-5b73-4e34-8196-b1c0448f429a" />

```CPP

Derived2 inherits Derived1. Derived1 inherits  Base

Base* ptr3 = new Derived2();
```
**Copy**

- By default, objects can be copied. This is true for objects of user-defined types as well as for builtin
types. The default meaning of copy is memberwise copy: copy each member.

- Copying of an object of a class is defined by two members: a copy constructor and a copy assignment.

- The name *this* is predefined in a member function and points to the object for which the member
function is called.

- A copy constructor and a copy assignment for a class X are typically declared to take an argument
of type const X&.

```CPP
ClassName(const ClassName& other);
```

**Move**

- A move operation is applied when an rvalue reference is used as an initializer or as the righthand
side of an assignment. It transfer the ownership.

- A move constructor does not take a const argument: after all, a move constructor is supposed to
remove the value from its argument. A move assignment is defined similarly. 

```CPP
ClassName(ClassName&& other);
```
- The && means ‘‘rvalue reference’’ and is a reference to which we can bind an rvalue. An rvalue is – to a first approximation – a value that you can’t assign to, such as an integer returned by a function call, and an rvalue reference is a reference to something that nobody else can assign to.

- If move constructor is not noexcept, STL containers (like std::vector) may use copy instead of move during reallocation.

- If you define Destructor and do not define move constructor, compiler only allow copy. Hence,performance drop.
- If you define copy-constructor and do not define move constructor, compiler only allow copy. Hence,performance drop.

```CPP
#include <iostream>
#include <cstring>

class Buffer {
private:
    char* data;
    size_t size;

public:
    // 1️⃣ Constructor
    Buffer(size_t s = 0) : size(s), data(s ? new char[s] : nullptr) {
        std::cout << "Constructor\n";
    }

    // 2️⃣ Destructor
    ~Buffer() {
        std::cout << "Destructor\n";
        delete[] data;
    }

    // 3️⃣ Copy Constructor
    Buffer(const Buffer& other) : size(other.size),
        data(other.size ? new char[other.size] : nullptr) {
        std::cout << "Copy Constructor\n";
        if (data)
            std::memcpy(data, other.data, size);
    }

    // 4️⃣ Copy Assignment
    Buffer& operator=(const Buffer& other) {
        std::cout << "Copy Assignment\n";
        if (this == &other)
            return *this;

        delete[] data;
        size = other.size;
        data = other.size ? new char[other.size] : nullptr;
        if (data)
            std::memcpy(data, other.data, size);

        return *this;
    }

    // 5️⃣ Move Constructor
    Buffer(Buffer&& other) noexcept
        : data(other.data), size(other.size) {
        std::cout << "Move Constructor\n";
        other.data = nullptr;
        other.size = 0;
    }

    // 6️⃣ Move Assignment
    Buffer& operator=(Buffer&& other) noexcept {
        std::cout << "Move Assignment\n";
        if (this == &other)
            return *this;

        delete[] data;

        data = other.data;
        size = other.size;

        other.data = nullptr;
        other.size = 0;

        return *this;
    }
};

```

**Suppressing Operations**

Using the default copy or move for a class in a hierarchy is typically a disaster: given only a pointer
to a base, we simply don’t know what members the derived class has, so we can’t know how to copy them. The =delete mechanism is general, that is, it can be used to suppress any operation.

```CPP
class Shape {
public:
  Shape(const Shape&) =delete; // no copy operations
  Shape& operator=(const Shape&) =delete;
  Shape(Shape&&) =delete; // no move operations
  Shape& operator=(Shape&&) =delete;
  // ˜Shape(); A move operation is not implicitly generated for a class where the user has explicitly declared a destructor.
// ...
};
```

**Templates**

A template is a class or a function that we parameterize with a set of types or values. It supports generic programming.

```CPP
template<typename T>
class Vector {
private:
  T∗ elem; // elem points to an array of sz elements of type T
  int sz;
public:
  Vector(int s); // constructor: establish invariant, acquire resources
  ˜Vector() { delete[] elem; } // destructor: release resources

...
};

template<typename T>
Vector<T>::Vector(int s)
{
if (s<0) throw Negative_siz e{};
elem = new T[s];
sz = s;
}
It is C++’s version of the mathematical ‘‘for all T’’ or more precisely ‘‘for all types T.’’

Vector<char> vc(200); // vector of 200 characters
Vector<string> vs(17); // vector of 17 strings
```

**Function Objects**

One particularly useful kind of template is the function object (sometimes called a functor), which
is used to define objects that can be called like functions.

```CPP
template<typename T>
class Less_than {
  const T val; // value to compare against
public:
  Less_than(const T& v) :val(v) { }
  bool operator()(const T& x) const { return x<val; } // call operator
};
```
The function called operator() implements the ‘‘function call,’’ ‘‘call,’’ or ‘‘application’’ operator ().
We can define named variables of type Less_than for some argument type:

```CPP
Less_than<int> lti {42}; // lti(i) will compare i to 42 using < (i<42)
Less_than<string> lts {"Backus"}; // lts(s) will compare s to "Backus" using < (s<"Backus")
```

**Variadic Templates**

A template can be defined to accept an arbitrary number of arguments of arbitrary types. Such a template is called a variadic template. For example:

```CPP
template<typename T, typename ... Tail>
void f(T head, Tail... tail)
{
g(head); // do something to head
f(tail...); // try again with tail
}

template<typename T>
void g(T x) { cout << x << " "; }
void f() { } // do nothing

```

**Aliases**

Introduce a synonym for a type or a template.

```CPP
using size_t = unsigned int;
```




