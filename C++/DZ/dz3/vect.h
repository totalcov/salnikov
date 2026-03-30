#pragma once
#include "MySatun.h"

class vect {
private:
    MySatun* v;
    int sz;

public:
    vect(int s);                  // конструктор с размером
    vect();                       // дефолтный - размер 99
    vect(const vect& other);      // конструктор копирования
    vect(vect&& other);           // конструктор перемещения
    ~vect();                      // деструктор

    inline int size()           { return sz; }
    inline MySatun& elem(int i) { return v[i]; }

    MySatun& operator[](int i);           // доступ по индексу с проверкой

    void print() const;

     void resize(int new_size);

    void operator=(const vect& other);    // присваивание копированием
    void operator=(vect&& other);         // присваивание перемещением

    friend vect operator+(vect& a, vect& b);  // сложение
    friend vect operator-(vect& a, vect& b);  // вычитание
};

void errron(const char* p);