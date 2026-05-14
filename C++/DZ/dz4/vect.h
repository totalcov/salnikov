#pragma once
#include <iostream>
#include "MySatun.h"

void errron(const char* p);

// Forward declaration
template <typename T>
class Vector;

// operator<< для Vector - нужен для вложенных векторов
template <typename T>
 std::ostream& operator<<(std::ostream& os, const Vector<T>& vec);

template <typename T>
class Vector {
private:
    T* v;
    int sz;

public:
    
    template <typename... Args>
    Vector(int s, Args... args) {
        if (s < 1) throw std::invalid_argument("Неверный размер");
        sz = s;
        v = new T[sz];  // Выделяем память БЕЗ инициализации
        if (v == 0) throw std::bad_alloc();
        
        // Инициализируем каждый элемент с переданными аргументами
        for (int i = 0; i < sz; i++) {
            new (&v[i]) T(args...);  
        }
    }



// Конструктор с размером
    Vector(int s) {
        if (s < 1) throw std::invalid_argument("Неверный размер");
        sz = s;
        v = new T[sz]();
        if (v == 0) throw std::bad_alloc();
    }

    // Дефолтный конструктор
    Vector() : Vector(99){

    }

    // Конструктор копирования
    Vector(const Vector& other) : Vector(other.sz) {
        for (int i = 0; i < sz; i++)
            v[i] = other.v[i];
    }

    // Конструктор перемещения
    Vector(Vector&& other) noexcept {
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
    inline int size() const { return sz; }

    // Доступ по индексу с проверкой
    T& operator[](int i) {
        if (i < 0 || i >= sz) throw std::out_of_range("Неверный индекс");
        return v[i];
    }

    // Константный доступ по индексу
    const T& operator[](int i) const {
        if (i < 0 || i >= sz) throw std::out_of_range("Неверный индекс");
        return v[i];
    }

    // Присваивание копированием
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;
        if (sz != other.sz){
            delete[] v;
            sz = other.sz;
            v = new T[sz];
        }
        for (int i = 0; i < sz; i++)
            v[i] = other.v[i];
        return *this;
    }

    // Присваивание перемещением
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;
        delete[] v;
        v = other.v;
        sz = other.sz;
        other.v = nullptr;
        other.sz = 0;
        return *this;
    }

    // Метод print - выводит все элементы
    void print(void) const {
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

    // Оператор вывода для вложенных векторов
    friend std::ostream& operator<< <T>(std::ostream& os, const Vector<T>& vec);
};

// Сложение
template <typename T>
Vector<T> operator+(Vector<T>& a, Vector<T>& b) {
    if (a.sz != b.sz) throw std::invalid_argument("Несоответствие размеров");
    Vector<T> res(a.sz);
    for (int i = 0; i < a.sz; i++)
        res.v[i] = a.v[i] + b.v[i];
    return res;
}

// Вычитание
template <typename T>
Vector<T> operator-(Vector<T>& a, Vector<T>& b) {
    if (a.sz != b.sz) throw std::invalid_argument("Несоответствие размеров");
    Vector<T> res(a.sz);
    for (int i = 0; i < a.sz; i++)
        res.v[i] = a.v[i] - b.v[i];
    return res;
}

//Оператор вывода для Vector<T> - поддерживает вложенные векторы
template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
    os << "Vector[" << vec.size() << "]: ";
    for (int i = 0; i < vec.size(); i++) {
        os << vec[i];
        if (i < vec.size() - 1) os << ", ";
    }
    return os;
}



// Специализация print для MySatun
template <>
inline void Vector<MySatun>::print(void) const {
    std::cout << "Vector[" << sz << "]:";
    for (int i = 0; i < sz; i++) {
        std::cout << " [" << i << "] = ";
        v[i].print();
    }
    std::cout << std::endl;
}