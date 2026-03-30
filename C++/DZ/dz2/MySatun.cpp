#include <cstdio>
#include <cmath>
#include "MySatun.h"


void MySatun::saturate(){
    if (mant == 0) return;

    if (exp > MAX_EXP){
        satFlag = true;
        exp = MAX_EXP;
        mant = (mant > 0) ? (SCALE - 1): -(SCALE);
    }
    else if (exp < -MAX_EXP){
        satFlag = true;
        exp = 0;
        mant = 0;
    }
}

MySatun::MySatun(double value) : MyDouble(value), satFlag(false){
    saturate();
} 

MySatun::MySatun(int m, int e) : MyDouble(m,e), satFlag(false){
    saturate();
}

MySatun::MySatun(const MyDouble &other) : MyDouble(other), satFlag(false){
    saturate();
}

void MySatun::print() const {
    if (satFlag) printf("* ");
    MyDouble::print();
}


MySatun operator+(MySatun a, MySatun b){
    MySatun res = MyDouble(a) + MyDouble(b);
    res.saturate();//?????
    res.satFlag = a.satFlag || b.satFlag || res.satFlag;//????
    return res;
}

MySatun operator-(MySatun a, MySatun b){
    MySatun res = MyDouble(a) - MyDouble(b);
    res.saturate();
    res.satFlag = a.satFlag || b.satFlag || res.satFlag;
    return res;
}

MySatun operator*(MySatun a, MySatun b){
    MySatun res = MyDouble(a) * MyDouble(b);
    res.saturate();
    res.satFlag = a.satFlag || b.satFlag || res.satFlag;
    return res;
}

MySatun operator/(MySatun a, MySatun b){
    MySatun res = MyDouble(a) / MyDouble(b);
    res.saturate();
    res.satFlag = a.satFlag || b.satFlag || res.satFlag;
    return res;
}
