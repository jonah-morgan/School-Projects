#include <iostream>
#include "Set.h"


int main() {
    node* headptr = NULL;

    insert(headptr, 235);
    insert(headptr, 0);
    insert(headptr, 1);
    insert(headptr, 4);
    insert(headptr, 1);
    insert(headptr, 3);
    insert(headptr, 3);
    insert(headptr, -3);


    std::cout << "Size: " << size(headptr) << std::endl;
    displaySet(headptr);

    return 0;
}
