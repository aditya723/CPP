// Copy an entire file into a vector of string
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, const char *argv[]) {

        vector<string>v;
        ifstream in("Fillvector.cpp");

        string line;

        while (getline(in, line))
                v.push_back(line); // Add the line to the end
        // Add line numbers:

        int i = 0;
        for(i=0; i<v.size(); i++) {
                cout << i << ": " << v[i] << endl;
        }
}
