#include <iostream>
#include <cstdlib>
using namespace std;

class Z{
    public:
        Z() {};
        static void* operator new(size_t dim) {
            cout << "Allocazione di memoria (" << dim << "byte)" << endl;
            void *p = malloc(dim);
            return p;
        }
        static void operator delete(void *p) {
            cout << "Deallocazione di memoria" << endl;
            free(p);
        }
};

int main(void) {
    Z* z = new Z;
    delete z;
    return 0;
}