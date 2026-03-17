#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>  // Добавляем для uintptr_t

int a, b, c, d;
typedef long long int ll;
int *pa = &a, *pb = &b, *pc = &c, *pd = &d;

void init_rng(void) {
    time_t curtime;
    time(&curtime);
    srand((unsigned int)curtime);
    rand(); rand(); rand();
}

int gen_rnd_int(void) {
    ll t = ((ll)rand() * 1000) / RAND_MAX;
    return (int)t;
}

int main(void) {
    init_rng();
    a = gen_rnd_int();
    b = gen_rnd_int();
    c = gen_rnd_int();
    d = gen_rnd_int();
    printf("\n%d %d %d %d", a, b, c, d);
    printf("\n%d %d %d %d", *pa, *pb, *pc, *pd);

    // Исправленные блоки с uintptr_t
    if (*pa > *pb) {
        pa = (int*)((uintptr_t)pa ^ (uintptr_t)pb);
        pb = (int*)((uintptr_t)pa ^ (uintptr_t)pb);
        pa = (int*)((uintptr_t)pa ^ (uintptr_t)pb);
    }
    
    if (*pc > *pd) {
        pc = (int*)((uintptr_t)pc ^ (uintptr_t)pd);
        pd = (int*)((uintptr_t)pc ^ (uintptr_t)pd);
        pc = (int*)((uintptr_t)pc ^ (uintptr_t)pd);
    }
    
    if (*pa > *pc) {
        pa = (int*)((uintptr_t)pa ^ (uintptr_t)pc);
        pc = (int*)((uintptr_t)pa ^ (uintptr_t)pc);
        pa = (int*)((uintptr_t)pa ^ (uintptr_t)pc);
        
        pb = (int*)((uintptr_t)pb ^ (uintptr_t)pd);
        pd = (int*)((uintptr_t)pb ^ (uintptr_t)pd);
        pb = (int*)((uintptr_t)pb ^ (uintptr_t)pd);
    }
    
    if (*pb > *pc) {
        pb = (int*)((uintptr_t)pb ^ (uintptr_t)pc);
        pc = (int*)((uintptr_t)pb ^ (uintptr_t)pc);
        pb = (int*)((uintptr_t)pb ^ (uintptr_t)pc);
    }
    
    if (*pb > *pd) {
        pb = (int*)((uintptr_t)pb ^ (uintptr_t)pd);
        pd = (int*)((uintptr_t)pb ^ (uintptr_t)pd);
        pb = (int*)((uintptr_t)pb ^ (uintptr_t)pd);
    }
    
    if (*pc > *pd) {
        pc = (int*)((uintptr_t)pc ^ (uintptr_t)pd);
        pd = (int*)((uintptr_t)pc ^ (uintptr_t)pd);
        pc = (int*)((uintptr_t)pc ^ (uintptr_t)pd);
    }

    printf("\n%d %d %d %d", a, b, c, d); 
    printf("\n%d %d %d %d", *pa, *pb, *pc, *pd);  
    return 0;
}