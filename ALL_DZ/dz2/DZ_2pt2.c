#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a, b,c,d;

typedef long long int ll;
int *pa = &a, *pb = &b, *pc = &c, *pd = &d;
void init_rng(void) {
    time_t curtime;
    time(&curtime);
    srand((unsigned int) curtime);
    rand(); rand(); rand();
}

int gen_rnd_int(void){
    ll t = ((ll) rand() *1000) / RAND_MAX;
    return (int)t;

}

int main(void) {
    init_rng();
    a = gen_rnd_int();
    b = gen_rnd_int();
    c = gen_rnd_int();
    d = gen_rnd_int();
    printf("\n%d %d %d %d", a,b,c,d);
    printf("\n%d %d %d %d", *pa, *pb,*pc,*pd);
    
    int *temp;
    
    
    if (*pa > *pb) {
        temp = pa;
        pa = pb;
        pb = temp;
    }
    
    if (*pc > *pd) {
        temp = pc;
        pc = pd;
        pd = temp;
    }
    
    
    if (*pa > *pc) {
        temp = pa;
        pa = pc;
        pc = temp;
        
        temp = pb;
        pb = pd;
        pd = temp;
    }
    
    
    if (*pb > *pc) {
        temp = pb;
        pb = pc;
        pc = temp;
    }
    
    if (*pb > *pd) {
        temp = pb;
        pb = pd;
        pd = temp;
    }
    
    if (*pc > *pd) {
        temp = pc;
        pc = pd;
        pd = temp;
    }
    


    printf("\n%d %d %d %d", a,b,c,d);
    printf("\n%d %d %d %d", *pa, *pb, *pc, *pd);
    return 0;

}