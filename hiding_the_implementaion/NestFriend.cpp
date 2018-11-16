// Nested friends
#include <iostream>
#include <cstring> // memset()
using namespace std;
const int sz = 20;

struct holder {
        private:
                int a[sz];
        public:
                void initialize(void);
 //               struct pointer; // declare, this step in not mandatory after c11++
 //                friend pointer; // this statement together with above statement is same as below one.
                friend  struct pointer; // make friend
                struct pointer { // define, this way pointer can access private data of holder
                        private:
                                holder *h;
                                int *p;
                        public:
                                void initialize(holder *h);
                                // mover around the array
                                void next();
                                void previous();
                                void top();
                                void end();
                                // Access Values
                                int read();
                                void set(int i);
                };
};

void holder::initialize() {
        memset(a, 0, sz*sizeof (int));
}

void holder::pointer::initialize(holder *rv) {
        h = rv;
        p = rv->a;
}

void holder::pointer::next() {
        if (p < &(h->a[sz-1])) p++;
}

void holder::pointer::previous() {
        if (p > &(h->a[sz-1])) p--;
}

void holder::pointer::top() {
        p = &(h->a[0]);
}

void holder::pointer::end() {
        p = &(h->a[sz - 1]);
}

int holder::pointer::read() {
        return *p;
}

void holder::pointer::set(int i) {
        *p = i;
}
int main(int argc, const char *argv[]) {

        holder h;
        holder::pointer hp, hp2;
        int i;

        h.initialize();
        hp.initialize(&h);
        hp2.initialize(&h);

        for(i = 0; i < sz; i++) {
                hp.set(i);
                hp.next();
        }

        hp.top();
        hp2.end();

        for(i=0;i<sz;i++) {
                cout << "hp =" << hp.read() << ", hp2 = " << hp2.read() << endl;
                hp.next();
                hp2.previous();
        }
        return 0;
}
