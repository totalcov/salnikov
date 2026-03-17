#include "MyDouble.h"

int main() {
    MyDouble a=10.0;
    MyDouble b(0.75);

    MyDouble c = a + b;
    MyDouble d = a - b;
    MyDouble e = a * b;
    MyDouble f = a / b;

    c.print();
    d.print();
    e.print();
    f.print();

    return 0;
}
