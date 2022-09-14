#include <iostream>
#include "Set.h"

int main() {
    Set setOne = Set();
    setOne.insert(10);
    setOne.insert(34);
    setOne.insert(4);
    setOne.insert(7);
    setOne.insert(8);

    Set setTwo = Set();
    setTwo.insert(3);
    setTwo.insert(5);
    setTwo.insert(11);
    setTwo.insert(8);

    displaySetFuncs(setOne, setTwo);
    return 0;
}
