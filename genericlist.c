#include "genericlist.h"

listDefine(int);

void printInt(int i) {
    printf("%d ", i);
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
    intListFor(list, printInt);

    intList* l2 = intListMap(list, addFive);
    intListFor(l2, printInt);
    printf("\n");

    intList* l3 = intListFilter(list, gtFive);
    intListFor(l3, printInt);
    printf("\n");

    intList* l4 = intListJoin(list, l2);
    intListFor(l4, printInt);
    printf("\n");

    intList* l5 = intListSort(l4, lt);
    intListFor(l5, printInt);
    printf("\n");

    intListFree(list);
    intListFree(l2);
    intListFree(l3);
    intListFree(l4);
    intListFree(l5);
}
