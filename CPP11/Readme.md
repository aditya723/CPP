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

• A class is a user-defined type.
• A class consists of a set of members. The most common kinds of members are data members and member functions.
• Member functions can define the meaning of initialization (creation), copy, move, and cleanup (destruction).
• Members are accessed using . (dot) for objects and −> (arrow) for pointers.
• Operators, such as +, !, and [], can be defined for a class.
• A class is a namespace containing its members.
• The public members provide the class’s interface and the private members provide implementation details.
• A struct is a class where members are by default public. By default, members of a class are private.
• Functions declared within a class definition (a struct is a kind of class; are called member functions.
• By default, objects can be copied. In particular, a class object can be initialized with a copy of an object of its class. The default semantics is memberwise copy. If that is not the right choice for a class X, the user can define an appropriate assignment operator

**Access Control**

**Constructors**

- A constructor is recognized by having the same name as the class itself. When a class has a constructor, all objects of that class will be initialized by a constructor call. If the constructor requires arguments, these arguments must be supplied.
- By providing several constructors, we can provide a variety of ways of initializing objects of a type. Constructors obey the same overloading rules as do ordinary functions.
- Given constructors, other member functions no longer have to deal with the possibility of uninitialized data

```CPP
class Date {
  int d, m, y;
  public:
  // ...
  Date(int, int, int); // day, month, year
  Date(int, int); // day, month, today’s year
  Date(int); //day, today’s month and year
  Date(); //default Date: today
  Date(const char∗); // date in string representation
  Date(int dd =0, int mm =0, int yy =0); we could use the default values directly as default arguments

  explicit Date(int dd =0, int mm =0, int yy =0);
};
```

Since a constructor defines initialization for a class, we can use the {}-initializer notation. Brace initialization does not allow narrowing.

```CPP
#include <vector>

std::vector<int> v1(10, 5);   // 10 elements, each 5
std::vector<int> v2{10, 5};   // two elements: 10 and 5

```
Here:

() calls (size, value)
{} calls initializer_list

If you want the first behavior, you must use ().

```CPP
auto a = std::vector<int>(10);  // vector of size 10
auto b = std::vector<int>{10};  // vector with one element 10

Semantics change because {} prefers initializer_list.
```
It is recommend to use the {} notation over the () notation for initialization because it is explicit about what is being done (initialization), avoids some potential mistakes, and can be used consistently.

A constructor declared with the keyword `explicit` can only be used for initialization and explicit conversions. It we can specify that a constructor is not used as an implicit conversion.  By default, declare a constructor that can be called with a single argument explicit. If a constructor is declared explicit and defined outside the class, that explicit cannot be repeated

```CPP
class Date {
  int d, m, y;
  public:
  explicit Date(int dd);
  // ...
};
Date::Date(int dd) { /* ... */ } // OK
explicit Date::Date(int dd) { /* ... */ } // error
```

```CPP
class Date {
  int d, m, y;
  public:
  explicit Date(int dd =0, int mm =0, int yy =0);
  // ...
};

Date d1 {15}; // OK: considered explicit
Date d2 = Date{15}; // OK: explicit
Date d3 = {15}; // error : = initialization does not do implicit conversions, type of 15 is not Date rathet int.
Date d4 = 15; // error : = initialization does not do implicit conversions, type of 15 is not Date rathet int

void f()
{
  my_fct(15); // error : argument passing does not do implicit conversions
  my_fct({15}); // error : argument passing does not do implicit conversions
  my_fct(Date{15}); // OK: explicit
// ...
}
```

```CPP

struct X {
  explicit X();
  explicit X(int,int);
};

X x1 ={}; //error : implicit
X x2 = {1,2}; // error : implicit
X x3{}; //OK: explicit
X x4 {1,2}; // OK: explicit
int f(X);
int i1 = f({}); // error : implicit
int i2 = f({1,2}); // error : implicit
int i3 = f(X{}); // OK: explicit
int i4 = f(X{1,2}); // OK: explicit
```

**In-Class Initializers**

```CPP
class Date {
  int d {today.d};
  int m {today.m};
  int y {today.y};
public:
  Date(int, int, int); // day, month, year
  Date(int, int); // day, month, today’s year
  Date(int); //day, today’s month and year
  Date(); //default Date: today
  Date(const char∗); // date in string representation
// ...
```

**Mutability**

We can define a named object as a constant or as a variable. In other words, a name can refer to an object that holds an immutable or a mutable value. Mutable allows a data member to be modified even if the object is const.
Systematic use of immutable objects leads to more comprehensible code, to more errors being found early, and sometimes to improved performance. In particular, immutability is a most useful property in a multi-threaded program.

`Constant Member Functions`

- A const member function can be invoked for both const and non-const objects, whereas a nonconst member function can be invoked only for non-const objects.
- When a const member function is defined outside its class, the const suffix is required.
- Note that const does not apply (transitively) to objects accessed through pointers or references.
- Bitwise constness → No member changes at all. Logical constness → Object’s observable behavior doesn’t change.
- mutable supports logical constness.

```CPP
#include <mutex>

class ThreadSafe {
    mutable std::mutex m;
    int data;

public:
    int get() const {
        std::lock_guard<std::mutex> lock(m);
        return data;
    }
};

Locking modifies the mutex state, but not the logical state of the object. Without mutable, this wouldn't compile.
```


We can define a member of a class to be mutable, meaning that it can be modified even in a const object:

```CPP
class Date {
public:
  // ...
  string string_rep() const; // string representation
  private:
  mutable bool cache_valid;
  mutable string cache;
  void compute_cache_value() const; // fill (mutable) cache
  // ...
};
```

Now we can define string_rep() in the obvious way:

```CPP
string Date::string_rep() const
{
  if (!cache_valid) {
    compute_cache_value();
    cache_valid = true;
  }
  return cache;
}
```

We can now use string_rep() for both const and non-const objects. For example:

```CPP
void f(Date d, const Date cd)
{
  string s1 = d.string_rep();
  string s2 = cd.string_rep(); // OK!
  // ...
}
```
Even if an object is const, it can still modify the data it points to.  Because const applies to the object itself — not necessarily to the memory it refers to.  This is different from mutable.  Here, we rely on pointers or references. It is called as Mutability through Indirection.


```CPP
class A {
    int* p;
public:
    A(int* ptr) : p(ptr) {}

    void change() const {
        *p = 42;   // ✅ Allowed
    }
};

Even though change() is const, we modify *p.
Because:
p itself is not changed.
Only the memory it points to is changed.
const does not automatically mean “deep const”.
```

- Each (non-static) member function knows for which object it was invoked and can explicitly refer to it.
- The expression ∗this refers to the object for which a member function is invoked.
- In a non-static member function, the keyword this(Self-Reference) is a pointer to the object for which the function was invoked. In a non-const member function of class X, the type of this is X∗. However, this is considered an rvalue, so it is not possible to take the address of this or to assign to this. In a const member function of class X, the type of this is const X∗ to prevent modification of the object itsel.
- One common explicit use of this is in linked-list manipulation. For example:
```CPP
struct Link {
  Link∗ pre;
  Link∗ suc;
  int data;
  
  Link∗ insert(int x) // inser t x before this
  {
    return pre = new Link{pre ,this,x};
  }
  
  void remove() // remove and destroy this
  {
    if (pre) pre−>suc = suc;
    if (suc) suc−>pre = pre;
    delete this;
  }
  // ...
};
```

Explicit use of this is required for access to members of base classes from a derived class that is a template.

- Member of a class X can be accessed by applying the . (dot) operator to an object of class X or by applying the −> (arrow) operator to a pointer to an object of class X.


**static Members**

- A static member – a function or data member – must be defined somewhere. The keyword static is not repeated in the definition of a static member.
- A variable that is part of a class, yet is not part of an object of that class, is called a static member. There is exactly one copy of a static member instead of one copy per object, as for
ordinary non-static members.
- Similarly, a function that needs access to members of a class, yet doesn’t need to be invoked for a particular object, is called a static member function.

```CPP
class Employee {
private:
    std::string name;          // Non-static member → one per object
    static int count;          // Static data member → ONE shared copy

public:
    Employee(std::string n) : name(n) {
        ++count;               // Accessing shared static member
    }

    static int getCount() {    // Static member function
        return count;          // Can access only static members directly
    }
};

// Definition of static data member
// IMPORTANT: 'static' keyword is NOT repeated here
int Employee::count = 0;

int main() {
    Employee e1("Alice");
    Employee e2("Bob");

    std::cout << Employee::getCount();  // Call using class name
}

```

**Member class / Nested class**

```CPP
template<typename T>
class Tree {
  using value_type = T; // member alias
  enum Policy { rb, splay, treeps }; // member enum
  class Node { // member class
    Node∗ right;
    Node∗ left;
    value_type value;
    public:
    void f(Tree∗);
  };
  Node∗ top;
  public:
  void g(const T&);
  // ...
};
```

A member class (often called a nested class) can refer to types and static members of its enclosing class. It can only refer to non-static members when it is given an object of the enclosing class to refer to.
A nested class has access to members of its enclosing class, even to private members (just as a member function has), but has no notion of a current object of the enclosing class.

```CPP
template<typename T>
void Tree::Node::f(Tree∗ p)
{
  top = right; // error : no object of type Tree specified
  p−>top = right; // OK
  value_type v = left−>value; // OK: value_type is not associated with an object
}
```

A class does not have any special access rights to the members of its nested class. For example:
```CPP
template<typename T>
void Tree::g(Tree::Node∗ p)
{
  value_type val = right−>value; //error : no object of type Tree::Node
  value_type v = p−>right−>value; // error : Node::right is private
  p−>f(this); //OK
}
```
Member enums are often an alternative to enum classes when it comes to avoiding polluting an enclosing scope with the names of enumerators

A class is called concrete (or a concrete class) if its representation is part of its definition. This distinguishes it from abstract classes (§3.2.2, §20.4) which provide an interface to a variety of
implementations. Having the representation available allows us:
• To place objects on the stack, in statically allocated memory, and in other objects
• To copy and move objects
• To refer directly to named objects (as opposed to accessing through pointers and references)

- Use public data (structs) only when it really is just data and no invariant is meaningful for the data members.
- Make a function that needs access to the representation of a class but needn’t be called for a specific object a static member function.


### Life cycle of an object - Construction, Cleanup, Copy, and Move ###

Constructors, copy and move assignment operations, and destructors directly support a view of lifetime and resource management. An object is considered an object of its type after its constructor
completes, and it remains an object of its type until its destructor starts executing.

```CPP
class X {
  X(Sometype); // ‘‘ordinar y constr uctor’’: create an object
  X(); //default constructor
  X(const X&); // copy constr uctor
  X(X&&); //move constr uctor
  X& operator=(const X&); // copy assignment: clean up target and copy
  X& operator=(X&&); // move assignment: clean up target and move
  ˜X(); //destructor: clean up
};
```
There are five situations in which an object is copied or moved:
  • As the source of an assignment
  • As an object initializer
  • As a function argument
  • As a function return value
  • As an exception

```CPP
struct S {
S(); //fine
void S(int); // error : no type can be specified for a constructor
int S; // error : the class name must denote a constructor
enum S { foo, bar }; // error : the class name must denote a constructor
};
```
Constructor initialization must establish a class invariant, that is, something that must hold whenever a member function is called (from outside the class).

A constructor builds a class object ‘‘from the bottom up’’:
  [1] first, the constructor invokes its base class constructors,
  [2] then, it invokes the member constructors, and
  [3] finally, it executes its own body.
A destructor ‘‘tears down’’ an object in the reverse order:
  [1] first, the destructor executes its own body,
  [2] then, it invokes its member destructors, and
  [3] finally, it inv okes its base class destructors.

In particular, a virtual base is constructed before any base that might use it and destroyed after all such bases. This ordering ensures that a base or a member is not used before it has been initialized or used after it has been destroyed.
A destructor is invoked implicitly upon exit from a scope or by delete.

```CPP
new(p) X{a}; // copy constr uct an X with the value a in address p. This use of a constructor is known as ‘‘placement new’’ 
```

A destructor can be declared to be virtual, and usually should be for a class with a virtual function. The reason we need a virtual destructor is that an object usually manipulated through the interface
provided by a base class is often also deleted through that interface

```CPP
void user(Shape∗ p)
{
  p−>draw(); // invoke the appropriate draw()
  // ...
  delete p; // invoke the appropriate destructor
};
```
Had Shape’s destructor not been virtual that delete would have failed to invoke the appropriate derived class destructor (e.g., ˜Circle()). That failure would cause the resources owned by the deleted object (if any) to be leaked.
If a class has a private non-static data member, it needs a constructor to initialize it. We can initialize objects of a class for which we have not defined a constructor using
  • memberwise initialization,
  • copy initialization, or
  • default initialization (without an initializer or with an empty initializer list).

```CPP
struct Work {
  string author;
  string name;
  int year;
};

Work s9 { "Beethoven",
    "Symphony No. 9 in D minor, Op. 125; Choral",
    1824
    }; //memberwise initialization

Work currently_playing { s9 }; // copy initialization

Work none {}; // default initialization
```
The three members of currently_playing are copies of those of s9. The default initialization of using {} is defined as initialization of each member by {}. So, none
is initialized to {{},{},{}}, which is {"","",0}.

### Operator Overloading ###

Functions defining meanings for the following operators can be declared:

```CPP
+     −   ∗     /       %       ˆ     &
|     ˜   !     =       <       >     +=
−=   ∗=   /=     %=    ˆ=       &=     |=
<<   >>   >>=   <<=     ==     !=     <=
>=   &&   ||     ++     −−     −>∗     ,
−>   []   ()     new   new[]   delete   delete[]
```

The following operators cannot be defined by a user:

```CPP
:: scope resolution
. member selection
.∗ member selection through pointer to member
```

They take a name, rather than a value, as their second operand and provide the primary means of referring to members.

The named ‘‘operators’’cannot be overloaded because they report fundamental facts about their operands:

```CPP
sizeof size of object 
alignof alignment of object
typeid type_info of an object
```

Finally, the ternary conditional expression operator cannot be overloaded (for no particularly fundamental reason):

```CPP
?: conditional evaluation
```

A binary operator can be defined by either a non-static member function taking one argument or a nonmember function taking two arguments. For any binary operator @, aa@bb can be interpreted
as either aa.operator@(bb) or operator@(aa,bb). If both are defined, overload resolution= determines which, if any, interpretation is used.

```CPP
class X {
  public:
  void operator+(int);
  X(int);
};

void operator+(X,X);

void operator+(X,double);

void f(X a)
{
  a+1; // a.operator+(1)
  1+a; // ::operator+(X(1),a)
  a+1.0; // ::operator+(a,1.0)
}
```

```CPP
class X {
  public: // members (with implicit this pointer):
  X∗ operator&(); // prefix unary & (address of)
  X operator&(X); // binar y & (and)
  X operator++(int); // postfix increment (see §19.2.4)
  X operator&(X,X); // error : ter nary
  X operator/(); // error : unar y /
};

// nonmember functions :
X operator−(X); //prefix unary minus
X operator−(X,X); //binar y minus
X operator−−(X&,int); // postfix decrement
X operator−(); //error : no operand
X operator−(X,X,X); // error : ter nary
X operator%(X); // error : unar y %
```

The operators operator= , operator[] , operator() , and operator−> must be non-static member functions. The default meaning of &&, ||, and , (comma) involves sequencing: the first operand is evaluated
before the second (and for && and || the second operand is not always evaluated). This special rule does not hold for user-defined versions of &&, ||, and , (comma); instead these operators are treated exactly like other binary operators.

The operators = (assignment), & (address-of), and , (sequencing) have predefined meanings when applied to class objects.

```CPP
class X {
  public:
  // ...
  void operator=(const X&) = delete;
  void operator&() = delete;
  void operator,(const X&) = delete;
  // ...
};
void f(X a, X b)
{
  a = b; // error : no operator=()
  &a; // error : no operator&()
  a,b; // error : no operator,()
}
```
An operator function must either be a member or take at least one argument of a user-defined type (functions redefining the new and delete operators need not). This rule ensures that a user cannot change the meaning of an expression unless the expression contains an object of a user-defined type. In particular, it is not possible to define an operator function that operates exclusively on pointers.
An operator function intended to accept a built-in type  as its first operand cannot be a member function. For example, consider adding a complex variable aa to the integer 2: aa+2 can, with a suitably declared member function, be interpreted as aa.operator+(2), but 2+aa cannot because there is no class int for which to define + to mean 2.operator+(aa). Because the compiler does not know the meaning of a user-defined +, it cannot assume that the operator is commutative and so interpret 2+aa as aa+2.

Enumerations are user-defined types so that we can define operators for them. For example:

```CPP
enum Day { sun, mon, tue, wed, thu, fri, sat };

Day& operator++(Day& d)
{
  return d = (sat==d) ? sun : static_cast<Day>(d+1);
}
```

For arguments, we have two main choices for passing arguments:
• Pass-by-value
• Pass-by-reference

We use const references to pass large objects that are not meant to be modified by the called function.

```CPP
void Point::operator+=(Point delta); // pass-by-value
Matrix operator+(const Matrix&, const Matrix&); // pass-by-const-reference
Matrix operator+(const Matrix& a, const Matrix& b) // return-by-value
Matrix& Matrix::operator+=(const Matrix& a) // return-by-reference
```
**Operators in Namespaces**

An operator is either a member of a class or defined in some namespace (possibly the global namespace).

```CPP
namespace std { // simplified std
  class string {
  };
  
  class ostream {
    ostream& operator<<(const char∗); //output C-style string
  };
  extern ostream cout;
  ostream& operator<<(ostream&, const string&); // output std::string
} // namespace std

std::cout << p
means
std::cout.operator<<(p)

```

Consider a binary operator @. If x is of type X and y is of type Y, x@y is resolved like this:
  • If X is a class, look for operator@ as a member of X or as a member of a base of X; and
  • look for declarations of operator@ in the context surrounding x@y; and
  • if X is defined in namespace N, look for declarations of operator@ in N; and
  • if Y is defined in namespace M, look for declarations of operator@ in M.

Declarations for several operator@s may be found and overload resolution rules are used to find the best match, if any. This lookup mechanism is applied only if the operator has at least one operand of a user-defined type. Note that a type alias is just a synonym and not a separate user-defined type. Note that in operator lookup no preference is given to members over nonmembers. This differs from lookup of named functions The lack of hiding of operators ensures that built-in
operators are never inaccessible and that users can supply new meanings for an operator without modifying existing class declarations. Unary operators are resolved analogously.

```CPP
X operator!(X);

struct Z {
  Z operator!(); //does not hide ::operator!()
  X f(X x) { /* ... */ return !x; } // invoke ::operator!(X)
  int f(int x) { /* ... */ return !x; } // invoke the built-in ! for ints
};
```
In particular, the standard iostream library defines << member functions to output built-in types, and a user can define << to output user-defined types without modifying class ostream.


### Special Operators ###

```CPP
[] () −> ++ −− new delete
```

An operator[]() must be a non-static member function.

```CPP
obj[index]
is translated by the compiler into:
obj.operator[](index)
So it must belong to the class of obj.
```

An operator()() must be a non-static member function. The use of the () operator is to provide the usual function call syntax for objects that in some way behave like functions.

Operator −> must be a non-static member function. If used, its return type must be a pointer or an object of a class to which you can apply −>. Despite the similarity between −> and . (dot), there is no way of overloading operator . (dot).

The increment and decrement operators are unique among C++ operators in that they can be used as both prefix and postfix operators. Consequently, we must define prefix and postfix increment and decrement for Ptr<T>. For example:

```CPP
template<typename T>
class Ptr {
  T∗ ptr;
  T∗ array;
  int sz;
  public:
  template<int N>
  Ptr(T∗ p, T(&a)[N]); // bind to array a, sz==N, initial value p
  Ptr(T∗ p, T∗ a, int s); // bind to array a of size s, initial value p
  Ptr(T∗p); //bind to single object, sz==0, initial value p
  Ptr& operator++(); // prefix
  Ptr operator++(int); // postfix
  Ptr& operator−−(); // prefix
  Ptr operator−−(int); // postfix
  T& operator∗(); //prefix
};
```

The int argument is used to indicate that the function is to be invoked for postfix application of ++. This int is never used; the argument is simply a dummy used to distinguish between prefix and postfix application.

```CPP
template<typename T>
Ptr& Ptr<T>::operator++() // return the current object after incrementing
{
  // ... check that ptr+1 can be pointed to ...
  return ∗++ptr;
}
```

The pre-increment operator can return a reference to its object. The post-increment operator must make a new object to return.

 ```CPP
template<typename T>
Ptr Ptr<T>::operator++(int) // increment and return a Ptr with the old value
{
  // ... check that ptr+1 can be pointed to ...
  Ptr<T> old {ptr,array,sz};
  ++ptr;
  return old;
}
```

A user can redefine the global operator new() and operator delete() or define operator new() and operator delete() for a particular class.

```CPP
void∗ operator new(siz e_t); // use for individual object
void∗ operator new[](siz e_t); // use for array
void operator delete(void∗, siz e_t); // use for individual object
void operator delete[](void∗, siz e_t); // use for array

void∗ operator new (siz e_t sz, void∗ p) noexcept; // place object of size sz at p
void∗ operator new[](siz e_t sz, void∗ p) noexcept; // place object of size sz at p
void operator delete (void∗ p, void∗) noexcept; // if (p) make *p invalid
void operator delete[](void∗ p, void∗) noexcept; // if (p) make *p invalid

void∗ operator new(siz e_t, void∗ p) { return p; } // explicit placement operator

int∗ p = new(nothrow) int[n]; // allocate n ints on the free store

void∗ operator new(siz e_t sz, const nothrow_t&) noexcept; // allocate sz bytes; // return nullptr if allocation failed
void operator delete(void∗ p, const nothrow_t&) noexcept; // deallocate space allocated by new
void∗ operator new[](siz e_t sz, const nothrow_t&) noexcept; // allocate sz bytes; // return nullptr if allocation failed
void operator delete[](void∗ p, const nothrow_t&) noexcept; // deallocate space allocated by new

```

Member operator new()s and operator delete()s are implicitly static members. Consequently, they don’t hav e a this pointer and do not modify an object. They provide storage that a constructor can initialize and a destructor can clean up.

How does a compiler know how to supply the right size to operator delete()? The type specified in the delete operation matches the type of the object being deleted. If we delete an object through a pointer to a base class, that base class must have a virtual destructor for the correct size to be given:

```CPP
Employee∗ p = new Manager; // potential trouble (the exact type is lost)
// ...
delete p; // hope Employee has a virtual destructor
```

In principle, deallocation is then done by the destructor (which knows the size of its class).

we can define literals for user-defined types and new forms of literals for built-in types. For example:

```CPP
"Hi!"s //string, not ‘‘zero-ter minated array of char’’
1.2i //imaginar y
101010111000101b // binar y
123s //seconds
123.56km //not miles! (units)
1234567890123456789012345678901234567890x // extended-precision
```
Such user-defined literals are supported through the notion of literal operators that map literals with a given suffix into a desired type. The name of a literal operator is operator"" followed by the suffix.

```CPP
 complex<double> operator"" i(long double d) // imaginar y literal , suffixes i
{
  return {0,d}; // complex is a literal type
}

std::string operator"" s(const char∗ p, size_t n) // std::string literal
{
  return string{p,n}; // requires free-store allocation
}

template<typename T> void f(const T&);

f("Hello"); // pass pointer to char*
f("Hello"s); // pass (five-character) string object
f("Hello\n"s); // pass (six-character) string object
auto z = 2+1i; // complex{2,1}

```

There are four kinds of literals that can be suffixed to make a user-defined literal):
• _An integer literal_: accepted by a literal operator taking an unsigned long long or a const char∗ argument or by a template literal operator, for example, 123m or 12345678901234567890X
• _A floating-point literal_: accepted by a literal operator taking a long double or a const char∗ argument or by a template literal operator, for example, 12345678901234567890.976543210x or 3.99s
• _A string literal_: accepted by a literal operator taking a (const char∗, size_t) pair of arguments, for example, "string"s and R"(Foo\bar)"_path
• _A character literal_: accepted by a literal operator taking a character argument of type char, wchar_t, char16_t, or char32_t, for example, 'f'_runic or u'BEEF'_w.


For example, we could define a literal operator to collect digits for integer values that cannot be represented in any of the built-in integer types:

```CPP
Bignum operator"" x(const char∗ p)
{
  return Bignum(p);
}

void f(Bignum);

f(123456789012345678901234567890123456789012345x);

the C-style string "123456789012345678901234567890123456789012345" is passed to operator"" x().
```

**Friends**

An ordinary member function declaration specifies three logically distinct things:
[1] The function can access the private part of the class declaration.
[2] The function is in the scope of the class.
[3] The function must be invoked on an object (has a this pointer).
By declaring a member function static, we can give it the first two properties only. By declaring a nonmember function a friend, we can give it the first property only. That is, a function
declared friend is granted access to the implementation of a class just like a member function but is otherwise independent of that class.

A friend declaration can be placed in either the private or the public part of a class declaration; it does not matter where. Like a member function, a friend function is explicitly declared in the declaration
of the class of which it is a friend. It is therefore as much a part of that interface as is a member function.

A member function of one class can be the friend of another. For example:
```CPP
class List_iterator {
// ...
  int∗ next();
};

class List {
  friend int∗ List_iterator::next();
// ...
};

There is a shorthand for making all functions of one class friends of another. For example:

class List {
  friend class List_iterator;
// ...
};
```
It is possible to make a template argument a friend.

```CPP
template<typename T>
class X {
  friend T;
  friend class T; // redundant ‘‘class’’
  // ...
};
```

A friend must be previously declared in an enclosing scope or defined in the non-class scope immediately enclosing the class that is declaring it to be a friend. Scopes outside the innermost enclosing namespace scope are not considered for a name first declared as a friend.

```CPP

class C1 { }; // will become friend of N::C
void f1(); // will become friend of N::C
namespace N {
  class C2 { }; // will become friend of C
  void f2() { } // will become friend of C
  class C {
  int x;
  public:
      friend class C1; // OK (previously defined)
      friend void f1();
      friend class C3; // OK (defined in enclosing namespace)
      friend void f3();
      friend class C4; // First declared in N and assumed to be in N
      friend void f4();
};

class C3 {}; // friend of C
void f3() { C x; x.x = 1; } // OK: friend of C
} // namespace N

class C4 { }; // not friend of N::C
void f4() { N::C x; x.x = 1; } // error : x is private and f4() is not a friend of N::C

```
A friend function can be found through its arguments even if it was not declared in the immediately enclosing scope. Thus, a friend function should be explicitly declared in an enclosing scope or take an argument of
its class or a class derived from that. If not, the friend cannot be called.

```CPP
// no f() in this scope
class X {
  friend void f(); // useless
  friend void h(const X&); // can be found through its argument
};
void g(const X& x)
{
  f(); // no f() in scope
  h(x); // X’s friend h()
}
```
_Should it be a member, a static member, or a friend?_

- Because member names are local to the class, a function that requires direct access to the representation should be a member unless there is a specific reason for it to be a nonmember.
- An operation modifying the state of a class object should therefore be a member or a function taking a non-const reference argument (or a non-const pointer argument).
- operations that do not need direct access to a representation are often best represented as nonmember functions, possibly in a namespace that makes their relationship with the class explicit.
- 
### Derived Classes ###

• Implementation inheritance: to sav e implementation effort by sharing facilities provided by a base class.
• Interface inheritance: to allow different derived classes to be used interchangeably through the interface provided by a common base class.

Interface inheritance is often referred to as run-time polymorphism (or dynamic polymorphism). In contrast, the uniform use of classes not related by inheritance provided by templates is often referred to as compile-time polymorphism (or static polymorphism).

A derived class is often said to inherit properties from its base, so the relationship is also called inheritance. A base class is sometimes called a superclass and a derived class a subclass.

Deriving Manager from Employee in this way makes Manager a subtype of Employee, so that a Manager can be used wherever an Employee is acceptable. A Manager is (also) an Employee, so a Manager∗ can be used as an Employee∗. Similarly, a Manager&
can be used as an Employee&. However, an Employee is not necessarily a Manager, so an Employee∗ cannot be used as a Manager∗.

```CPP
void g(Manager mm, Employee ee)
{
  Employee∗ pe = &mm; // OK: every Manager is an Employee
  Manager∗ pm = &ee; // error : not every Employee is a Manager
  pm−>level = 2; // disaster : ee doesn’t have a lev el
  pm = static_cast<Manager∗>(pe); // brute force: wor ks because pe points
  // to the Manager mm
  pm−>level = 2; // fine: pm points to the Manager mm that has a level
}
```

In other words, an object of a derived class can be treated as an object of its base class when manipulated through pointers and references.

Using a class as a base is equivalent to defining an (unnamed) object of that class. Consequently, a class must be defined in order to be used as a base:

```CPP
class Employee; // declaration only, no definition
class Manager : public Employee { // error : Employee not defined
  // ...
};
```

A member of a derived class can use the public – and protected – members of a base class as if they were declared in the derived class itself. However, a derived class cannot access private members of a base class.

As usual, constructors and destructors are as essential:
• Objects are constructed from the bottom up (base before member and member before derived) and destroyed top-down (derived before member and member before base);
• Each class can initialize its members and bases (but not directly members or bases of its bases);.
• Typically, destructors in a hierarchy need to be virtual;.
• Copy constructors of classes in a hierarchy should be used with care (if at all) to avoid slicing;
• The resolution of a virtual function call, a dynamic_cast, or a typeid() in a constructor or destructor reflects the stage of construction and destruction (rather than the type of the yet-tobe-completed object);

In a large class hierarchy, accessible (not private) data in a common base class becomes the ‘‘global variables’’ of the hierarchy i.e. visible to everyone. For clean design and simpler maintenance, we want to keep separate issues separate and avoid mutual dependencies. This causes a violation of the ideals of modularity and data hiding.

**Virtual Functions**

Virtual functions allow the programmer to declare functions in a base class that can be redefined in each derived class. The compiler and linker will guarantee the correct correspondence between objects and the functions applied to them.
A virtual function must be defined for the class in which it is first declared (unless it is declared to be a pure virtual function. To allow a virtual function declaration to act as an interface to functions defined in derived
classes, the argument types specified for a function in a derived class cannot differ from the argument types declared in the base, and only very slight changes are allowed for the return type.

A virtual function can be used even if no class is derived from its class, and a derived class that does not need its own version of a virtual function need not provide one. A function from a derived class with the same name and the same set of argument types as a virtual function in a base is said to override the base class version of the virtual function. Furthermore, it is possible to override a virtual function from a base with a more derived return type.

To get runtime polymorphic behavior in C++, the member functions called must be virtual and objects must be manipulated through pointers or references. When manipulating an object directly (rather than through a pointer or reference),
its exact type is known by the compiler so that run-time polymorphism is not needed.

By default, a function that overrides a virtual function itself becomes virtual. We can, but do not have to, repeat virtual in a derived class. If you want to be explicit, use override.

The class internally created a pointer to implement polymorphism. In a typical implementation, the space taken is just enough to hold a pointer: the usual implementation technique is for the compiler to convert the name of a virtual function into an index into  a table of pointers to functions. That table is usually called the virtual function table or simply the vtbl. Each class with virtual functions has its own vtbl identifying its virtual functions. This can be represented graphically like this:

<img width="735" height="373" alt="image" src="https://github.com/user-attachments/assets/ec1943c8-9405-4208-9dba-6fbecf44f305" />

The functions in the vtbl allow the object to be used correctly even when the size of the object and the layout of its data are unknown to the caller. The implementation of a caller need only know the location of the vtbl in an Employee and the index used for each virtual function. This virtual call mechanism can be made almost as efficient as the ‘‘normal function call’’ mechanism (within 25%), so efficiency concerns should not deter anyone from using a virtual function where an ordinary function call would be acceptably efficient. Its space overhead is one pointer in each object of a class with virtual functions plus one vtbl for each such class. You pay this overhead only for objects of a class with a virtual function. You choose to pay this overhead only if you need the added functionality virtual functions provide. Had you chosen to use the alternative type-field solution, a comparable amount of space would have been needed for the type field.

A virtual function invoked from a constructor or a destructor reflects that the object is partially constructed or partially destroyed. It is therefore typically a bad idea to call a virtual function from a constructor or a destructor.

Calling a function using the scope resolution operator, ::,  ensures that the virtual mechanism is not used.

**Override Control**

_virtual_: The function may be overridden.
_=0_: The function must be virtual and must be overridden.
_override_: The function is meant to override a virtual function in a base class. Can not be used for non-virtual functions.
_final_: The function is not meant to be overridden.

In the absence of any of these controls, a non-static member function is virtual if and only if it overrides a virtual function in a base class.

The _override_ specifier comes last in a declaration, after all other parts. In a large or complicated class hierarchy with many virtual functions, it is best to use virtual only to introduce a new virtual function and to use override on all functions intended as overriders. Using override is a bit verbose but clarifies the programmer’s intent. An override specifier is not part of the type of a function and cannot be repeated in an out-ofclass.
definition.


**override**

```CPP
class Derived : public Base {
  void f() override; // OK if Base has a virtual f()
  void g() override; // OK if Base has a virtual g()
};
void Derived::f() override // error : overr ide out of class
{
  // ...
}

void g() // OK
{
// ...
}
```
override is not a keyword; it is what is called a contextual keyword. That is, override has a special meaning in a few contexts but can be used as an identifier elsewhere. There is a relaxation of the rule that the type of an overriding function must be the same as the type of the virtual function it overrides. That is, if the original return type was B∗, then the return type of the overriding function may be D∗, provided B is a public base of D. Similarly, a return type of B& may be relaxed to D&. This is sometimes called the covariant return rule. This relaxation applies only to return types that are pointers or references, and not to ‘‘smart pointers’’ such as unique_ptr.

**final**

Reasons to choose virtual:
• Can we imagine the need for further derived classes?
• Does a designer of a derived class need to redefine the function to achieve a plausible aim?
• Is overriding a function error-prone (i.e., is it hard for an overriding function to provide the expected semantics of a virtual function)?

If the answer is ‘‘no’’ to all three questions, we can leave the function non-virtual to gain simplicity of design and occasionally some performance (mostly from inlining). Far more rarely, we hav e a class hierarchy that starts out with virtual functions, but after the definition of a set of derived classes, one of the answers becomes ‘‘no.’’ That is, we might want to close our design to modification from its users. 

```CPP
struct Node { // interface class
  virtual Type type() = 0;
  // ...
};

class If_statement : public Node {
public:
  Type type() override final; // prevent further overr iding
  // ...
};

class Modified_if_statement : public If_statement {
public:
  Type type() override; // error : If_statement::type() is final
  // ...
};
```
For good and bad, adding final to the class not only prevents overriding, it also prevents further derivation from a class.
A final specifier is not part of the type of a function and cannot be repeated in an out-of-class definition. For example:

```CPP
class Derived : public Base {
  void f() final; // OK if Base has a virtual f()
  void g() final; // OK if Base has a virtual g()
  // ...
};

void Derived::f() final // error : final out of class
{
  // ...
}

void g() final // OK
{
  // ...
}
```

Like override, final is a contextual keyword. 

**using**

Functions do not overload across scopes. For example:

```CPP
struct Base {
  void f(int);
};

struct Derived : Base {
  void f(double);
};

void use(Derived d)
{
  d.f(1); // call Derived::f(double)
  Base& br = d
  br.f(1); // call Base::f(int)
}

void use2(D2 d)
{
  d.f(1); // call D2::f(int), that is, Base::f(int)
  Base& br = d
  br.f(1); // call Base::f(int)
}
```

This can surprise people, and sometimes we want overloading to ensure that the best matching member function is used. As for namespaces, using-declarations can be used to add a function to a
scope. For example:
```CPP
struct D2 : Base {
  using Base::f; // bring all fs from Base into D2
  void f(double);
};
```

This is a simple consequence of a class also being considered a namespace. Several using-declarations can bring in names from multiple base classes. For example:

```CPP
struct B1 {
  void f(int);
};

struct B2 {
  void f(double);
};

struct D : B1, B2 {
  using B1::f;
  using B2::f;
  void f(char);
};

void use(D d)
{
  d.f(1); // call D::f(int), that is, B1::f(int)
  d.f('a'); // call D::f(char)
  d.f(1.0); // call D::f(double), that is, B2::f(double)
}
```

A name brought into a derived class scope by a using-declaration has its access determined by the placement of the using-declaration; We cannot use using-directives to bring all members of a base class into a
derived class.

**virtual constructors**
TBD

**Abstract Classes**

A virtual function is ‘‘made pure’’ by the ‘‘pseudo initializer’’ = 0:

```CPP
class Shape { // abstract class
public:
  virtual void rotate(int) = 0; // pure virtual function
  virtual void draw() const = 0; // pure virtual function
  virtual bool is_closed() const = 0; // pure virtual function
  // ...
  virtual˜Shape(); //vir tual
};
```
A class with one or more pure virtual functions is an abstract class, and no objects of that abstract class can be created. Because the interface provided by an abstract class cannot be used to create objects using a constructor, abstract classes don’t usually have constructors. 

**Access Control**

• If it is private, its name can be used only by member functions and friends of the class in which it is declared.
• If it is protected, its name can be used only by member functions and friends of the class in which it is declared and by member functions and friends of classes derived from this class.
• If it is public, its name can be used by any function.

In a class, members are by default private; in a struct, members are by default public.

When designing a class hierarchy, we sometimes provide functions designed to be used by implementers of derived classes but not by the general user. For example, we may provide an (efficient)
unchecked access function for derived class implementers and (safe) checked access for others. Declaring the unchecked version protected achieves that.

```CPP
class Buffer {
public:
char& operator[](int i); // checked access, user can make worry free access
// ...
protected:
char& access(int i); // unchecked access , developer can make intelligent decisions
// ...
};
```
This prevents subtle errors that would otherwise occur when one derived class corrupts data belonging to other derived classes.

Like a member, a base class can be declared private, protected, or public. For example:
```CPP
class X : public B { /* ... */ };
class Y : protected B { /* ... */ };
class Z : private B { /* ... */ };
```

The different access specifiers serve different design needs:
• public derivation makes the derived class a subtype of its base. For example, X is a kind of B. This is the most common form of derivation.
• private bases are most useful when defining a class by restricting the interface to a base so that stronger guarantees can be provided. For example, B is an implementation detail of Z.
• protected bases are useful in class hierarchies in which further derivation is the norm. Like private derivation, protected derivation is used to represent implementation details.

The access specifier for a base class can be left out. In that case, the base defaults to a private base for a class and a public base for a struct. For example:

```CPP
class XX : B { /* ... */ }; // B is a private base
struct YY : B { /* ... */ }; // B is a public base
```

The access specifier for a base class controls the access to members of the base class and the conversion of pointers and references from the derived class type to the base class type. Consider a class D derived from a base class B:
• If B is a private base, its public and protected members can be used only by member functions and friends of D. Only friends and members of D can convert a D∗ to a B∗.
• If B is a protected base, its public and protected members can be used only by member functions and friends of D and by member functions and friends of classes derived from D. Only friends and members of D and friends and members of classes derived from D can convert a D∗ to a B∗.
• If B is a public base, its public members can be used by any function. In addition, its protected members can be used by members and friends of D and members and friends of classes derived from D. Any function can convert a D∗ to a B∗.

This basically restates the rules for member access. When designing a class, we choose access for bases in the same way as we do for members.

**Multiple Inheritance and Access Control**
TBD

**using-Declarations and Access Control**

A using-declaration cannot be used to gain access to additional information. It is simply a mechanism for making accessible information more convenient to use. On the other hand, once access is available, it can be granted to other users.

```CPP
class B {
  private:
    int a;
  protected:
    int b;
  public:
    int c;
};
class D : public B {
public:
  using B::a; // error : B::a is private
  using B::b; // make B::b publicly available through D
};
```

When a using-declaration is combined with private or protected derivation, it can be used to specify interfaces to some, but not all, of the facilities usually offered by a class. For example:

```CPP
class BB : private B { // give access to B::b and B::c, but not B::a
public:
  using B::b;
  using B::c;
};
```
A pointer to member cannot be assigned to a void∗ or any other ordinary pointer. A null pointer (e.g., nullptr) can be assigned to a pointer to member and then represents ‘‘no member.’’

```CPP
class Std_interface {
public:
  virtual void start() = 0;
  virtual void suspend() = 0;
  virtual void resume() = 0;
  virtual void quit() = 0;
  virtual void full_size() = 0;
  virtual void small() = 0;
  virtual ˜Std_interface() {}
};
```

We can use a pointer to member to indirectly refer to a member of a class. Consider Std_interface. If I want to invoke suspend() for some object without mentioning suspend() directly,
I need a pointer to member referring to Std_interface::suspend(). I also need a pointer or reference to the object I want to suspend. Consider a trivial example:

```CPP
using Pstd_mem = void (Std_interface::∗)(); // pointer-to-member type

void f(Std_interface∗ p)
{
  Pstd_mem s = &Std_interface::suspend; // pointer to suspend()
  p−>suspend(); //direct call
  p−>∗s(); //call through pointer to member
}
```
A pointer to member can be obtained by applying the address-of operator, &, to a fully qualified class member name, for example, &Std_interface::suspend. A variable of type ‘‘pointer to member of class X’’ is declared using a declarator of the form X::∗.

Just like ordinary pointers to functions, pointers to member functions are used when we need to refer to a function without having to know its name. However, a pointer to member isn’t a pointer to a piece of memory the way a pointer to a variable or a pointer to a function is. It is more like an offset into a structure or an index into an array, but of course an implementation takes into account the differences between data members, virtual functions, nonvirtual
functions, etc. When a pointer to member is combined with a pointer to an object of the right type, it yields something that identifies a particular member of a particular object.

The p−>∗s() call can be represented graphically like this:

<img width="616" height="140" alt="image" src="https://github.com/user-attachments/assets/1e9ccf42-595e-4137-b8db-570bba1f5734" />

Because a pointer to a virtual member (s in this example) is a kind of offset, it does not depend on an object’s location in memory. A pointer to a virtual member can therefore be passed between different address spaces as long as the same object layout is used in both. Like pointers to ordinary functions, pointers to non-virtual member functions cannot be exchanged between address spaces. Note that the function invoked through the pointer to function can be virtual. For example,
when we call suspend() through a pointer to function, we get the right suspend() for the object to which the pointer to function is applied. This is an essential aspect of pointers to functions.

A static member isn’t associated with a particular object, so a pointer to a static member is simply an ordinary pointer.

```CPP
class Task {
  // ...
  static void schedule();
};

void (∗p)() = &Task::schedule; // OK
void (Task::∗ pm)() = &Task::schedule; // error : ordinar y pointer assigned
// to pointer to member
```
Naturally, the notion of pointer to member applies to data members and to member functions with arguments and return types. For example:
```CPP
struct C {
  const char∗ val;
  int i;
  void print(int x) { cout << val << x << '\n'; }
  int f1(int);
  void f2();
  C(const char∗ v) { val = v; }
};

using Pmfi = void (C::∗)(int); // pointer to member function of C taking an int
using Pm = const char∗ C::∗; //pointer to char* data member of C

void f(C& z1, C& z2)
{
  C∗ p = &z2;
  Pmfi pf = &C::print;
  Pm pm = &C::val;
  z1.print(1);
  (z1.∗pf)(2);
  z1.∗pm = "nv1 ";
  p−>∗pm = "nv2 ";
  z2.print(3);
  (p−>∗pf)(4);
  pf = &C::f1; // error : retur n type mismatch
  pf = &C::f2; // error : argument type mismatch
  pm = &C::i; // error : type mismatch
  pm = pf; // error : type mismatch
}
```
The type of a pointer to function is checked just like any other type.

We can safely assign a pointer to a member of a base class to a pointer to a member of a derived class, but not the other way around. This property is often called contravariance.

```CPP
class Text : public Std_interface {
public:
  void start();
  void suspend();
  // ...
virtual void print();
  private:
    vector s;
};
void (Std_interface::∗ pmi)() = &Text::print; // error
void (Text::∗pmt)() = &Std_interface::start; // OK
```

This contravariance rule appears to be the opposite of the rule that says we can assign a pointer to a derived class to a pointer to its base class. In fact, both rules exist to preserve the fundamental
guarantee that a pointer may never point to an object that doesn’t at least have the properties that the pointer promises. In this case, Std_interface::∗ can be applied to any Std_interface, and most
such objects presumably are not of type Text. Consequently, they do not have the member Text::print with which we tried to initialize pmi. By refusing the initialization, the compiler saves us from a run-time error.

### Class Hierarchies ###

The logical conclusion of this line of thought is a system represented to users as a hierarchy of abstract classes and implemented by a classical hierarchy. In other words:
• Use abstract classes to support interface inheritance.
• Use base classes with implementations of virtual functions to support implementation inheritance.

_factory_: is class which is responsible to create object of class, and its functions are (somewhat misleadingly) sometimes called virtual constructors.

inheritance aims to provide one of two benefits:
• Shared interfaces: leading to less replication of code using classes and making such code more uniform. This is often called run-time polymorphism or interface inheritance.
• Shared implementation: leading to less code and more uniform implementation code. This is often called implementation inheritance.



### Run-Time Type Information ###

### Templates ###

### Generic Programming ###

### Specialization ###

### Instantiation ###

### Templates and Hierarchies ###

### Metaprogramming ###

### A Matrix Design ###
