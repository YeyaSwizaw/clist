#include "list.h"

list* listNew() {
    list* ptr = malloc(sizeof(*ptr));
    ptr->start = NULL;
    ptr->end = NULL;
    return ptr;
}

void listPush(list* l, int el) {
    node* n = malloc(sizeof(*n));
    n->data = el;
    n->next = NULL;

    if(l->start == NULL) {
        l->start = n;
    } else {
        l->end->next = n;
    }

    l->end = n;
}

void listPushN(list* l, int n, ...) {
    va_list args;
    va_start(args, n);

    for(; n > 0; n--) {
        listPush(l, va_arg(args, int));
    }

    va_end(args);
}

list* listMap(list* l, int(*f)(int)) {
    list* ret = listNew();
    node* n = l->start;

    while(n != NULL) {
        listPush(ret, f(n->data));
        n = n->next;
    }

    return ret;
}

list* listFilter(list* l, bool(*f)(int)) {
    list* ret = listNew();
    node* n = l->start;

    while(n != NULL) {
        if(f(n->data)) {
            listPush(ret, n->data);
        }
        n = n->next;
    }

    return ret;
}

list* listJoin(list* l1, list* l2) {
    list* ret = listNew();

    node* n = l1->start;
    while(n != NULL) {
        listPush(ret, n->data);
        n = n->next;
    }

    n = l2->start;
    while(n != NULL) {
        listPush(ret, n->data);
        n = n->next;
    }
    
    return ret;
}

list* listSort(list* l, bool(*f)(int, int)) {
    list* ret = NULL;
    node* n = l->start;
    if(n == NULL) {
        ret = listNew();
    } else if(n->next == NULL) {
        ret = listNew();
        listPush(ret, n->data);
    } else {
        list* lt = listNew();
        list* gt = listNew();

        n = n->next;
        while(n != NULL) {
            if(f(n->data, l->start->data)) {
                listPush(lt, n->data);
            } else {
                listPush(gt, n->data);
            }

            n = n->next;
        }

        listPush(lt, l->start->data);
        ret = listJoin(listSort(lt, f), listSort(gt, f));

        listFree(lt);
        listFree(gt);
    }

    return ret;
}


void listPrint(list* l) {
    node* n = l->start;

    while(n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }

    printf("\n");
}

void listFree(list* l) {
    node* n = l->start;

    while(n->next != NULL) {
        node* tmp = n->next;
        free(n);
        n = tmp;
    }

    free(n);
    free(l);
}

int addFive(int num) {
    return num + 5;
}

bool gtFive(int num) {
    return num > 5;
}

bool lt(int a, int b) {
    return a < b;
}

int main(int argc, char* argv[]) {
    list* l = listNew();
    listPushN(l, 3, 7, 2, 12);
    listPrint(l);

    list* l2 = listMap(l, addFive);
    listPrint(l2);

    list* l3 = listFilter(l, gtFive);
    listPrint(l3);

    list* l4 = listJoin(l, l2);
    listPrint(l4);

    list* l5 = listSort(l4, lt);
    listPrint(l5);

    listFree(l);
    listFree(l2);
    listFree(l3);
    listFree(l4);
    listFree(l5);
}
