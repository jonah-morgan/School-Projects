#include <iostream>
#include "Fraction.h"
#include <vector>


int main() {
    std::vector<Fraction> fractions;
    fractions.insert(fractions.end(), Fraction(2,3));
    fractions.insert(fractions.end(), Fraction(2,7));
    fractions.insert(fractions.end(), Fraction(1,4));
    fractions.insert(fractions.end(), Fraction(3,11));

    for(int i = 0; i <= 1; i++){
        std::string frac1 = fractions[i].display();
        std::string frac2 = fractions[i+2].display();

        Fraction addFrac = fractions[i] + fractions[i+2];
        Fraction subFrac = fractions[i] - fractions[i+2];
        Fraction multFrac = fractions[i] * fractions[i+2];
        Fraction divFrac = fractions[i] / fractions[i+2];

        std::cout << frac1 << " * " << frac2 << " = " << multFrac.display() << "\n";
        std::cout << frac1 << " / " << frac2 << " = " << divFrac.display() << "\n";
        std::cout << frac1 << " + " << frac2 << " = " << addFrac.display() << "\n";
        std::cout << frac1 << " - " << frac2 << " = " << subFrac.display() << "\n";
        std::cout << std::endl;
    }

    return 0;
}



