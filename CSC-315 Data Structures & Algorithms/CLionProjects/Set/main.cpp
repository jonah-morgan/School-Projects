#include <iostream>
#include "Set.h"


int main() {
    node* setOne = NULL;

//    insert(setOne, -5);
//    insert(setOne, 0);
//    insert(setOne, 1);
    insert(setOne, 4);
    insert(setOne, 0);
    insert(setOne, 2);
    insert(setOne,4);
    insert(setOne, 21);

    node* setTwo = NULL;
    insert(setTwo, 0);
    insert(setTwo, 4);
    insert(setTwo, 2);



    std::cout << "Size: " << size(setOne) << std::endl;
    displaySet(setOne);

    std::cout << std::endl;

    std::cout << "Size: " << size(setTwo) << std::endl;
    displaySet(setTwo);

    std::cout << "Is s1 subset s2: " << isSubset(setOne, setTwo);
    std::cout << "\nEquality: " << isEqual(setOne, setTwo);

    return 0;
}
