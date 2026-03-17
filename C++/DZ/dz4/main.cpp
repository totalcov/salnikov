#include <iostream>
#include "vect.h"
#include "MySatun.h"

int main() {
    // Vector<double>
    Vector<double> vd(5);
    vd[0] = 1.5;
    vd.print();
    
    // Vector<int>
    Vector<int> vi(3);
    vi[0] = 12;
    vi[1] = 20;
    vi[2] = vi[0] + vi[1];
    vi.print();
    
    // Vector<MySatun>
    Vector<MySatun> vs(3);
    vs[0] = MySatun(7.0);
    vs[1] = MySatun(2.5);
    vs[2] = MySatun(100000.0);  // насыщение
    vs.print(); 
    
    return 0;
}