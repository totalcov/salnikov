#pragma once
#include "MyDouble.h"

#define MAX_EXP 16


class MySatun : public MyDouble{
private:
    bool satFlag;
    void saturate();

public:
    MySatun(double value = 0.0);
    MySatun(int m, int e);
    MySatun(const MyDouble &other);

    void print() const;

    friend MySatun operator+(MySatun a, MySatun b);
    friend MySatun operator-(MySatun a, MySatun b);
    friend MySatun operator*(MySatun a, MySatun b);
    friend MySatun operator/(MySatun a, MySatun b);


};