#include <string>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

#define SIZE 10

int main()
{
        fstream testFile;

        testFile.open("TestFile.txt", fstream::out | fstream::in | fstream::app);
        if (!testFile.is_open()) {
                cout << "Could not open file, error: " << errno << endl;
                exit(1);
        }

        char *buffer = new char[SIZE];
        if (NULL == buffer) {
                cout << "Could not allocate memory, error: " << errno << endl;
                exit(1);
        }

        char *buffer1 = new char[SIZE];
        if (NULL == buffer1) {
                cout << "Could not allocate memory, error: " << errno << endl;
                exit(1);
        }

        memset(buffer, 'c', SIZE);
        testFile.write(buffer, SIZE);
        if (testFile)
                std::cout << "all characters written successfully\n";
        else
                std::cout << "error: only " << testFile.gcount() << " could be read: " << errno << endl;

        testFile.seekg (0, testFile.beg);
        testFile.read(buffer1, SIZE);
        if (testFile)
                std::cout << "all characters read successfully\n";
        else
                std::cout << "error: only " << testFile.gcount() << " could be read: " << errno << endl;

        cout << buffer1 << "and " << buffer << endl;


        if (strcmp(buffer1, buffer) == 0)
                cout << "Wow!, strings are equal" << endl;
        else
                cout << "Ooops!, strings are not equal" << endl;

        testFile.close();
        remove("TestFile.txt");

        delete []buffer;
        delete []buffer1;

        return 0;
}
