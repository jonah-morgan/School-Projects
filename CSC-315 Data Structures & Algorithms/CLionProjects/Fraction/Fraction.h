#ifndef FRACTION_FRACTION_H
#define FRACTION_FRACTION_H
#include <string>

class Fraction {
public:
    Fraction();
    Fraction(int n, int d = 1);

    std::string display();
    Fraction operator+(Fraction rhs);
    Fraction operator-(Fraction rhs);
    Fraction operator*(Fraction rhs);
    Fraction operator/(Fraction rhs);

private:
    int numerator;
    int denominator;
};

#endif //FRACTION_FRACTION_H
