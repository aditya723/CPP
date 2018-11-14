//Copy one file to another, a line at a time i.e. contents of Scopy.cpp will copied into Scopy2.cpp

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char *argv[]) {

        ifstream in("Scopy.cpp"); // Open for reading
        ofstream out("Scopy2.cpp"); // Open for writing

        string s;

        while (getline(in, s)) // Discards newline char
                out << s << "\n"; // ... must add it back
}
