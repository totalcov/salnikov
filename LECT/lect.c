# include <stdio.h>
# include <stdlib.h>

int main(){
    //
    char *p;
    p = (char*)malloc(10);
    char *p2;

    p2 = (char*)realloc(p, 20);

    if (p2){
        
    }


    int **table, rn, cn;
    rn = 10;
    cn = 15;
    table = (int**)calloc(rn, sizeof(int*));
    for (int i = 0; i < rn; i++){
        table[i] = (int*)calloc(cn, sizeof(int));
    }
    table[2][0] = 100;
    for (int i = 0; i < rn; i++) free(table[i]);
    free(table);

}