#include <cstdio>
#include <cmath>
#include "MyDouble.h"

//  normalize
void MyDouble::normalize() {
    if (mant == 0) {
        exp = 0;
        return;
    }

    
    while (std::abs(mant) >= SCALE) {
        mant /= 2;
        exp++;
    }

    while (std::abs(mant) < SCALE / 2) {
        mant *= 2;
        exp--;
    }
}


//constructors
MyDouble::MyDouble(double value) {
    if (value == 0.0) {
        mant = 0;
        exp = 0;
        return;
    }

    exp = 0;

    while (std::abs(value) >= 1.0) {
        value /= 2.0;
        exp++;
    }

    while (std::abs(value) < 0.5) {
        value *= 2.0;
        exp--;
    }

    mant = static_cast<int>(value * SCALE);
    normalize();
}


MyDouble::MyDouble(int m, int e) {
    mant = m;
    exp = e;
    normalize();
}

//  print
void MyDouble::print() const {
    double value = (double)mant / SCALE;
    value *= std::pow(2.0, exp);

    printf("%.6f[%d ,%d] ", value, mant, exp);
}

// operators

/*
MyDouble operator+(MyDouble a, MyDouble b)
{
    // выравниваем экспоненты
    while (a.exp < b.exp) {
        a.mant /= 2;//????
        a.exp++;
    }

    while (b.exp < a.exp) {
        b.mant /= 2;
        b.exp++;
    }

    // складываем мантиссы
    return MyDouble(a.mant + b.mant, a.exp);
}




MyDouble operator-(MyDouble a, MyDouble b)
{
    // выравниваем экспоненты
    while (a.exp < b.exp) {
        a.mant /= 2;
        a.exp++;
    }

    while (b.exp < a.exp) {
        b.mant /= 2;
        b.exp++;
    }

    // вычитаем мантиссы
    return MyDouble(a.mant - b.mant, a.exp);
}
*/


MyDouble operator+(MyDouble a, MyDouble b) {
    long long ma = a.mant;
    long long mb = b.mant;

    // Поднимаем мантиссу с меньшей экспонентой,
    // пока экспоненты не сравняются.
    // Умножение на 2 — точная операция, биты не теряются.
    while (a.exp > b.exp) { ma <<= 1; a.exp--; }
    while (b.exp > a.exp) { mb <<= 1; b.exp--; }

    // Теперь экспоненты равны, складываем мантиссы
    return MyDouble(static_cast<int>(ma + mb), a.exp);
}

MyDouble operator-(MyDouble a, MyDouble b) {
    long long ma = a.mant;
    long long mb = b.mant;

    while (a.exp > b.exp) { ma <<= 1; a.exp--; }
    while (b.exp > a.exp) { mb <<= 1; b.exp--; }

    return MyDouble(static_cast<int>(ma - mb), a.exp);
}


MyDouble operator*(MyDouble a, MyDouble b) {
    long long m = static_cast<long long>(a.mant) * b.mant;
    m /= MyDouble::SCALE;
    return MyDouble(static_cast<int>(m), a.exp + b.exp);
}

MyDouble operator/(MyDouble a, MyDouble b) {
    long long m = static_cast<long long>(a.mant) * MyDouble::SCALE;
    m /= b.mant;
    return MyDouble(static_cast<int>(m), a.exp - b.exp);
}

