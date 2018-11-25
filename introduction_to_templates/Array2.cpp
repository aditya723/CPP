template<class T>
class Array {
        enum { size = 100 };
        T A[size];
        public:
        T& operator[](int index);
};

// Non-inline template definition
/* Any reference to a template’s class name must be accompanied by its template argument list, as in Array<T>::operator[.]You can imagine that internally, the class name is being decorated with the arguments in the template argument list to produce a unique class name identifier for each template instantiation. */
template<class T>
T& Array<T>::operator[](int index) {
        return A[index];
}
int main() {
        Array<float> fa;
        fa[0] = 1.414;
} ///:~
