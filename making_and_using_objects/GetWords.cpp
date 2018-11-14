// Break a file into whitespace-separated words
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, const char *argv[]) {
        vector<string>s;

        ifstream in("GetWords.cpp");

        string words;

        while (in >> words) {
                s.push_back(words);
        }

        int i = 0;
        for(; i < s.size(); i++) {
                cout << s[i] << endl;
        }

        return 0;
}
