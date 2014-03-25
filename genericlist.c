#include "genericlist.h"

listDefine(int);

void listPrint(intList* l) {
    intNode* n = l->start;

    while(n != NULL) {
        printf("%d ", n->data);
        n = n->next;
    }

    printf("\n");
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
    intList* list = intListNew();
    intListPushN(list, 5, 7, 3, 5, 156, 12);
    listPrint(list);

    intList* l2 = intListMap(list, addFive);
    listPrint(l2);

    intList* l3 = intListFilter(list, gtFive);
    listPrint(l3);

    intList* l4 = intListJoin(list, l2);
    listPrint(l4);

    intList* l5 = intListSort(l4, lt);
    listPrint(l5);

    intListFree(list);
    intListFree(l2);
    intListFree(l3);
    intListFree(l4);
    intListFree(l5);
}
