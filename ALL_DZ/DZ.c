#include <stdio.h>

int a;
short b;

int main() {
    flag1:
        printf("enter the number a[0:1000000000]:");
        scanf("%d", &a);
        if (a < 0 || a > 1000000000) {
            printf("incorrect number entered\n");
            goto flag1;
        }
    
    flag2:
        printf("enter the number b[2:32]:");
        scanf("%hd", &b);
        if (2 < 0 || b > 32) {
            printf("incorrect number entered\n");
            goto flag2;
        } 
    int pow = 1;
    flag3:
        if (pow <= a/b){
            pow *= b;
            goto flag3;
        }
    flag4:
        if (a > 0) {
            int d = a/pow;
            a %= pow;
            pow /= b;
            if (pow == 0){
                printf("%d", d);
            }
            else {
                printf("%d,", d);}
            goto flag4;

        }
    return 0;
}

