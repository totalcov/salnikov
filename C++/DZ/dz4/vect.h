#pragma once
#include <iostream>
#include "MySatun.h"


void errron(const char* p);

template <typename T>
class Vector {
private:
    T* v;
    int sz;

public:
    // Конструктор с размером
    Vector(int s) {
        if (s < 1) errron("invalid size");
        sz = s;
        v = new T[sz]();
        if (v == 0) errron("bad alloc");
    }

    // Дефолтный конструктор
    Vector() : Vector(99) {
    }

    // Конструктор копирования
    Vector(const Vector& other) : Vector(other.sz) {
        for (int i = 0; i < sz; i++)
            v[i] = other.v[i];
    }

    // Конструктор перемещения
    Vector(Vector&& other) {
        v = other.v;
        sz = other.sz;
        other.v = nullptr;
        other.sz = 0;
    }

    // Деструктор
    ~Vector() {
        delete[] v;
    }

    // Размер вектора
    inline int size() { return sz; }

    // Доступ по индексу с проверкой
    T& operator[](int i) {
        if (i < 0 || i >= sz) errron("invalid index");
        return v[i];
    }

    // Присваивание копированием
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        if (sz != other.sz) errron("size mismatch");
        for (int i = 0; i < sz; i++)
            v[i] = other.v[i];
        return *this;
    }

    // Присваивание перемещением
    Vector& operator=(Vector&& other) {
        if (this == &other) return *this;
        if (sz != other.sz) errron("size mismatch");
        delete[] v;
        v = other.v;
        sz = other.sz;
        other.v = nullptr;
        other.sz = 0;
        return *this;
    }

    // Метод print - выводит все элементы
    void print(void) {
        std::cout << "Vector[" << sz << "]: ";
        for (int i = 0; i < sz; i++) {
            std::cout << v[i];
            if (i < sz - 1) std::cout << ", ";
        }
        std::cout << std::endl;
    }

    // Сложение векторов
    template <typename U>
    friend Vector<U> operator+(Vector<U>& a, Vector<U>& b);

    // Вычитание векторов
    template <typename U>
    friend Vector<U> operator-(Vector<U>& a, Vector<U>& b);
};

// Сложение
template <typename T>
Vector<T> operator+(Vector<T>& a, Vector<T>& b) {
    if (a.sz != b.sz) errron("size mismatch");
    Vector<T> res(a.sz);
    for (int i = 0; i < a.sz; i++)
        res.v[i] = a.v[i] + b.v[i];
    return res;
}

// Вычитание
template <typename T>
Vector<T> operator-(Vector<T>& a, Vector<T>& b) {
    if (a.sz != b.sz) errron("size mismatch");
    Vector<T> res(a.sz);
    for (int i = 0; i < a.sz; i++)
        res.v[i] = a.v[i] - b.v[i];
    return res;
}

template <>
inline void Vector<MySatun>::print(void) {
    std::cout << "Vector[" << sz << "]:";
    for (int i = 0; i < sz; i++) {
        std::cout << " [" << i << "] = ";
        v[i].print();
    }
}