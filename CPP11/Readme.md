# CPP11 #

Reference: The C++ Programming Language Fourth Edition Bjarne Stroustrup and Internet(GFG etc.).

The C++ language features most directly support four programming styles:

_Procedural programming_

_Data abstraction_: This is programming focused on the design of interfaces, hiding implementation details in general and representations in particular. The facilities for defining classes with private implementation details, constructors and destructors, and associated operations directly support this. The notion of an abstract class provides direct support for complete data hiding.

_Object-oriented programming_: This is programming focused on the design, implementation, and use of class hierarchies. Class hierarchies provide run-time polymorphism and encapsulation.

_Generic programming_: This is programming focused on the design, implementation, and use of general algorithms. Templates provide (compiletime) parametric polymorphism.

## Part 1: Introduction ##

### The Basics ###

**Constness**

Constness improves the performance.

_const_: I promise not to change this value

_constexpr_: To be evaluated at compile time
  - For a function to be usable in a constant expression, that is, in an expression that will be evaluated by the compiler, it must be defined constexpr.
  - A constexpr function can be used for non-constant arguments, but when that is done the result is not a constant expression.

The language requires constant expressions for array sizes, case labels, and template value arguments.
If initialization is done at compile time, there can be no data races on that object in a multi-threaded system.
Usually, constexpr is a better choice than const for defining simple constants, but constexpr is new in C++11, so older code tends to use const. In many cases, enumerators  are another
alternative to consts.

A const differs from a constexpr in that it can be initialized by something that is not a constant expression; in that case, the const cannot be used as a constant expression.

```cpp
char ∗const cp; // const pointer to char
char const∗pc; //pointer to const char
const char∗ pc2; //pointer to const char

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

A class with a constexpr constructor is called a `literal type`. To be simple enough to be constexpr, a constructor must have an empty body and all members must be initialized by potentially constant expressions.

```CPP
struct Point {
  int x,y,z;
  constexpr Point up(int d) { return {x,y,z+d}; }
  constexpr Point move(int dx, int dy) { return {x+dx,y+dy}; }
  // ...
};

constexpr Point xy{0,sqrt(2)}; // error : sqrt(2) is not a constant expression
```

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

Introduce a synonym for a type or a template. The _t suffix is conventional for aliases (‘‘typedefs’’).

```CPP
using size_t = unsigned int;
typedef int int32_t;

```
### Container and alogorithms ###

**I/O of User-Defined Types**


```CPP
struct Entry {
  string name;
  int number;
};
```

We can define a simple output operator to write an Entry using a {"name",number} format similar to the one we use for initialization in code:

```CPP
ostream& operator<<(ostream& os, const Entry& e)
{
  return os << "{\"" << e.name << "\", " << e.number << "}";
}
```
A user-defined output operator takes its output stream (by reference) as its first argument and returns it as its result.

The corresponding input operator is more complicated because it has to check for correct formatting and deal with errors:

```CPP
istream& operator>>(istream& is, Entry& e)
// read { "name" , number } pair. Note: for matted with { " " , and }
{
  char c, c2;
  if (is>>c && c=='{' && is>>c2 && c2=='"') { // star t with a { "
    string name; // the default value of a string is the empty string: ""
    while (is.get(c) && c!='"') // anything before a " is part of the name
    name+=c;
      if (is>>c && c==',') {
      int number = 0;
        if (is>>number>>c && c=='}') { // read the number and a }
        e = {name ,number}; // assign to the entry
        return is;
        }
    }
  }
  is.setf(ios_base::failbit); // register the failure in the stream
  return is;
}
```
An input operation returns a reference to its istream which can be used to test if the operation succeeded.
The is>>c skips whitespace by default, but is.g et(c) does not, so that this Entr y-input operator ignores (skips) whitespace outside the name string, but not within it.

**Container**

- *vector* : A vector is a sequence of elements of a given type. The elements are stored contiguously in memory. Indexing starts at 0. size() gives the number of elements
- *list* : A doubly-linked list. We use a list for sequences where we want to insert and delete elements without moving other elements.
- *map* : The standard library offers a search tree (a redblack tree) called map. It is implemented as a balanced binary tree. The standard-library map is a container of pairs of values optimized for lookup. When indexed by a value of its first type (called the key), a map returns the corresponding value of the second type (called the value or the mapped type). The cost of a map lookup is O(log(n)) where n is the number of elements in the map.
- *unordered_map* : hashed containers are referred to as ‘‘unordered’’ because they don’t require an ordering function.  we can do better than map by using a hashed lookup rather than comparison using an ordering function, such as <.

  <img width="535" height="257" alt="image" src="https://github.com/user-attachments/assets/29cab7a3-cc09-40a7-8d1b-31b4e11e5fad" />

The unordered containers are optimized for lookup with a key (often a string); in other words, they are implemented using hash tables.

**Algorithms**

An algorithm is a finite set of rules which gives a sequence of operations for solving a specific set of problems [and] has five important features: Finiteness ... Definiteness ...
Input ... Output ... Effectiveness.

<img width="551" height="293" alt="image" src="https://github.com/user-attachments/assets/cb6c3929-765a-4a90-8ec5-3859f2920c70" />

**Predicate**

**Iterator**


**stream iterator**

<img width="546" height="245" alt="image" src="https://github.com/user-attachments/assets/ec69ad33-6987-4660-b437-ddb987dd0fcd" />


Every standard-library container provides the functions begin() and end(), which return an iterator to the first and to one-past-the-last element, respectively.

## Concurrency and Utilities ##

**Resource Acquisition Is Initialization - RAII**

```CPP
mutex m; // used to protect access to shared data
// ...
void f()
{
  unique_lock<mutex> lck {m}; // acquire the mutex m
  // ... manipulate shared data ...
}
```
A thread will not proceed until lck’s constructor has acquired its mutex, m (§5.3.4). The corresponding destructor releases the resource. So, in this example, unique_lock’s destructor releases the mutex when the thread of control leaves f() (through a return, by ‘‘falling off the end of the function,’’ or through an exception throw).

**unique_ptr**
- unique_ptr to represent unique ownership.
- unique_ptr ensures that its object is properly destroyed whichever way we exit its scope (by throwing an exception, by executing return, or by ‘‘falling off the end’’).
- uses include passing free-store allocated objects in and out of functions

```CPP
unique_ptr<X> sp {new X};
```

**shared_ptr**
- The shared_ptrs for an object share ownership of an object and that object is destroyed when the last of its shared_ptrs is destroyed.
- Use shared_ptr only if you actually need shared ownership.

```CPP
shared_ptr<fstream> fp {new fstream(name ,mode)};
```

- Implement a complete ‘‘no naked new’’ policy
- When we share an object, we need pointers (or references) to refer to the shared object, so a shared_ptr becomes the obvious choice (unless there is an obvious single owner).
- When we refer to a polymorphic object, we need a pointer (or a reference) because we don’t know the exact type of the object referred to or even its size), so a unique_ptr becomes the
obvious choice.
- A shared polymorphic object typically requires shared_ptrs.

**Tasks and threads**

```CPP
void f(); // function
struct F { // function object
  void operator()(); // F’s call operator
};
void user()
{
  thread t1 {f}; // f() executes in separate thread
  thread t2 {F()}; // F()() executes in separate thread
  t1.join(); // wait for t1
  t2.join(); // wait for t2
}
```

The join()s ensure that we don’t exit user() until the threads have completed. To ‘‘join’’ means to ‘‘wait for the thread to terminate.’’

**Passing Arguments**

```CPP

void f(vector<double>& v); // function do something with v

struct F { // function object: do something with v
  vector<double>& v;
  F(vector<double>& vv) :v{vv} { }
  void operator()(); // application operator ;
};

int main()
{
  vector<double> some_vec {1,2,3,4,5,6,7,8,9};
  vector<double> vec2 {10,11,12,13,14};
  thread t1 {f,some_vec}; // f(some_vec) executes in a separate thread
  thread t2 {F{vec2}}; // F(vec2)() executes in a separate thread
  t1.join();
  t2.join();
}
```

**Returning Results**

- pass the input data by const reference and to pass the location of a place to deposit the result as a separate argument.

```CPP
void f(const vector<double>& v, double∗ res);// take input from v; place result in *res
```

**Sharing Data**



## Part 2: Basic Facilities ##

### Type annd Declarations ###

**Character Literals**

A character literal is a single character enclosed in single quotes, for example, 'a' and '0'. The type of a character literal is char.
<img width="355" height="275" alt="image" src="https://github.com/user-attachments/assets/34113d59-8928-4823-9af9-81bb16418aab" />


**Alignment**

The alignof() operator returns the alignment of its argument expression.

```CPP
auto ac = alignof('c'); // the alignment of a char
auto ai = alignof(1); // the alignment of an int
auto ad = alignof(2.0); // the alignment of a double
```

alignas(T) means ‘‘align just like a T.’’

```CPP
void user(const vector<X>& vx)
{
  alignas(X) buffer[bufmax]; // uninitialized
}
```

**Keywords**

<img width="552" height="292" alt="image" src="https://github.com/user-attachments/assets/6db8228c-e356-4a17-b1a0-d739ed489e9d" />

In addition, the word expor t is reserved for future use.

**Scope**

- Local scope
- Class scope
- Namespace scope
- Global scope
- Statement scope
- Function scope

**Initialization**

Initialization using {}, list initialization, does not allow narrowing. That is:

• An integer cannot be converted to another integer that cannot hold its value. For example, char to int is allowed, but not int to char.
• A floating-point value cannot be converted to another floating-point type that cannot hold its value. For example, float to double is allowed, but not double to float.
• A floating-point value cannot be converted to an integer type.
• An integer value cannot be converted to a floating-point type.

```CPP
int x2 = val; // if val==7.9, x2 becomes 7 ...  c-style
int x3 {val}; // error : possible truncation --- c++11 style, strongly recommended

char c4 {24}; // OK: 24 can be represented exactly as a char
char c5 {264}; // error (assuming 8-bit chars): 264 cannot be represented as a char
```

If no initializer is specified, a global , namespace, local static, or static member (collectively called static objects) is initialized to {} of the appropriate type.

```CPP
void f()
{
  int x; // x does not have a well-defined value
  int y {}; // y becomes 0
}
```

A member of an array or a class is default initialized if the array or structure is.

**Deducing a Type**

*auto*
auto for deducing a type of an object from its initializer; the type can be the type of a variable, a const, or a constexpr.

```CPP
auto a3 = 123; // the type of a3 is ‘‘int’’

for (auto p = arg.begin(); p!=arg.end(); ++p)

for (const auto& x : v) { // x is a const int&

```

```CPP

char v1 {12345}; // error : narrowing
int v2 {'c'}; // fine: implicit char->int conversion
T v3 {f()}; // works if and only if the type of f() can be implicitly converted to a T

auto v1 = 12345; // v1 is an int
auto v2 = 'c'; // v2 is a char
auto v3 = f(); // v3 is of some appropriate type

auto v1 {12345}; // v1 is a list of int
auto v2 {'c'}; // v2 is a list of char
auto v3 {f()}; // v3 is a list of some appropriate type

auto x0 {}; // error : cannot deduce a type
auto x1 {1}; // list of int with one element
auto x2 {1,2}; // list of int with two elements
auto x3 {1,2,3}; // list of int with three elements
```

*decltype()*
decltype(expr) for deducing the type of something that is not a simple initializer, such as the return type for a function or the type of a class member.
decltype(expr) is the declared type of expr. Used in generic programming

```CPP
template<class T, class U>
auto operator+(const Matrix<T>& a, const Matrix<U>& b) −> Matrix<decltype(T{}+U{})>;


template<class T, class U>
auto operator+(const Matrix<T>& a, const Matrix<U>& b) −> Matrix<decltype(T{}+U{})>
{
  Matrix<decltype(T{}+U{})> res;
  for (int i=0; i!=a.rows(); ++i)
  for (int j=0; j!=a.cols(); ++j)
  res(i,j) += a(i,j) + b(i,j);
  return res;
}
```

**lvalue and rvalue**

**Lifetimes of Objects**

- Automatic
- Static : Objects declared in global or namespace scope (§6.3.4) and statics declared in functions  or classes  are created and initialized once (only) and ‘‘live’’ until
the program terminates. A static object has the same address throughout the life of a program execution.
- Free store
- Temporary objects
- Thread-local

### Pointer Array and Reference ###

**References**

- You access a reference with exactly the same syntax as the name of an object.
- A reference always refers to the object to which it was initialized.
- There is no ‘‘null reference,’’ and we may assume that a reference refers to an object
- The main use of references is for specifying arguments and return values for functions in general and for overloaded operators in particular

To reflect the lvalue/rvalue and const/non-const distinctions, there are three kinds of references:
• lvalue references: to refer to objects whose value we want to change
• const references: to refer to objects whose value we do not want to change (e.g., a constant)
• rvalue references: to refer to objects whose value we do not need to preserve after we have used it (e.g., a temporary) Collectively, they are called references. The first two are both called lvalue references.

*Lvalue References*

In a type name, the notation X& means ‘‘reference to X.’’ It is used for references to lvalues, so it is often called an lvalue reference.

```CPP
int var = 1;
int& r1 {var}; // OK: r1 initialized
int& r2; // error : initializer missing
extern int& r3; // OK: r3 initialized elsewhere

int& rr {var}; ++rr does not increment the reference rr; rather, ++ is applied to the int to which rr refers, that is, to var.

int∗ pp = &rr; // pp points to var, To get a pointer to the object denoted by a reference rr, we can write &rr. 
```

A temporary created to hold a reference initializer persists until the end of its reference’s scope.
```CPP

double& dr = 1; // error : lvalue needed
const double& cdr {1}; // OK

The interpretation of this last initialization might be:

double temp = double{1}; // first create a temporar y with the right value
const double& cdr {temp}; // then use the temporar y as the initializer for cdr
```

• A non-const lvalue reference refers to an object, to which the user of the reference can write.
• Aconst lvalue reference refers to a constant, which is immutable from the point of view of the user of the reference.

*Rvalue References*

• An rvalue reference refers to a temporary object, which the user of the reference can (and typically will) modify, assuming that the object will never be used again.
• An rvalue reference can bind to an rvalue, but not to an lvalue.

```CPP
string var {"Cambridge"};
string f();
string& r1 {var}; // lvalue reference, bind r1 to var (an lvalue)
string& r2 {f()}; // lvalue reference, error : f() is an rvalue
string& r3 {"Princeton"}; // lvalue reference, error : cannot bind to temporary
string&& rr1 {f()}; // rvalue reference, fine: bind rr1 to rvalue (a temporar y)
string&& rr2 {var}; // rvalue reference, error : var is an lvalue
string&& rr3 {"Oxford"}; // rr3 refers to a temporar y holding "Oxford"
const string cr1& {"Harvard"}; // OK: make temporar y and bind to cr1
```

The && declarator operator means ‘‘rvalue reference.’’ We do not use const rvalue references; most
of the benefits from using rvalue references involve writing to the object to which it refers. Both a
const lvalue reference and an rvalue reference can bind to an rvalue. However, the purposes will be
fundamentally different:
• We use rvalue references to implement a ‘‘destructive read’’ for optimization of what would otherwise have required a copy.
• We use a const lvalue reference to prevent modification of an argument.

An object referred to by an rvalue reference is accessed exactly like an object referred to by an lvalue reference or an ordinary variable name.

std::move(x) does not move x (it simply produces an rvalue reference to x)


*References to References*

It you take a reference to a reference to a type, you get a reference to that type, rather than some kind of special reference to reference type.

```CPP
using rr_i = int&&;
using lr_i = int&;
using rr_rr_i = rr_i&&; // ‘‘int && &&’’ is an int&&
using lr_rr_i = rr_i&; // ‘‘int && &’’ is an int&
using rr_lr_i = lr_i&&; // ‘‘int & &&’’ is an int&
using lr_lr_i = lr_i&; // ‘‘int & &’’ is an int&
```
lvalue reference always wins. The syntax does not allow *int && & r = i;*


*Pointers and References*

****TBD****

### Structures, Unions, and Enumerations ###

• Astruct (a structure) is a sequence of elements (called members) of arbitrary types.
• Aunion is a struct that holds the value of just one of its elements at any one time.
• Anenum (an enumeration) is a type with a set of named constants (called enumerators).
• enum class (a scoped enumeration) is an enum where the enumerators are within the scope of the enumeration and no implicit conversions to other types are provided.

**Structures**

- Variables of struct types can be initialized using the {} notation

```CPP
struct Readout {
  char hour; // [0:23]
  int value;
  char seq; // sequence mark ['a':'z']
};

sizeof(Readout) is 12.

struct Readout {
  int value;
  char hour; // [0:23]
  char seq; // sequence mark ['a':'z']
};

sizeof(Readout)==8.

```

```CPP
struct No_good {
  No_good member; // error : recursive definition
};
```
This is an error because the compiler is not able to determine the size of No_good.

It is possible to declare a struct and a non-struct with the same name in the same scope. A struct is simply a class where the members are public by default.
```CPP
struct stat { /* ... */ };
int stat(char∗ name, struct stat∗ buf);
```

**Bitfield**

A field is often called a bit-field. A member is defined to be a field by specifying the number of bits it is to occupy. Unnamed fields are allowed.

```CPP
struct PPN { // R6000 Physical Page Number
  unsigned int PFN : 22; // Page Frame Number
  int : 3; // unused
  unsigned int CCA : 3; // Cache Coherency Algorithm
  bool nonreachable : 1;
  bool dirty : 1;
  bool valid : 1;
  bool global : 1;
};
```

**Union**

A union is a struct in which all members are allocated at the same address so that the union occupies only as much space as its largest member.

The members s and i can never be used at the same time, so space is wasted. It can be easily recovered by specifying that both should be members of a union, like this:

```CPP
union Value {
char∗ s;
int i;
};
```

The language doesn’t keep track of which kind of value is held by a union,

**Unions and Classes**

[1] A union cannot have virtual functions.
[2] A union cannot have members of reference type.
[3] A union cannot have base classes.
[4] If a union has a member with a user-defined constructor, a copy operation, a move operation, or a destructor, then that special function is deleted for that union; that is, it cannot be used for an object of the union type.
[5] At most one member of a union can have an in-class initializer.
[6] A union cannot be used as a base class.

The declaration of anonymous union is not named. That makes it an anonymous union. An anonymous union is an object, not a type, and its members can be accessed without
mentioning an object name. That means that we can use members of an anonymous union exactly as we use other members of a class – as long as we remember that union members really can be
used only one at a time.



**Enumerations**

An enumeration is a type that can hold a set of integer values specified by the user.

```CPP
enum class Color { red, green, blue };
```

There are two kinds of enumerations:
[1] enum classes, for which the enumerator names (e.g., red) are local to the enum and their values do not implicitly convert to other types
[2] ‘‘Plain enums,’’ for which the enumerator names are in the same scope as the enum and their values implicitly convert to integers
In general, prefer the enum classes because they cause fewer surprises.

An enum class is a scoped and strongly typed enumeration. enums of different types can not be assigned.

Note that the enumerators present in multiple enums do not clash because each is in the scope of its own enum class.

enum class Warning : int { green, yellow, orang e, red }; // sizeof(War ning)==sizeof(int)
If we considered that too wasteful of space, we could instead use a char:
enum class Warning : char { green, yellow, orang e, red }; // sizeof(War ning)==1
By default, enumerator values are assigned increasing from 0.

Declaring a variable Warning instead of plain int can give both the user and the compiler a hint as to the intended use. Compiler might issues an warning for missing enum. For example:

```CPP
void f(Warning key)
{
switch (key) {
  case Warning::green:
    // do something
    break;
  case Warning::orang e:
    // do something
    break;
  case Warning::red:
    // do something
    break;
  }
}
```

It is possible to declare an enum class without defining it  until later. For example:

```CPP
enum class Color_code : char; // declaration
void foobar(Color_code∗ p); // use of declaration
// ...
enum class Color_code : char { // definition
red, yellow, green, blue
};
```

The enumerators of a plain enum are exported into the enum’s scope, and they implicitly convert to values of some integer type

```CPP
enum Traffic_light { red, yellow, green };
enum Warning { green, yellow, orang e, red }; // fire alert lev els
// error : two definitions of yellow (to the same value)
```

A plain enum can be unnamed. For example:
```CPP
enum { arrow_up=1, arrow_down, arrow_sideways };
```
We use that when all we need is a set of integer constants, rather than a type to use for variables.

*QUESTION*: Difference between class enum, plain enum and unnamed enums.

## Statements ##

- The expression in the case labels of switch must be a constant expression of integral or enumeration type.
- It is possible, and common, to declare variables within the block of a switch-statement. However, it is not possible to bypass an initialization. For example:

```CPP
void f(int i)
{
  switch (i) {
    case 0:
    int x; // uninitialized
    int y = 3; // error : declaration can be bypassed (explicitly initialized)
    string s; // error : declaration can be bypassed (implicitly initialized)
    case 1:
    ++x; //error : use of uninitialized object
    ++y;
    s = "nasty!";
  }
}
```

## Expressions ##

The **integral promotions** are:
• Achar, signed char, unsigned char, short int, or unsigned short int is converted to an int if int can represent all the values of the source type; otherwise, it is converted to an unsigned int.
• Achar16_t, char32_t, wchar_t, or a plain enumeration type is converted to the first of the following types that can represent all the values of its underlying type: int, unsigned int, long, unsigned long, or unsigned long long.
• A bit-field is converted to an int if int can represent all the values of the bit-field; otherwise, it is converted to unsigned int if unsigned int can represent all the values of the bit-field. Otherwise, no integral promotion applies to it.
• Abool is converted to an int; false becomes 0 and true becomes 1.

**Arithmetic Conversions**

[1] If either operand is of type long double, the other is converted to long double.
• Otherwise, if either operand is double, the other is converted to double.
• Otherwise, if either operand is float, the other is converted to float.
• Otherwise, integral promotions (§10.5.1) are performed on both operands.
[2] Otherwise, if either operand is unsigned long long, the other is converted to unsigned long long.
• Otherwise, if one operand is a long long int and the other is an unsigned long int, then if a long long int can represent all the values of an unsigned long int, the unsigned long
int is converted to a long long int; otherwise, both operands are converted to unsigned long long int. Otherwise, if either operand is unsigned long long, the other is converted
to unsigned long long.
• Otherwise, if one operand is a long int and the other is an unsigned int, then if a long int can represent all the values of an unsigned int, the unsigned int is converted to a
long int; otherwise, both operands are converted to unsigned long int.
• Otherwise, if either operand is long, the other is converted to long.
• Otherwise, if either operand is unsigned, the other is converted to unsigned.
• Otherwise, both operands are int.

## Select Operation ##

**Memory Management**

The main problems with free store are:
• Leaked objects: People use new and then forget to delete the allocated object.
• Premature deletion: People delete an object that they hav e some other pointer to and later use that other pointer.
• Double deletion: An object is deleted twice, invoking its destructor (if any) twice.

The rule of thumb for the use of new and delete is ‘‘no naked news’’; that is, new belongs in constructors and similar operations, delete belongs in destructors, and together they provide a coherent memory management strategy.

Applying delete[] to the null pointer has no effect.

When operator new needs to allocate space for an object, it calls operator new() to allocate a suitable number of bytes. Similarly, when operator new needs to allocate space for an array, it calls operator new[](). The standard implementations of operator new() and operator new[]() do not initialize the memory returned.

```CPP
void∗ operator new(siz e_t); // allocate space for individual object
void operator delete(void∗ p); // if (p) deallocate space allocated using operator new()
void∗ operator new[](siz e_t); // allocate space for array
void operator delete[](void∗ p); // if (p) deallocate space allocated using operator new[]()
```

**Overloading new**

```CPP
void∗ operator new(siz e_t, void∗ p) { return p; } // explicit `placement operator`
void∗ buf = reinterpret_cast<void∗>(0xF00F); // significant address
X∗ p2 = new(buf) X; // construct an X at buf;
// invokes: operator new(sizeof(X),buf)

void∗ operator new (siz e_t sz, void∗ p) noexcept; // place object of size sz at p
void∗ operator new[](siz e_t sz, void∗ p) noexcept; // place object of size sz at p
void operator delete (void∗ p, void∗) noexcept; // if (p) make *p invalid `placement delete`
void operator delete[](void∗ p, void∗) noexcept; // if (p) make *p invalid
```

**nothrow new**

These operator new functions return nullptr, rather than throwing bad_alloc, if there is not sufficient memory to allocate.

```CPP
void∗ operator new(siz e_t sz, const nothrow_t&) noexcept; // allocate sz bytes;
// return nullptr if allocation failed
void operator delete(void∗ p, const nothrow_t&) noexcept; // deallocate space allocated by new
void∗ operator new[](siz e_t sz, const nothrow_t&) noexcept; // allocate sz bytes;
// return nullptr if allocation failed
void operator delete[](void∗ p, const nothrow_t&) noexcept; // deallocate space allocated by new

int∗ p = new(nothrow) int[n]; // allocate n ints on the free store
```

### List {} ###
TBD

### Lambda ###
TBD

**Explicit Type Conversion**

Construction, using the {} notation, providing type-safe construction of new values (§11.5.1)
• Named conversions, providing conversions of various degrees of nastiness:
  • const_cast for getting write access to something declared const 
  • static_cast for reversing a well-defined implicit conversion
  • reinterpret_cast for changing the meaning of bit patterns
  • dynamic_cast for dynamically checked class hierarchy navigation
• C-style casts, providing any of the named conversions and some combinations of those
• Functional notation, providing a different notation for C-style casts

If rounding is desirable, we can use the standardlibrary function `round()`; it performs ‘‘conventional 4/5 rounding,’’ such as 7.9 to 8 and 7.4 to 7.

`static_cast` converts between related types such as one pointer type to another in the same class hierarchy, an integral type to an enumeration, or a floating-point type to an integral
type. It also does conversions defined by constructors and conversion operators.

`reinterpret_cast` handles conversions between unrelated types such as an integer to a pointer or a pointer to an unrelated pointer type.

`const_cast` converts between types that differ only in const and volatile qualifiers.

`dynamic_cast` does run-time checked conversion of pointers and references into a class hierarchy.

```CPP
static_cast<TYPE *> (var);
reinterpret_cast<TYPE *> (var);
const_cast<TYPE *> (var);
dynamic_cast<TYPE *> (var);


c-stype
(Type) var;
```

Prefer T{v} conversions for well-behaved construction and the named casts (e.g., static_cast) for other conversions.


## Function ##

**Declaration**

• The name of the function; required
• The argument list, which may be empty (); required
• The return type, which may be void and which may be prefix or suffix (using auto); required
• inline, indicating a desire to have function calls implemented by inlining the function body
• constexpr, indicating that it should be possible to evaluate the function at compile time if given constant expressions as arguments
• noexcept, indicating that the function may not throw an exception
• A linkage specification, for example, static 
• [[noreturn]], indicating that the function will not return using the normal call/return mechanism

In addition, a member function may be specified as:
• virtual, indicating that it can be overridden in a derived class
• override, indicating that it must be overriding a virtual function from a base class
• final, indicating that it cannot be overriden in a derived class
• static, indicating that it is not associated with a particular object
• const, indicating that it may not modify its object


• Constructors are technicallly not functions; in particular, they don’t return a value, can initialize bases and members , and can’t have their address taken.
• Destructors can’t be overloaded and can’t have their address taken.
• Function objects are not functions (they are objects) and can’t be overloaded, but their operator()s are functions.
• Lambda expressions are basically a shorthand for defining function objects.

**inline Functions**

- An inline function still has a unique address, and so do static variables of an inline function.
- If an inline function is defined in more than one translation unit (e.g., typically because it was defined in a header;), its definition in the different translation units must be identical
- If you want a guarantee that a value is computed at compile time, declare it constexpr and make sure that all functions used in its evaluation are constexpr.

**constexpr Functions**

- By specifying a function constexpr, we indicate that we want it to be usable in constant expressions if given constant expressions as arguments.
- When constexpr is used in a function definition, it means ‘‘should be usable in a constant expression when given constant expressions as arguments.’’ When used in an object definition, it means ‘‘evaluate the initializer at compile time.’’

```CPP
constexpr int fac(int n)
{
return (n>1) ? n∗fac(n−1) : 1;
}
constexpr int f9 = fac(9); // must be evaluated at compile time
```
 
- Like inline functions, constexpr functions obey the ODR (‘‘one-definition rule’’), so that definitions in the different translation units must be identical.
- A constexpr function allows recursion and conditional expressions.
- By using literal types, constexpr functions can be defined to use user-defined types.

```CPP
struct Rect {
    int w, h;

    constexpr Rect(int w_, int h_) : w(w_), h(h_) {}

    constexpr int area() const {
        return w * h;
    }
};

constexpr Rect r(5, 6);
constexpr int a = r.area();   // computed at compile time

User-defined type behaving like int.
```

A constexpr function cannot have side effects, so writing to nonlocal objects is not possible. However, a constexpr function can refer to nonlocal objects as long as it does not write to them. A constexpr function can take reference arguments. Of course, it cannot write through such references, but const reference parameters are as useful as ever.

It is possible for a constexpr function to return a reference or a pointer. For example:
```CPP
constexpr const int∗ addr(const int& r) { return &r; } // OK


static const int x = 5;
constexpr const int∗ p1 = addr(x); // OK
constexpr int xx = ∗p1; //OK
static int y;
constexpr const int∗ p2 = addr(y); // OK
constexpr int yy = ∗y; //error : attempt to read a var iable
constexpr const int∗ tp = addr(5); // error : address of temporary

```
### Conditional Evaluation of constexpr ###
TBD

**[[noreturn]] Functions**

Placing [[noreturn]] at the start of a function declaration indicates that the function is not
expected to return. For example:

```CPP
[[noreturn]] void exit(int); // exit will never retur n
```

**Argument Passing**
How do we choose among the ways of passing arguments? My rules of thumb are:
[1] Use pass-by-value for small objects.
[2] Use pass-by-const-reference to pass large values that you don’t need to modify.
[3] Return a result as a return value rather than modifying an object through an argument.
[4] Use rvalue references to implement move and forwarding .
[5] Pass a pointer if ‘‘no object’’ is a valid alternative (and represent ‘‘no object’’ by nullptr).
[6] Use pass-by-reference only if you have to.

These three declarations are equivalent and declare the same function.
```CPP
void odd(int∗ p);
void odd(int a[]);
void odd(int buf[1020]);
```

**Macros**

The first rule about macros is: don’t use them unless you have to. Almost ev ery macro demonstrates a flaw in the programming language, in the program, or in the programmer.
Use g macros only for conditional compilation and in particular for include guards.

If you must use a macro, use the scope resolution operator, ::, when referring to global names  and enclose occurrences of a macro argument name in parentheses whenever possible. For
example:
#define MIN(a,b) (((a)<(b))?(a):(b))

The auto, constexpr, const, decltype, enum, inline, lambda expressions, namespace, and template mechanisms can be used as better-behaved alternatives to many traditional uses of preprocessor constructs.

A string can be created by concatenating two strings using the ## macro operator. For example:
```CPP
#define NAME2(a,b) a##b
int NAME2(hack,cah)();
will produce
int hackcah();
```

A single # before a parameter name in a replacement string means a string containing the macro argument. For example:

```CPP
#define printx(x) cout << #x " = " << x << '\n';
int a = 7;
string str = "asdf";
void f()
{
printx(a); // cout << "a" << " = " << a << '\n';
printx(str); // cout << "str" << " = " << str << '\n';
}
```

`Conditional Compilation`
#ifdef IDENTIFIER

`Predefined Macros`

A few macros are predefined by the compiler:
• __cplusplus: defined in a C++ compilation (and not in a C compilation). Its value is 201103L in a C++11 program; previous C++ standards have lower values.
• __DATE__: date in ‘‘yyyy:mm:dd’’ format.
• __TIME__: time in ‘‘hh:mm:ss’’ format.
• __FILE__: name of current source file.
• __LINE__: source line number within the current source file.
• __FUNC__: an implementation-defined C-style string naming the current function.
• __STDC_HOSTED__: 1 if the implementation is hosted ; otherwise 0.

In addition, a few macros are conditionally defined by the implementation:
• __STDC__: defined in a C compilation (and not in a C++ compilation)
• __STDC_MB_MIGHT_NEQ_WC__: 1 if, in the encoding for wchar_t, a member of the basic character set might have a code value that differs from its value as an ordinary character
literal
• __STDCPP_STRICT_POINTER_SAFETY__: 1 if the implementation has strict pointer safety; otherwise undefined.
• __STDCPP_THREADS__: 1 if a program can have more than one thread of execution; otherwise undefined.

`Pragmas`


## Exception Handling ##

## Namespaces ##

## Source File and Programs ##
