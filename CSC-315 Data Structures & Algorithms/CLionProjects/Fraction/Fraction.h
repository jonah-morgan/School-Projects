#ifndef FRACTION_FRACTION_H
#define FRACTION_FRACTION_H
#include <string>

class Fraction {
public:
    Fraction();
    Fraction(int n, int d = 1);
    void display();

    void add(Fraction rhs);
    void subtract(Fraction rhs);
    void multiply(Fraction rhs);
    void divide(Fraction rhs);

private:
    int numerator;
    int denominator;
};

#endif //FRACTION_FRACTION_H
