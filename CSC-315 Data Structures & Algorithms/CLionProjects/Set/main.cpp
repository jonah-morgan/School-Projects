#include <iostream>
#include "Set.h"


int main() {
    node* setOne = NULL;
    insert(setOne, -5);
    insert(setOne, 0);
    insert(setOne, 1);
    insert(setOne, 4);
    insert(setOne, 0);
    insert(setOne, 2);
    insert(setOne,4);
    insert(setOne, 21);
    insert(setOne, 10000);

    node* setTwo = NULL;
    insert(setTwo, 0);
    insert(setTwo, 4);
    insert(setTwo, 2);
    insert(setTwo, 21);
    insert(setTwo, 45);
    insert(setTwo, 56);

    node* unionSet = setUnion(setOne, setTwo);
    node* intersectionSet = setIntersection(setOne, setTwo);
    node* differenceSet = setDifference(setOne, setTwo);

    std::cout << "Size: " << size(setOne) << std::endl;
    displaySet(setOne);

    std::cout << "\n";

    std::cout << "Size: " << size(setTwo) << std::endl;
    displaySet(setTwo);

    std::cout << "\nIs s1 subset s2: " << isSubset(setOne, setTwo);
    std::cout << "\nEquality: " << isEqual(setOne, setTwo);

    std::cout << "\n\nUnion: ";
    displaySet(unionSet);
    std::cout << "\nIntersection: ";
    displaySet(intersectionSet);
    std::cout << "\nDifference: ";
    displaySet(differenceSet);

    return 0;
}
