#include <iostream>
#include "Set.h"


int main() {
    node* setOne = NULL;

//    insert(setOne, -5);
//    insert(setOne, 0);
//    insert(setOne, 1);
    insert(setOne, 4);

    node* setTwo = NULL;
    insert(setTwo, 0);
    insert(setTwo, 4);
    insert(setTwo, 2);



    std::cout << "Size: " << size(setOne) << std::endl;
    displaySet(setOne);

    std::cout << std::endl;

    std::cout << "Size: " << size(setTwo) << std::endl;
    displaySet(setTwo);

    std::cout << "Is setone a subset of setTwo?: " << isSubset(setOne, setTwo);

    return 0;
}
