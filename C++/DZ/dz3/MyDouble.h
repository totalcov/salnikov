#pragma once

class MyDouble {
protected:
    // mant хранит мантиссу, умноженную на SCALE
    // реальное число = (mant / SCALE) * 2^exp
    int mant;
    int exp;

    static const int SCALE = 8192; /// 

    // приводит mant и exp к нормализованному виду
    void normalize();

public:
    MyDouble(double value = 0.0);
    MyDouble(int mant, int exp);

    void print() const;

    friend MyDouble operator+(MyDouble a, MyDouble b);
    friend MyDouble operator-(MyDouble a, MyDouble b);
    friend MyDouble operator*(MyDouble a, MyDouble b);
    friend MyDouble operator/(MyDouble a, MyDouble b);
};
