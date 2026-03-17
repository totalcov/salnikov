#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

# define N 10


void init_rng() {
    time_t curtime;
    time(&curtime);
    srand((unsigned int)curtime);
    rand(); rand(); rand();
}   

int gen_rnd_int() {
    return rand() % 1000;
}

// ОБЫЧНОЕ ДЕРЕВО, БЕЗ БАЛАНСИРОВКИ
struct tree{
    struct tree *pRight;
    struct tree *pLeft;
    int val;
};

typedef struct tree Tree;

Tree *createNew(int val){
    Tree *po = (Tree*)malloc(sizeof(Tree));
    if (po == NULL) return NULL;
    po->val = val;
    po->pRight = NULL;
    po->pLeft = NULL;
    return po;
}

Tree *insert(Tree *root, int val){
    if (root == NULL) return createNew(val);

    if (val < root->val){
        root->pLeft = insert(root->pLeft, val);
    }
    else if (val > root->val){
        root->pRight = insert(root->pRight, val);
    }
    return root;
}


// ДЕРЕВО АВЛ
struct avl {
    struct avl *pRight;
    struct avl *pLeft;
    int val;
    int count;   // число узлов в поддереве
};

typedef struct avl AVL;

AVL *createAVL(int val) {
    AVL *po = (AVL*)malloc(sizeof(AVL));
    if (po == NULL) return NULL;
    po->pLeft  = NULL;
    po->pRight = NULL;
    po->val    = val;
    po->count  = 1;
    return po;
}

int getCount(AVL *root) {
    if (root == NULL) return 0;
    return root->count;
}

void updateCount(AVL *root) {
    if (root == NULL) return;
    root->count = 1 + getCount(root->pLeft) + getCount(root->pRight);
}

/********** ПОВОРОТЫ **********/

AVL *rotateRight(AVL *y) {
    AVL *x = y->pLeft;
    AVL *t = x->pRight;

    x->pRight = y;
    y->pLeft  = t;

    updateCount(y);
    updateCount(x);
    return x;
}

AVL *rotateLeft(AVL *x) {
    AVL *y = x->pRight;
    AVL *t = y->pLeft;

    y->pLeft  = x;
    x->pRight = t;

    updateCount(x);
    updateCount(y);
    return y;
}

/********** БАЛАНСИРОВКА ПО КОЛИЧЕСТВУ УЗЛОВ **********/

#define MAX_DIFF 1

AVL *rebalanceBySizeStrict(AVL *root) {
    if (root == NULL) return root;

    int leftSize  = getCount(root->pLeft);
    int rightSize = getCount(root->pRight);
    int balance   = leftSize - rightSize;

    // условие уже выполняется
    if (balance >= -MAX_DIFF && balance <= MAX_DIFF) {
        return root;
    }

    // "косит" влево: левое поддерево значительно больше
    if (balance > MAX_DIFF) {
        // размеры подподдеревьев
        int leftLeftSize  = getCount(root->pLeft->pLeft);
        int leftRightSize = getCount(root->pLeft->pRight);

        // если левое-правое больше, чем левое-левое, сначала делаем левый поворот
        if (leftRightSize > leftLeftSize) {
            root->pLeft = rotateLeft(root->pLeft);
        }
        root = rotateRight(root);
    }
    // "косит" вправо: правое поддерево значительно больше
    else if (balance < -MAX_DIFF) {
        int rightLeftSize  = getCount(root->pRight->pLeft);
        int rightRightSize = getCount(root->pRight->pRight);

        if (rightLeftSize > rightRightSize) {
            root->pRight = rotateRight(root->pRight);
        }
        root = rotateLeft(root);
    }

    return root;
}

/********** ВСТАВКА С БАЛАНСИРОВКОЙ **********/

AVL *insertAVL(AVL *root, int val) {
    if (root == NULL) return createAVL(val);

    if (val < root->val) {
        root->pLeft = insertAVL(root->pLeft, val);
    } else if (val > root->val) {
        root->pRight = insertAVL(root->pRight, val);
    } else {
        // равные не вставляем
        return root;
    }

    updateCount(root);

    // балансировка по количеству узлов
    root = rebalanceBySizeStrict(root);

    return root;
}



// 1. Функция для вывода дерева с псевдографикой
void printTreeVisual(Tree *root, int space, int isRight) {
    if (root == NULL) return;
    // Сначала выводим правое поддерево
    printTreeVisual(root->pRight, space + 4, 1);
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
// 2. Функция для вывода AVL дерева с псевдографикой
void printAVLVisual(AVL *root, int space, int isRight) {
    if (root == NULL) return;
    // Сначала выводим правое поддерево
    printAVLVisual(root->pRight, space + 4, 1);
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
    printAVLVisual(root->pLeft, space + 4, 0);
}

/*
// НЕ НУЖНАЯ ФУНКЦИЯ, НО ОЧЕНЬ ОЧЕНЬ ЖАЛКО ЕЁ УДАЛЯТЬ 
AVL* rotateTree(AVL* root) {
    if (root == NULL || (root->pLeft == NULL && root->pRight == NULL)) {
        return root;
    }
    
    // Создаем стек для обхода дерева в глубину без рекурсии
    AVL* stack[N*N];
    int top = -1;
    
    // Массивы для хранения повернутых поддеревьев
    AVL* newRoot = NULL;
    
    // Начинаем с корня
    stack[++top] = root;
    
    while (top >= 0) {
        AVL* current = stack[top--];
        
        // Меняем местами левое и правое поддеревья
        AVL* temp = current->pLeft;
        current->pLeft = current->pRight;
        current->pRight = temp;
        
        // Добавляем дочерние узлы в стек
        if (current->pLeft != NULL) {
            stack[++top] = current->pLeft;
        }
        if (current->pRight != NULL) {
            stack[++top] = current->pRight;
        }
        
        // Если это корень, запоминаем его
        if (newRoot == NULL) {
            newRoot = current;
        }
    }
    
    return newRoot;
}
*/

int arr[N];
int main(){
    init_rng();
    for (int i = 0; i < N; i++){
        arr[i] = gen_rnd_int() % 100;
    }
    for( int i = 0 ; i < N; i++) printf("%d ", arr[i]);
    Tree *root = NULL;

    for (int i = 0; i < N ; i++){
        root = insert(root, arr[i]);
    }
    printf("\n");
    printf("Главный элемент: %d", root->val);
    printf("\n");


    printf("1.ДЕРЕВО БЕЗ БАЛАНСА :\n");
    printf("────────────────────────────────────────\n");
    printTreeVisual(root, 0, 0);
    printf("────────────────────────────────────────\n\n");


    AVL *rootAVL = NULL;
    for (int i = 0; i < N; i++){
        rootAVL = insertAVL(rootAVL, arr[i]);
    }
    printf("\n");
    printf("Главный элемент: %d", rootAVL->val);
    printf("\n");


    printf("2.СБАЛАНСИОРВАННОЕ ДЕРЕВО:\n");
    printf("────────────────────────────────────────\n");
    printAVLVisual(rootAVL, 0, 0);
    printf("────────────────────────────────────────\n\n");
    /*
    AVL* rootROTATE = rotateTree(rootAVL);

    printf("\n");


    printf("3.ПЕРЕВЁРНУТОЕ ДЕРЕВО:\n");
    printf("────────────────────────────────────────\n");
    printAVLVisual(rootROTATE, 0, 0);
    printf("────────────────────────────────────────\n\n");
    */

}