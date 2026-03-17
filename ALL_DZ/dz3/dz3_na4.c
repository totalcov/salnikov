# include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *pv){
    int  t = pv[0]; pv[0] = pv[1]; pv[1] = t;   
}

void init_rng() {
    time_t curtime;
    time(&curtime);
    srand((unsigned int)curtime);
    rand(); rand(); rand();
}   

int gen_rnd_int() {
    return rand() % 1000;
}

int ar[21] = {0};
int main(){
    init_rng();
    int n =sizeof(ar)/sizeof(ar[0]);
    for (int i = 0; i < n; i ++){
        ar[i] = gen_rnd_int();
    }

    int flag = 0;
    for (int i = 0; i < n; i ++){
        printf("%d, ", ar[i]);

    }

    for (int i =1; i < n; i ++){
        int key = ar[i]; // берём элемент 
        int j = i-1; // берём предидущий элемент
        while (j>= 0 && ar[j]< key){ // если предидущий элемент меньше проверяемого 
            swap(&ar[j]); //то используем функцию свап, тоесть меняем элемен ты в списке местами с помощью указателе(и с помощью арифметики указателей)
            j--; // т.к у нас while, то уменьшаем j на один и заново будем проверять 
        }
        // таким образом, мы постоянно берём элемент, и сравниваем его с предидущими, ставя его в нужное место, это позволяет ускорить сортировку в уже немного отсортированном массиве.
    }
    printf("\n");
    char ch = ',';
    for (int i = 0; i < n; i ++){
        if (i == n-1)
            ch = ' ';
        printf("%4d%c", ar[i], ch);

    }
    printf("\n");
    if (n %2 == 0 )
        printf("%d ", ar[n/2 -1]);
    else printf("%d ", ar[n/2]);



    return 0;
}