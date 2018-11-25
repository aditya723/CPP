#include <iostream>
#include <string>
using namespace std;

class Pet {
        string pname;
        public:
        Pet(const string& name) : pname(name) {}
        virtual string name() const { return pname; }
        virtual string description() const {
                return "This is " + pname;
        }
};

class Dog : public Pet {
        string favoriteActivity;
        public:
        Dog(const string& name, const string& activity)
                : Pet(name), favoriteActivity(activity) {}
        string description() const {
                        return Pet::name() + " likes to " +
                                favoriteActivity;
                }
};

void describe(Pet p) { // Slices the object, object of size pet will be pushed onto stack rest object is sliced
/* When passing by value, the copy-constructor for a Pet object is used, which initializes the VPTR to the Pet VTABLE and copies only the Pet parts of the object. There’s no explicit copy-constructor here, so the compiler synthesizes one. Under all interpretations, the object truly becomes a Pet during slicing. */
        cout << p.description() << endl;
}

int main() {
        Pet p("Alfred");
        Dog d("Fluffy", "sleep");
        describe(p);
        describe(d);
} ///:~
