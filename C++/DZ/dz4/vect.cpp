#include <cstdio>
#include <cstdlib>
#include "vect.h"

// Глобальная функция ошибки
void errron(const char* p) {
    printf("%s\n", p);
    exit(1);
}   