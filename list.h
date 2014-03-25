#ifndef SAM_LIST_H
#define SAM_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} node;

typedef struct {
    node* start;
    node* end;
} list;

list* listNew();
void listPush(list* l, int el);
void listPushN(list* l, int n, ...);
list* listMap(list* l, int(*f)(int));
list* listFilter(list* l, bool(*f)(int));
list* listJoin(list* l1, list* l2);
list* listSort(list* l, bool(*f)(int, int));
void listPrint(list* l);
void listFree(list* l);

#endif // SAM_LIST_H
