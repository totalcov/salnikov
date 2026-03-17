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

int median(int ar[],int n){
    int z = 0;
    for (int i = 0; i < n; i ++){
        int count = 0;
        for (int j = 0; j < n; j ++){
            if( ar[i] >= ar[j])
                count ++;
            
        }
        if (count- 1 == (n/2))
            z = i;
    }
    return ar[z];

}

int ar[22] = {0};
int main(){
    init_rng();
    int n =sizeof(ar)/sizeof(ar[0]);
    for (int i = 0; i < n; i ++){
        ar[i] = gen_rnd_int();
    }

    int flag = 0;
    for (int i = 0; i < n; i ++){
        printf("%d,", ar[i]);

    }
    printf("\n");
    printf("%d", median(ar,n));
    // сортировка вставками более практична в наполовину отсортированном массиве, чем сортировка пузырьком.
    for (int i =1; i < n; i ++){
        int key = ar[i];
        int j = i-1;
        while (j>= 0 && ar[j]< key){
            swap(&ar[j]);
            j--;
        }

    }
    printf("\n");
    char ch = ',';
    for (int i = 0; i < n; i ++){
        if (i == n-1)
            ch = ' ';
        printf("%d%c", ar[i], ch);

    }
    printf("\n");
    if (n%2 ==0)
        printf("%d ", ar[n/2 -1]);
    else
        printf("%d ", ar[n/2]);
    return 0;
}