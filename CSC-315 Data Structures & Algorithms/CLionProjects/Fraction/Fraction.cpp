#include "Fraction.h"
#include <iostream>
#include <string>
#include <sstream>


Fraction::Fraction() {
    numerator = 0;
    denominator = 1;
}


Fraction::Fraction(int n, int d) {
    numerator = n;
    denominator = d;
}


std::string Fraction::display() {
    std::stringstream myStr;
    myStr << numerator << "/" << denominator;
    return myStr.str();
}


Fraction Fraction::operator+(Fraction rhs) {
    int n = (numerator * rhs.denominator) + (denominator * rhs.numerator);
    int d = denominator * rhs.denominator;
    return Fraction(n, d);
}

Fraction Fraction::operator-(Fraction rhs) {
    int n = (numerator * rhs.denominator) - (denominator * rhs.numerator);
    int d = denominator * rhs.denominator;
    return Fraction(n, d);
}

Fraction Fraction::operator*(Fraction rhs) {
    int n = numerator * rhs.numerator;
    int d = denominator * rhs.denominator;
    return Fraction(n, d);
}

Fraction Fraction::operator/(Fraction rhs) {
    int n = numerator * rhs.denominator;
    int d = denominator * rhs.numerator;
    return Fraction(n, d);
}






