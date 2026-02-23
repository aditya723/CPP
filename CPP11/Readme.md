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

### Concurrency and Utilities ###

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

### Statements ###

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

### Expressions ###

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

### Select Operation ###

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

#### List {} ####
TBD

#### Lambda ####
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


### Function ###

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

A branch of a conditional expression that is not taken in a constexpr function is not evaluated. This implies that a branch not taken can require run-time evaluation.

```CPP
constexpr int check(int i)
{
  return (low<=i && i<high) ? i : throw out_of_rang e();
}
constexpr int low = 0;
constexpr int high = 99;
// ...
constexpr int val = check(f(x,y,z));
```
f(x,y,z) computes some implementation-dependent value ,hence check() will be computed at run-time.

**[[noreturn]] Functions**

Placing [[noreturn]] at the start of a function declaration indicates that the function is not
expected to return. For example:

```CPP
[[noreturn]] void exit(int); // exit will never retur n
```
**Pointer to Function**
- dereferencing a pointer to function using `∗` is optional. Similarly, using `&` to get the address of a function is optional.
- Pointers to functions have argument types declared just like the functions themselves. In pointer assignments, the complete function type must match exactly.
- You can take the address of an overloaded function by assigning to or initializing a pointer to function. In that case, the type of the target is used to select from the set of overloaded functions. For
example:
```CPP
void f(int);
int f(char);
void (∗pf1)(int) = &f; // void f(int)
int (∗pf2)(char) = &f; // int f(char)
void (∗pf3)(char) = &f; // error : no void f(char)
```

It is also possible to take the address of member functions, but a pointer to member function is quite different from a pointer to (nonmember) function.
A pointer to a noexcept function can be declared noexcept. For example:
```CPP
void f(int) noexcept;
void g(int);
void (∗p1)(int) = f; // OK: but we throw away useful infor mation
void (∗p2)(int) noexcept = f; // OK: we preser ve the noexcept infor mation
void (∗p3)(int) noexcept = g; // error : we don’t know that g doesn’t throw
```

A pointer to function must reflect the linkage of a function. Neither linkage specification nor noexcept may appear in type aliases:
```CPP
using Pc = extern "C" void(int); // error : linkage specification in alias
using Pn = void(int) noexcept; // error : noexcept in alias
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

**List Arguments**
TBD

**Default Arguments**
```CPP
  complex(double r ={}, double i ={}) :re{r}, im{i} {} // construct complex from two scalars
```
**Overloaded Functions**

A series of criteria are tried in order:
[1] Exact match; that is, match using no or only trivial conversions (for example, array name to pointer, function name to pointer to function, and T to const T)
[2] Match using promotions; that is, integral promotions (bool to int, char to int, short to int, and their unsigned counterparts; and float to double)
[3] Match using standard conversions (e.g., int to double, double to int, double to long double ,Derived∗ to Base∗, T∗ to void∗, int to unsigned int)
[4] Match using user-defined conversions (e.g., double to complex<double>; )
[5] Match using the ellipsis ... in a function declaration 
[5] Match using narrowing  (int to char etc)

If two matches are found at the highest level where a match is found, the call is rejected as ambiguous.

``CPP
void print(int);
void print(const char∗);
void print(double);
void print(long);
void print(char);
void h(char c, int i, short s, float f)
{
  print(c); // exact match: invoke print(char)
  print(i); // exact match: invoke print(int)
  print(s); // integral promotion: invoke print(int)
  print(f); // float to double promotion: print(double)
  print('a'); // exact match: invoke print(char)
  print(49); // exact match: invoke print(int)
  print(0); // exact match: invoke print(int)
  print("a"); // exact match: invoke print(const char*)
  print(nullptr); // nullptr_t to const char* promotion: invoke print(cost char*)
}
```
- Overload resolution is independent of the order of declaration of the functions considered.
- Function templates are handled by applying the overload resolution rules to the result of specialization based on a set of arguments.
- There are separate rules for overloading when a {}-list is used  and for rvalue reference template arguments
- Return types are not considered in overload resolution. The reason is to keep resolution for an individual operator or function call context-independent.
- Overloading takes place among the members of an overload set. By default, that means the functions of a single scope; functions declared in different non-namespace scopes do not overload
- A base class and a derived class provide different scopes so that overloading between a base class function and a derived class function doesn’t happen by default. For example:

```CPP
struct Base {
  void f(int);
};
struct Derived : Base {
  void f(double);
};
void g(Derived& d)
{
  d.f(1); // call Derived::f(double);
}
```

- When overloading across class scopes or namespace scopes is wanted, usingdeclarations or using-directives can be used . Argument-dependent lookup can also lead to overloading across namespaces.
- In the process of choosing among overloaded functions with two or more arguments, a best match is found for each argument.3. A function that is the best match for one argument and a better or equal match for all other arguments is called. If no such function exists,the call is rejected as ambiguous.

```CPP
int pow(int, int);
double pow(double , double);
complex pow(double , complex);
complex pow(complex, int);
complex pow(complex, complex);

void g()
{
  double d = pow(2.0,2); // error : pow(int(2.0),2) or pow(2.0,double(2))?
}

```
- One can also add an explicit type conversion to resolve a specific call.

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

`Pragmas` is a preprocessor directive used to give special instructions to the compiler. `#pragma once` Prevents multiple inclusion of a header file.
-  #pragma message("Compiling module X") , Print compile-time message

### Exception Handling ###

- A function that cannot cope with a problem throws an exception, hoping that its (direct or indirect) caller can handle the problem. A function that wants to handle a kind of problem indicates that by catching the corresponding exception. An exception is an object thrown to represent the occurrence of an error.
  • A calling component indicates the kinds of failures that it is willing to handle by specifying those exceptions in a catch-clause of a try-block.
  • A called component that cannot complete its assigned task reports its failure to do so by throwing an exception using a throw-expression.

```CPP
void taskmaster()
{
  try {
    auto result = do_task();
    // use result
  }
  catch (Some_error) {
    // failure to do_task: handle problem
  }
}

int do_task()
{
// ...
  if (/* could perfor m the task */)
    return result;
  else
    throw Some_error{};
}
```
- we call an operation exceptionsafe if that operation leaves the program in a valid state when the operation is terminated by throwing an exception.
- 
**terminate and noexcept**

**Finally**

finally() does for a block what the increment part of a for-statement does for the forstatement ; it specifies the final action at the top of a block where it is easy to be seen and where it logically belongs from a specification point of view. It says what is to be done upon exit from a scope, saving the programmer from trying to write code at each of the potentially many places from which the thread of control might exit the scope. People have inv ented ‘‘finally’’ language constructs for writing arbitrary
code to clean up after an exception.


• <cassert>, the standard library provides the assert(A) macro, which checks its assertion, A, at run time if and only if the macro NDEBUG (‘‘not debugging’’) is not defined . If
the assertion fails, the compiler writes out an error message containing the (failed) assertion, the source file name, and the source file line number and terminates the program.
• The language provides static_assert(A,message), which unconditionally checks its assertion, A, at compile time (§2.4.3.3). If the assertion fails, the compiler writes out the message and the compilation fails.

**Throwing and Catching Exceptions**

- We can throw an exception of any type that can be copied or moved.
  ```CPP
class No_copy {
  No_copy(const No_copy&) = delete; // prohibit copying (§17.6.4)
};
class My_error {
// ...
};

void f(int n)
{
  switch (n) {
    case 0: throw My_error{}; // OK
    case 1: throw No_copy{}; // error : can’t copy a No_copy
    case 2: throw My_error; // error : My_error is a type, rather than an object
  }
}
```

- A throw x; initializes a temporary variable of x’s type with x. This temporary may be further copied several times before it is caught: the exception is passed (back) from called function to calling function until a suitable handler is found. The type of the exception is used to select a handler in the catch-clause of some try-block.
- During, stack unwinding, in each scope exited, the destructors are invoked so that every fully constructed object is properly destroyed.
- There is a small standard-library hierarchy of exception types that can be used either directly or as base classes.
- Some functions don’t throw exceptions and some really shouldn’t. To indicate that, we can declare such a function noexcept. 
- It is possible to declare a function to be conditionally noexcept. For example:
```CPP
template<typename T>
void my_fct(T& x) noexcept(Is_pod<T>());
```
The noexcept(Is_pod<T>()) means that My_fct may not throw if the predicate Is_pod<T>() is true but may throw if it is false. The noexcept() operator takes an expression as its argument and returns true if the compiler ‘‘knows’’ that it
cannot throw and false otherwise.

The predicate in a noexcept() specification must be a constant expression. Plain noexcept means noexcept(true).

The noexcept() operator takes an expression as its argument and returns true if the compiler ‘‘knows’’ that it cannot throw and false otherwise. For example:
```CPP
template<typename T>
void call_f(vector<T>& v) noexcept(noexcept(f(v[0]))
{
  for (auto x : v)
    f(x);
  }
}
```
The double mention of noexcept looks a bit odd, but noexcept is not a common operator. The operand of noexcept() is not evaluated, so in the example we do not get a run-time error if we pass call_f() with an empty vector.

A noexcept(expr) operator does not go to heroic lengths to determine whether expr can throw; it simply looks at every operation in expr and if they all have noexcept specifications that evaluate to
true, it returns true. A noexcept(expr) does not look inside definitions of operations used in expr. Conditional noexcept specifications and the noexcept() operator are common and important in standard-library operations that apply to containers. For example

```CPP
template<class T, siz e_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(∗a, ∗b)));
```

```CPP
void f(int) throw(Bad,Worse); // may only throw Bad or Worse exceptions
void g(int) throw(); // may not throw
```
An empty exception specification throw() terminates the program.

**Catching Exceptions**

```CPP
void f()
{
  try {
    throw E{};
  }
  catch(H) {
  // when do we get here?
  }
}
```
The handler is invoked:
[1] If H is the same type as E
[2] If H is an unambiguous public base of E
[3] If H and E are pointer types and [1] or [2] holds for the types to which they refer
[4] If H is a reference and [1] or [2] holds for the type to which H refers

In addition, we can add const to the type used to catch an exception in the same way that we can add it to a function parameter.
The {} in both the try-part and a catch-clause of a try-block are real scopes.

**Rethrow**

A rethrow is indicated by a throw without an operand and rethrow the original exception caught. A rethrow may occur in a catch-clause or in a function called from a catch-clause. If a rethrow is attempted when there is no exception to
rethrow, std::terminate() will be called. 

```CPP
catch (std::exception& err) {
  if (can_handle_it_completely) {
    // ... handle it ...
    return;
  }
  else {
    // ... do what can be done here ...
    throw; // rethrow the exception
  }
}
```

**Catch Every Exception**

```CPP
catch (...) { // handle every exception
```

**Multiple Handlers**

A try-block may have multiple catch-clauses (handlers).

```CPP
void f()
{
  try {
  // ...
  }
  catch (std::ios_base::failure) {
  // ... handle any iostream error (§30.4.1.1) ...
  }
  catch (std::exception& e) {
  // ... handle any standard-librar y exception (§30.4.1.1) ...
  }
  catch (...) {
  // ... handle any other exception (§13.5.2.2) ...
  }
}
```
- if an exception is thrown in a base-or-member initializer, the exception is passed on to whatever inv oked the constructor for the member’s class. So, we can catch exceptions thrown by member constructors.

**Termination**

- Don’t throw an exception while handling an exception. Don’t throw an exception that can’t be caught.

The specific rules for calling terminate() are :
  • When no suitable handler was found for a thrown exception
  • When a noexcept function tries to exit with a throw
  • When a destructor invoked during stack unwinding tries to exit with a throw
  • When code invoked to propagate an exception (e.g., a copy constructor) tries to exit with a throw
  • When someone tries to rethrow (throw;) when there is no current exception being handled
  • When a destructor for a statically allocated or thread-local object tries to exit with a throw
  • When an initializer for a statically allocated or thread-local object tries to exit with a throw
  • When a function invoked as an atexit() function tries to exit with a throw
In such cases, the function std::terminate() is called.

By default, terminate() will call abort(). This default is the correct choice for most users – especially during debugging. If that is not acceptable, the user can provide a terminate
handler function by a call std::set_terminate() from <exception>

```CPP
using terminate_handler = void(∗)(); // from <exception>
[[noreturn]] void my_handler() // a ter minate handler cannot return
{
  // handle termination my way
}
void dangerous() // very!
{
  terminate_handler old = set_terminate(my_handler);
  // ...
  set_terminate(old); // restore the old terminate handler
}
```
Note that abort() indicates abnormal exit from the program. The function exit() can be used to exit a program with a return value that indicates to the surrounding system whether the exit is normal or abnormal.
If you want to ensure cleanup when an otherwise uncaught exception happens, you can add a catch-all handler to main().

If an exception is not caught on a thread, std::terminate() is called.


### Namespaces ###

We can avoid name clashes by separating sets of declarations (e.g., library interfaces) into namespaces. The members of a namespace are in the same scope and can refer to each other without special notation, whereas access from outside the
namespace requires explicit notation. A namespace is a (named) scope. A member can be declared within a namespace definition and defined later using the namespacename::member-name notation.

A using-declaration introduces a synonym into a scope. When used for an overloaded name, a using-declaration applies to all the overloaded versions.
For example:

```CPP
namespace N {
  void f(int);
  void f(string);
};

void g()
{
  using N::f;
  f(789); //N::f(int)
  f("Bruce"); // N::f(string)
}
```
- A using-directive makes names from a namespace available almost as if they had been declared outside their namespace, like , using namespace std.
- When a class member invokes a named function, other members of the same class and its base classes are preferred over functions potentially found based on the argument types (operators follow a different rule).
- A namespace is open; that is, you can add names to it from several separate namespace declarations. For example:

The rules of thumb are:
[1] If some qualification is really common for several names, use a using-directive for that namespace.
[2] If some qualification is common for a particular name from a namespace, use a using-declaration for that name.
[3] If a qualification for a name is uncommon, use explicit qualification to make it clear from where the name comes.
[4] Don’t use explicit qualification for names in the same namespace as the user.

```CPP
namespace A {
  int f(); // now A has member f()
}

namespace A {
  int g(); // now A has two members, f() and g()
}
```

```CPP
namespace X {
  int i, j, k;
}

int k;

void f1()
{
  int i = 0;
  using namespace X; // make names from X accessible
  i++; //local i
  j++; //X::j
  k++; //error : X’s k or the global k?
  ::k++; //the global k
  X::k++; //X’s k
}
void f2()
{
  int i = 0;
  using X::i; // error : i declared twice in f2()
  using X::j;
  using X::k; // hides global k
  i++;
  j++; //X::j
  k++; //X::k
}
```

- A locally declared name (declared either by an ordinary declaration or by a using-declaration) hides nonlocal declarations of the same name, and any illegal overloading of the name is detected at the point of declaration.
- If users give their namespaces short names, the names of different namespaces will clash:
  
```CPP
namespace A {// shor t name, will clash (eventually)
// ...
}
A::String s1 = "Grieg";
A::String s2 = "Nielsen";
However, long namespace names can be impractical in real code.

namespace ATT = American_Telephone_and_Telegraph; // use namespace alias to shorten names:

```

**Namespace Composition**

Combining composition (by using-directives) with selection (by using-declarations) yields the flexibility needed for most real-world examples.

```CPP
namespace Lib2 {
using namespace His_lib; // everything from His_lib
using namespace Her_lib; // everything from Her_lib
using His_lib::String; // resolve potential clash in favor of His_lib
using Her_lib::Vector; // resolve potential clash in favor of Her_lib
using Her_string = Her_lib::String; // rename
template<class T>
  using His_vec = His_lib::Vector<T>; // rename
template<class T>
  class List { /* ... */ }; // additional stuff
// ...
}
There is no general language mechanism for renaming, but for types and templates, we can introduce aliases with using.
```
- Function overloading works across namespaces.
- There is a way of selecting between two versions that simply and obviously guarantees that a user sees exactly one particular version. This is called an `inline namespace`. Here, Popular contains three subnamespaces, each defining a version. The inline specifies that V3_2 is the default meaning of Popular.
  
```CPP
namespace Popular {

  inline namespace V3_2 { // V3_2 provides the default meaning of Popular
  double f(double);
  int f(int);
  template<class T>
  class C { /* ... */ };
  }
  
  namespace V3_0 {
  // ...
  }
  namespace V2_4_2 {
    double f(double);
    template<class T>
    class C { /* ... */ };
  }
}
```
- An unnamed namespace (also called an anonymous namespace) is used to give internal linkage to everything declared inside it. Is visible only within that translation unit (.cpp file). Cannot be accessed from other .cpp files.Avoid Global Symbol Collisions. Replace static at Global Scope

 ```CPP
static int counter = 5;
int glbl = 10; // If two translation unit defines same global , results in linker error

// Each file gets its own private counter.
namespace {
    int counter = 5;
}

namespace {
    int glbl = 5;
}
Each file gets its own private counter.
```
- Use unnamed namespace instead of global static.

### Source File and Programs ###

**Linkage**

A name that can be used in translation units different from the one in which it was defined is said to have `external linkage`. A name that can be referred to only in the translation unit in which it is defined is said to have internal linkage.
Names that a linker does not see, such as the names of local variables, are said to have no linkage.
```CPP
int global; //external linkage
static int x1 = 1; // internal linkage: not accessible from other translation units
const char x2 = 'a'; // internal linkage: not accessible from other translation units
extern const char x3 = 'a'; //external linkage
extern  char x4 = 'a'; //external linkage
``` 
- Combination of external linkage and inlining is banned to make life simpler for compiler writers.
- We keep inline function definitions consistent by putting them into header files. An inline function must be defined identically in every translation unit in which it is used - bad taste!.
- By default, const objects , constexpr objects , type aliases , and anything declared static in a namespace scope have internal linkage. To ensure consistency, place aliases, consts, constexprs, and inlines in header files.
- If you must use global variables, at least restrict their use to a single source file. This restriction can be achieved in one of two ways:
    [1] Place declarations in an unnamed namespace.
    [2] Declare an entity static.

<img width="692" height="380" alt="image" src="https://github.com/user-attachments/assets/d06ae8d3-a1b9-4b03-b837-3080639463e7" />
<img width="616" height="128" alt="image" src="https://github.com/user-attachments/assets/e3a105d3-1f1a-43f7-bf90-4affd4ca36fe" />

<img width="642" height="158" alt="image" src="https://github.com/user-attachments/assets/5bf0ff18-dbc4-4621-8b7d-e001f775567e" />

- Including a header containing such definitions will lead to errors or (in the case of the using-directive) to confusion.
- That is, two definitions of a class, template, or inline function are accepted as examples of the same unique definition if and only if
    [1] they appear in different translation units, and
    [2] they are token-for-token identical, and
    [3] the meanings of those tokens are the same in both translation units.
```CPP
For example:
// file1.cpp:
struct S { int a; char b; };
void f(S∗);
// file2.cpp:
struct S { int a; char b; };
void f(S∗ p) { /* ... */ }
The ODR says that this example is valid and that S refers to the same class in both source files.
```
- Local type aliases and macros can change the meaning of #included declarations:
// s.h:
  struct S { Point a; char b; };

// file1.cpp:
  #define Point int
  #include "s.h"
  // ...

// file2.cpp:
  class Point { /* ... */ };
  #include "s.h"
  // ...

The best defense against this kind of hackery is to make headers as self-contained as possible. For example, if class Point had been declared in the s.h header, the error would have been detected.
A template definition can be #included in sev eral translation units as long as the ODR is adhered to. This applies even to function template definitions and to class templates containing member function definitions.

**extern "C"**
TBD

**Linkage and Pointers to Functions**

```CPP
typedef int (∗FT)(const void∗, const void∗); //FT has C++ linkage
extern "C" {
  typedef int (∗CFT)(const void∗, const void∗); //CFT has C linkage
  void qsort(void∗ p, size_t n, size_t sz, CFT cmp); // cmp has C linkage
}

void isort(void∗ p, size_t n, size_t sz, FT cmp); // cmp has C++ linkage
void xsort(void∗ p, size_t n, size_t sz, CFT cmp); // cmp has C linkage
extern "C" void ysort(void∗ p, size_t n, size_t sz, FT cmp); // cmp has C++ linkage
int compare(const void∗, const void∗); //compare() has C++ linkage
extern "C" int ccmp(const void∗, const void∗); //ccmp() has C linkage

void f(char∗ v, int sz)
{
  qsort(v,sz,1,&compare); // error
  qsort(v,sz,1,&ccmp); // OK
  isort(v,sz,1,&compare); // OK
  isort(v,sz,1,&ccmp); // error
}

```
To avoid data races in initialization, try these techniques in order:
    [1] Initialize using constant expressions (note that built-in types without initializers are initialized to zero and that standard containers and strings are initialized to empty by linktime initialization).
    [2] Initialize using expressions without side effects.
    [3] Initialize in a known single-threaded ‘‘startup phase’’ of computation.
    [4] Use some form of mutual exclusion.



A program can terminate in several ways:
    [1] By returning from main()
    [2] By calling exit()
    [3] By calling abort()
    [4] By throwing an uncaught exception
    [5] By violating noexcept
    [6] By calling quick_exit()

## Abstraction Mechanisms ##

### Classes ###

### Construction, Cleanup, Copy, and Move ###

### Operator Overloading ###

### Special Operators ###

### Derived Classes ###

### Class Hierarchies ###

### Run-Time Type Information ###

### Templates ###

### Generic Programming ###

### Specialization ###

### Instantiation ###

### Templates and Hierarchies ###

### Metaprogramming ###

### A Matrix Design ###
