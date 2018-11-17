/* Note that you access members of an anonymous union just as if they were ordinary variables. The only difference is that both variables occupy the same space. If the anonymous union is at file scope (outside all functions and classes) then it must be declared static so it has internal linkage.
*/
int main() {
        union { int i;
                float f;
                };
        // Access members without using qualifiers:
        i = 12;
        f = 1.22;
} ///:~

