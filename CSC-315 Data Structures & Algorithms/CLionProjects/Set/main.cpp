#include <iostream>
#include "Set.h"


int main() {

    node* setOne = nullptr;
    insert(setOne, 10);
    insert(setOne, 34);
    insert(setOne, 4);
    insert(setOne, 7);
    insert(setOne, 8);

    node* setTwo = nullptr;
    insert(setTwo, 3);
    insert(setTwo, 5);
    insert(setTwo, 11);
    insert(setTwo, 8);

    displaySetFuncs(setOne, setTwo);
    return 0;
}
