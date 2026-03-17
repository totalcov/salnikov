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

void DelFromList(Town *po); // пишем сами


Town *Search4(const char *name); // найти город с таким именем и вернуть адресс структуры или 0 если такого города нет 

void PrintAllTowns(void){
    printf("\n all Town list:");
    Town *po = pFirst;
    while (po != 0){
        printf(" \n %s", po->Name);
        po = po->pNext;

    }
}

void SortTowns(void);

int main(){
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF|_CRTDBG_CHECK_ALWAYS_DF);
    Town *po;
    po = Create("Saint Peterburg"); if (po == 0)return -1;AddToList(po);

    //добавить ещё городов
    PrintAllTowns();
    po = Search4("Paris"); DelFromList(po); Destroy(po);
    PrintAllTowns();
    SortTowns();
    PrintAllTowns();
    return 0;
}

