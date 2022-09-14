#include <iostream>
#include "Set.h"

int main() {
    Set setOne = Set();
    setOne.insert(11);
    setOne.insert(2);
    setOne.insert(5);
    setOne.insert(1);
    setOne.insert(5);

    Set setTwo = Set();
    setTwo.insert(1);
    setTwo.insert(2);
    setTwo.insert(-44);

    displaySetFuncs(setOne, setTwo);
    return 0;
}
