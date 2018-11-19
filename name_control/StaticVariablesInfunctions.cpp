#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

inline void require(bool requirement,
                const std::string& msg = "Requirement failed")
{
        using namespace std;

        if (!requirement) {
                fputs(msg.c_str(), stderr);
                fputs("\n", stderr);
                exit(1);
        }
}

char oneChar(const char* charArray = 0) {
  static const char* s; // s remembers its value between function call
  if(charArray) {
    s = charArray;
return *s; }
  else
    require(s, "un-initialized s");
  if(*s == '\0')
    return 0;
  return *s++;
}

char* a = "abcdefghijklmnopqrstuvwxyz";

int main() {
//  oneChar(); // require() fails
  oneChar(a); // Initializes s to a
  char c;
  while((c = oneChar()) != 0)
    cout << c << endl;
} ///:~
