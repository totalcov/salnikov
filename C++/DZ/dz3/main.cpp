#include "vect.h"

int main() {
    vect a(4);
    a[0] = MySatun(1.0);
    a[1] = MySatun(2.0);
    a[2] = MySatun(3.0);
    a[3] = MySatun(4.0);

    vect b(3);
    b[0] = MySatun(4.0);
    b[1] = MySatun(5.0);
    b[2] = MySatun(6.0);

    vect c = a + b;   // {5, 7, 9}
    vect d = a - b;   // {-3, -3, -3}

    c.print();
    d.print();

    vect big(2);
    big[0] = MySatun(100000.0);  // насытится при создании
    big[1] = MySatun(500.0);

    vect x(2);
    x[0] = MySatun(500.0);
    x[1] = MySatun(500.0);

    vect sat = big + x;  // оба элемента превысят барьер
    sat.print();

    return 0;
}