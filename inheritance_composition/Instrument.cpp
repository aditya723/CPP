// Inheritance & upcasting
#include <iostream>
using namespace std;

enum note { middleC, Csharp, Cflat }; // Etc.

class Instrument {
        public:
                void play(note) const {cout << "Playing Instrument\n";}
};

// Wind objects are Instruments
// because they have the same interface:
class Wind : public Instrument {};

void tune(Instrument& i) {
        // ...
        i.play(middleC);
}

int main() {
        Wind flute;
        tune(flute); // Upcasting
} ///:~

