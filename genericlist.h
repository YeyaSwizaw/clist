#ifndef SAM_GENERIC_LIST_H
#define SAM_GENERIC_LIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

#define listDefine(type) \
typedef struct type##Node { \
    type data; \
    struct type##Node* next; \
} type##Node; \
\
typedef struct { \
    type##Node* start; \
    type##Node* end; \
} type##List; \
\
type##List* type##ListNew() { \
    type##List* ptr = malloc(sizeof(*ptr)); \
    ptr->start = NULL; \
    ptr->end = NULL; \
    return ptr; \
} \
\
void type##ListPush(type##List* l, type el) { \
    type##Node* n = malloc(sizeof(*n)); \
    n->data = el; \
    n->next = NULL; \
    \
    if(l->start == NULL) { \
        l->start = n; \
    } else { \
        l->end->next = n; \
    } \
    \
    l->end = n; \
} \
\
void type##ListPushN(type##List* l, int n, ...) { \
    va_list args; \
    va_start(args, n); \
    \
    for(; n > 0; n--) { \
        type##ListPush(l, va_arg(args, type)); \
    } \
    \
    va_end(args); \
} \
\
void type##ListFor(type##List* l, void(*f)(type)) { \
    type##Node* n = l->start; \
    \
    while(n != NULL) { \
        f(n->data); \
        n = n->next; \
    } \
} \
\
type##List* type##ListMap(type##List* l, type(*f)(type)) { \
    type##List* ret = type##ListNew(); \
    type##Node* n = l->start; \
    \
    while(n != NULL) { \
        type##ListPush(ret, f(n->data)); \
        n = n->next; \
    } \
    \
    return ret; \
} \
\
type##List* type##ListFilter(type##List* l, bool(*f)(type)) { \
    type##List* ret = type##ListNew(); \
    type##Node* n = l->start; \
    \
    while(n != NULL) { \
        if(f(n->data)) { \
            type##ListPush(ret, n->data); \
        } \
        n = n->next; \
    } \
    \
    return ret; \
} \
\
type##List* type##ListJoin(type##List* l1, type##List* l2) { \
    type##List* ret = type##ListNew(); \
    \
    type##Node* n = l1->start; \
    while(n != NULL) { \
        type##ListPush(ret, n->data); \
        n = n->next; \
    } \
    \
    n = l2->start; \
    while(n != NULL) { \
        type##ListPush(ret, n->data); \
        n = n->next; \
    } \
    \
    return ret; \
} \
\
void type##ListFree(type##List* l) { \
    type##Node* n = l->start; \
    \
    while(n->next != NULL) { \
        type##Node* tmp = n->next; \
        free(n); \
        n = tmp; \
    } \
    \
    free(n); \
    free(l); \
} \
\
type##List* type##ListSort(type##List* l, bool(*f)(type, type)) { \
    type##List* ret = NULL; \
    type##Node* n = l->start; \
    \
    if(n == NULL) { \
        ret = type##ListNew(); \
    } else if(n->next == NULL) { \
        ret = type##ListNew(); \
        type##ListPush(ret, n->data); \
    } else { \
        type##List* lt = type##ListNew(); \
        type##List* gt = type##ListNew(); \
        \
        n = n->next; \
        while(n != NULL) { \
            if(f(n->data, l->start->data)) { \
                type##ListPush(lt, n->data); \
            } else { \
                type##ListPush(gt, n->data); \
            } \
            \
            n = n->next; \
        } \
        \
        type##ListPush(lt, l->start->data); \
        ret = type##ListJoin(type##ListSort(lt, f), type##ListSort(gt, f)); \
        \
        type##ListFree(lt); \
        type##ListFree(gt); \
    } \
    \
    return ret; \
} 

/*
list* listNew();
void listPush(list* l, int el);
void listPushN(list* l, int n, ...);
list* listMap(list* l, int(*f)(int));
list* listFilter(list* l, bool(*f)(int));
list* listJoin(list* l1, list* l2);
list* listSort(list* l, bool(*f)(int, int));
void listPrint(list* l);
void listFree(list* l);
*/

#endif // SAM_GENERIC_LIST_H
