#include "Fraction.h"
#include <iostream>
#include <string>


Fraction::Fraction() {
    numerator = 0;
    denominator = 1;
}


Fraction::Fraction(int n, int d) {
    numerator = n;
    denominator = d;
}


void Fraction::display() {
    std::cout << numerator << "/" << denominator;
}


void Fraction::add(Fraction rhs) {
    numerator = (numerator * rhs.denominator) + (denominator * rhs.numerator);
    denominator = denominator * rhs.denominator;
}


void Fraction::subtract(Fraction rhs) {
    numerator = (numerator * rhs.denominator) - (denominator * rhs.numerator);
    denominator = denominator * rhs.denominator;
}


void Fraction::multiply(Fraction rhs) {
    numerator = numerator * rhs.numerator;
    denominator = denominator * rhs.denominator;
}


void Fraction::divide(Fraction rhs) {
    numerator = numerator * rhs.denominator;
    denominator = denominator * rhs.numerator;
}






