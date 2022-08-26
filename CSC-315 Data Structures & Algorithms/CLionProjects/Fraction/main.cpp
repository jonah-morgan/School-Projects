#include <iostream>
#include "Fraction.h"
#include <vector>



void displayFunc(Fraction one, Fraction two, std::string type);

int main() {
    std::vector<Fraction> fractions;

    for(int i = 0; i < 20; i++){
        int randOne = rand() % 20 + 1;
        int randTwo = rand() % 20 + 1;
        fractions.insert(fractions.end(), Fraction(randOne, randTwo));
    }

    for(int i = 0; i < 16; i++){
        displayFunc(fractions[i], fractions[i+1], "add");
    }

    return 0;
}

void displayFunc(Fraction one, Fraction two, std::string type)
{
    if(type == "add"){
        one.display(); std::cout << " + "; two.display(); std::cout << " = ";
        one.add(two); one.display(); std::cout << std::endl;
    }
}


