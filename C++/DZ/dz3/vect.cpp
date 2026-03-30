#include <cstdio>
#include <cstdlib>
#include "vect.h"

// глобальная функция ошибки
void errron(const char* p) {
    printf(p);
    exit(1);
}


vect::vect(int s) {
    if (s < 1) errron("invalid size");
    sz = s;
    v = new MySatun[sz];
    if (v == 0) errron("bad alloc");
}


vect::vect() : vect(99) {
}
// конструктор копирования, при использовании оригинал живёт
vect::vect(const vect& other) : vect(other.sz) {
    for (int i = 0; i < sz; i++)
        v[i] = other.v[i];
}

// конструктор перемещения - забираем данные у временного объекта
vect::vect(vect&& other) {
    v = other.v;    // забираем указатель
    sz = other.sz;  // забираем размер
    other.v = 0;    // оригинал теперь пустой
    other.sz = 0;
}

// деструктор
vect::~vect() {
    delete[] v;
}

// доступ по индексу с проверкой
MySatun& vect::operator[](int i) {
    if (i < 0 || i >= sz) errron("invalid index");
    return v[i];
}

void vect::resize(int new_size) {
    if (new_size < 1) errron("invalid size");
    if (new_size == sz) return;  // размер уже подходит
    
    MySatun* new_v = new MySatun[new_size];
    if (new_v == 0) errron("bad alloc");
    
    // копируем существующие элементы
    int copy_size = (new_size < sz) ? new_size : sz;
    for (int i = 0; i < copy_size; i++) {
        new_v[i] = v[i];
    }
    
    // если увеличиваем размер, новые элементы уже инициализированы нулями
    // благодаря конструктору по умолчанию MySatun(double value = 0.0)
    
    // освобождаем старый массив и переключаемся на новый
    delete[] v;
    v = new_v;
    sz = new_size;
}

// присваивание копированием - оригинал живёт
void vect::operator=(const vect& other) { 
    if (this == &other) return;
    
    if (sz!= other.sz){
        delete[] v;
        sz = other.sz;
        v = new MySatun[sz];

    }
    for ( int i = 0; i < sz; i++){
        v[i] = other.v[i];
        }
}

// присваивание перемещением - забираем данные
void vect::operator=(vect&& other) {
    if (this == &other) return;
    delete[] v;             // освобождаем свои старые данные
    v  = other.v;           // забираем указатель у временного
    sz = other.sz;
    other.v  = nullptr;     // обнуляем донора
    other.sz = 0;
}

vect operator+(vect& a, vect& b) {
    if (a.sz < b.sz) {
        a.resize(b.sz);  // расширяем a до размера b
    } else if (b.sz < a.sz) {
        b.resize(a.sz);  // расширяем b до размера a
    }
    
    // теперь размеры равны, выполняем сложение
    vect res(a.sz);
    for (int i = 0; i < a.sz; i++)
        res.v[i] = a.v[i] + b.v[i];
    return res;
}
 
// вычитание с автоматическим расширением меньшего вектора
vect operator-(vect& a, vect& b) {
    if (a.sz < b.sz) {
        a.resize(b.sz);  // расширяем a до размера b
    } else if (b.sz < a.sz) {
        b.resize(a.sz);  // расширяем b до размера a
    }
    
    // теперь размеры равны, выполняем вычитание
    vect res(a.sz);
    for (int i = 0; i < a.sz; i++)
        res.v[i] = a.v[i] - b.v[i];
    return res;
}



/*
vect operator+(vect& a, vect& b) {
    if (a.sz != b.sz) errron("size mismatch");
    vect res(a.sz);
    for (int i = 0; i < a.sz; i++)
        res.v[i] = a.v[i] + b.v[i];
    return res;
}

// вычитание
vect operator-(vect& a, vect& b) {
    if (a.sz != b.sz) errron("size mismatch");
    vect res(a.sz);
    for (int i = 0; i < a.sz; i++)
        res.v[i] = a.v[i] - b.v[i];
    return res;
}
*/
void vect::print() const {
    printf("[ ");
    for (int i = 0; i < sz; i++) v[i].print();
    printf("]\n");
}