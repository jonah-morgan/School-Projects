#include <iostream>
#include "Set.h"


int main() {

    node* setOne = nullptr;
    insert(setOne, -5);
    insert(setOne, 0);
    insert(setOne, 1);
    insert(setOne, 4);
    insert(setOne, 0);
    insert(setOne, 2);
    insert(setOne,4);
    insert(setOne, 21);
    insert(setOne, 10000);

    node* setTwo = nullptr;
    insert(setTwo, 0);
    insert(setTwo, 4);
    insert(setTwo, 2);
    insert(setTwo, 21);
    insert(setTwo, 45);
    insert(setTwo, 56);

    displaySetFuncs(setOne, setTwo);
    return 0;
}
