// Functions that are synthesized by the compiler
#include <iostream>
using namespace std;

class Gameboard {
        public:
        Gameboard() {cout << "Gameboard()\n";}
        Gameboard(const Gameboard&) {
                cout << "Gameboard(const Gameboard&)\n";
        }
        Gameboard& operator=(const Gameboard&) {
                cout << "Gameboard::operator=()\n";
                return *this;
        }
        ~Gameboard() {cout << "~Gameboard()\n";}
};

class Game {
        Gameboard gb; // composition
        public:
                // Default GameBoard constructor called:
                Game() { cout << "Game()\n"; }
                // You must explicitly call the GameBoard
                // copy-constructor or the default constructor // is automatically called instead:
                Game(const Game& g) :gb(g.gb) {
                        cout << "Game(const Game&)\n";
                }
                Game(int) {cout << "Game(int)\n";}
                Game& operator=(const Game& g) {
                
                    // You must explicitly call the GameBoard
                    // assignment operator or no assignment at
                    // all happens for gb!

                    gb = g.gb;
                    cout << "Game::operator=()\n";
                    return *this;
                }
                class other {}; // Nested class
                operator other() const {
                        cout << "Game::operator other()\n";
                        return other();
                }
                ~Game() {cout << "~Game()\n";}
};

class Chess:public Game {};

void f(Game::other) {}

class Checkers : public Game {
        public:
                //// Default base-class constructor called:
                Checkers() { cout << "Checkers()\n"; }
                // You must explicitly call the base-class copy constructor or the default constructor // will be automatically called instead: 
                Checkers(const Checkers& c) : Game(c) {
                cout << "Checkers(const Checkers& c)\n";
                }
                Checkers& operator=(const Checkers& c) {
                // You must explicitly call the base-class // version of operator=() or no base-class // assignment will happen:
                Game::operator=(c);
                cout << "Checkers::operator=()\n";
                return *this;
                }
};

int main(int argc, const char *argv[]) {
        Chess d1; // default constructor
        Chess d2(d1); // copy constructor
        //! chess d3(1) // Erro: no int constructor in chess class
        d1 = d2;    // operator= synthesized, provided by compiler
        f(d1); // Type-conversion is inherited
        Game::other go;
        //! d1 = go; // operator= not synthesized for different types
        Checkers c1, c2(c1);
        c1 = c2;

}
