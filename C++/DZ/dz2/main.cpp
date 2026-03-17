#include "MySatun.h"

int main() {
    MySatun a = 10.0;
    MySatun b(0.75);

    MySatun c = a + b;
    MySatun d = a - b;
    MySatun e = a * b;
    MySatun f = a / b;

    c.print();
    d.print();
    e.print();
    f.print();

    MySatun big(100000.0);  // превышает барьер при создании
    big.print();

    MySatun x(500.0);
    MySatun y(500.0);
    MySatun z = x * y;      // 500 * 500 = 250000 - превысит барьер
    z.print();

    return 0;

}