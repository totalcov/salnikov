#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct town{
    struct town *pNext;
    struct town *pPrev;
    char Name[];
};

typedef struct town Town;
Town* pFirst = 0, * pLast = 0;

Town* Create(const char* name) {
  size_t len = strlen(name);
  Town* po = (Town*)malloc(sizeof(Town) + len + 1);
  if (po == 0) return 0;
  strncpy_s(po->Name, len + 2, name, len + 1);
  return po;
}

void Destroy(Town *po){
    if (po) free(po);
}

void AddToList(Town *po){
    if(pLast) pLast->pNext = po;
    po -> pPrev = pLast;
    pLast = po;
    po -> pNext = 0;
    if (pFirst == 0) pFirst = po;
}

void DelFromList(Town *po){//????
    if (po == NULL) return ;
    if(po-> pPrev != NULL){
        po->pPrev->pNext = po->pNext;
    }
    else pFirst = po->pNext;

    if (po->pNext !=NULL)  po->pNext->pPrev = po->pPrev;
    else pLast = po->pPrev;

    po->pNext = NULL;
    po->pPrev = NULL;
} // пишем сами


Town *Search4(const char *name){// найти город с таким именем и вернуть адресс структуры или 0 если такого города нет 
    Town *po = pFirst;
    while (po!= 0){
        if (strcmp(po->Name, name) == 0){
            return po;

        }
        po = po->pNext;
    }
    printf("ГОрод не найден");
    return 0;
}

void PrintAllTowns(void){
    printf("\n all Town list:");
    Town *po = pFirst;
    while (po != 0){
        printf(" \n %s", po->Name);
        po = po->pNext;

    }
}

void SortTowns(void){
    if (pFirst == NULL) return ;
    if (pFirst->pNext == NULL) printf("всего один город: %s", pFirst->Name);

    int swap = 1;
    while (swap){
        swap = 0;
        // сортировка пузырьком
        Town *cur = pFirst;
        while (cur != NULL && cur->pNext != NULL ){
            if (strcmp(cur->pNext->Name, cur->Name) < 0){
                Town *node1= cur;
                Town *node2 = cur->pNext;
                Town *prev = node1->pPrev;
                Town *next = node2->pNext;

                if (prev != NULL){
                    prev->pNext = node2;
                }
                else pFirst = node2;

                if (next != NULL){
                    next->pPrev = node1;
                }
                else pLast = node1;

                // обновить указатели
                node1->pPrev = node2;
                node1->pNext = next;
                node2->pPrev = prev;
                node2->pNext = node1;

                swap = 1;

                cur = node2;

            }
            cur = cur->pNext;

        }
        
    }
}


int main(void) {
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
  Town* po;
  po = Create("Saint Petersburg"); if (po == 0) return -1; AddToList(po);
  po = Create("Paris"); if (po == 0) return -1; AddToList(po);
  po = Create("Beijing"); if (po == 0) return -1; AddToList(po);
  po = Create("London"); if (po == 0) return -1; AddToList(po);
  po = Create("Tokyo"); if (po == 0) return -1; AddToList(po);
  po = Create("Moscow"); if (po == 0) return -1; AddToList(po);
  PrintAllTowns(); printf("\n");
  po = Search4("Paris"); DelFromList(po); Destroy(po);
  PrintAllTowns();printf("\n");
  SortTowns();
  PrintAllTowns();printf("\n");
  return 0;

}