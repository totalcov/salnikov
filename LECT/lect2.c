#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int a, b;

typedef long long int ll;
int *pa = &a, *pb = &b;
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
    printf("\n%d %d", a,b);
    printf("\n%d %d", *pa, *pb);
    int *pt = pb;
    pb = pa;
    pa = pt;
    printf("\n%d %d", a,b);
    printf("\n%d %d", *pa, *pb);
    return 0;

}