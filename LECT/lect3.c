# include <stdio.h>

void swap(int *pv){
    int  t = pv[0]; pv[0] = pv[1]; pv[1] = t;   
}

int ar[10] = {400,134,28,15,1,0,99,1234,4321,5};
int main(){
    int n =sizeof(ar)/sizeof(ar[0]);
    int flag = 0;
    for (int i = 0; i < n; i ++){
        printf("%d, ", ar[i]);

    }

    for (int i =0; i < n; i ++){
        flag = 0;
        for (int j = 0; j < (n-1); j ++ ){
            if (ar[j] < ar[j + 1]){
                swap(&ar[j]);
                flag = 1;
            }
            
        }
        if (flag == 0)
            break;
    }
    printf("\n");
    char ch = ',';
    for (int i = 0; i < n; i ++){
        if (i == n-1)
            ch = ' ';
        printf("%05d%c", ar[i], ch);

    }
    return 0;
}