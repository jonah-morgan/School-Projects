#include <iostream>
#include "Set.h"


int main() {
    node* headptr;

    insert(headptr, 0);
    insert(headptr, 1);
    insert(headptr, 4);
    insert(headptr, 0);
    insert(headptr, 1);
    insert(headptr, 3);
    insert(headptr, 3);
    insert(headptr, -3);

    displaySet(headptr);

    return 0;
}
