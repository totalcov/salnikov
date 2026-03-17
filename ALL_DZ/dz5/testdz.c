#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


# define N 13

void init_rng() {
    time_t curtime;
    time(&curtime);
    srand((unsigned int)curtime);
    rand(); rand(); rand();
}   

int gen_rnd_int() {
    return rand() % 1000;
}

struct tree
{
    struct tree *pRitght;
    struct tree *pLeft;
    int val;
    int count;
};


typedef struct tree TR;


// *!выделяем не освобождаем
TR *creatTree(int val){
    TR *po = (TR*)(malloc(sizeof(TR)));
    if (po == NULL) return NULL;
    po->pLeft = NULL;
    po->pRitght = NULL;
    po->val = val;
    po->count = 1;

    return po;
}


int getCount(TR *root){
    if (root == NULL) return 0;
    return root->count;
}


void updateCount(TR *root){
    if (root == NULL) return;
    root->count = 1 + getCount(root->pLeft) + getCount(root->pRitght);
}


void inOrder(TR *root, int *arr,  int *ind){
    if (root == NULL) return;

    inOrder(root->pLeft, arr, ind);
    arr[*ind] = root->val;
    (*ind)++;
    inOrder(root->pRitght, arr, ind);
}


void freeTree(TR *root){
    if (root == NULL) return ;

    freeTree(root->pLeft);
    freeTree(root->pRitght);
    free(root);
}


TR *buldBalancedSort(int *arr, int l, int r){
    if (l> r) return NULL;

    int mid = (l+r) / 2;

    TR *root = creatTree(arr[mid]);
    if (root == NULL) return NULL;

    root->pLeft = buldBalancedSort(arr, l, mid-1);
    root->pRitght = buldBalancedSort(arr, mid +1, r);

    updateCount(root);
    return root;
}


// *!выделяем освобождаем
TR *rebuildTree(TR *root){
    if (root == NULL) return root;

    int size = getCount(root);
    if (size == 0) return root;

    int *arr = (int*)malloc(size * sizeof(int));
    if (arr == NULL) return root;

    int ind = 0;

    inOrder(root, arr, &ind);
    // освобождаем старое дерево
    freeTree(root);

    TR *newRoot = buldBalancedSort(arr, 0, size-1);
    free(arr);
    return newRoot;
}


//проверка на необходимость ребилда
int needsR(TR *root){
    if (root == NULL ) return 0;

    int balance = (getCount(root->pLeft) - getCount(root->pRitght));

    return (balance > 1 || balance < -1); 
}


TR *insert(TR *root, int val){
    if (root == NULL) return  creatTree(val);

    if (val < root->val) root->pLeft = insert(root->pLeft, val);
    else if (val > root->val) root->pRitght = insert(root->pRitght, val); 
    else return root;

    updateCount(root);

    if (needsR(root)){
        TR *rebuilt = rebuildTree(root);
        if (rebuilt != NULL) root = rebuilt;
    }
    return root;
}


// 1. Функция для вывода дерева с псевдографикой
void printTreeVisual(TR *root, int space, int isRight) {
    if (root == NULL) return;
    // Сначала выводим правое поддерево
    printTreeVisual(root->pRitght, space + 4, 1);
    // Выводим отступы и связи
    for (int i = 0; i < space - 4; i++) {
        printf(" ");
    }
    
    // Выводим соединения между узлами
    if (space > 0) {
        if (isRight) {
            printf(" ┌──");
        } else {
            printf(" └──");
        }
    }
    
    // Выводим значение узла
    printf("%d\n", root->val);
    
    // Выводим левое поддерево
    printTreeVisual(root->pLeft, space + 4, 0);
}


int arr[N];
int main(){
    init_rng();
    for (int i = 0; i < N; i++){
        arr[i] = gen_rnd_int() % 100;
    }
    for( int i = 0 ; i < N; i++) printf("%d ", arr[i]);


    TR *rootAVL = NULL;
    for (int i = 0; i < N; i++){
        rootAVL = insert(rootAVL, arr[i]);
    }
    printf("\n");
    if (rootAVL != NULL)
        printf("Главный элемент: %d", rootAVL->val);
    else
        printf("Дерево пустое");
    printf("\n");


    printf("1.СБАЛАНСИОРВАННОЕ ДЕРЕВО:\n");
    printf("────────────────────────────────────────\n");
    printTreeVisual(rootAVL, 0, 0);
    printf("────────────────────────────────────────\n\n");


    return 0;
}
