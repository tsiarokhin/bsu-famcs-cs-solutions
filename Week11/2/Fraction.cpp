#include "Fraction.h"
#include <iostream>

using namespace std;

Fraction::Fraction(const int a, const double b): integer_part(a), float_part(b) {}

Fraction::Fraction(double other): Fraction((int)other, (other-(int)other)) {}

Fraction::Fraction(const Fraction& other): Fraction(other.integer_part, other.float_part) {}

Fraction::operator double() const
{
    return (double)(integer_part) + float_part;
}

ostream& operator<<(ostream& output, const Fraction& F)
{
    output << (double)F;
    return output;
}

istream& operator>>(istream& input, Fraction& F)
{
    double t;
    input >> t;
    F.integer_part = (int)t;
    F.float_part = t - (int)t;
    return input;
}

bool Fraction::operator<=(const Fraction& rhs) const
{
    return (double)(*this) <= (double)(rhs);
}

bool Fraction::operator>=(const Fraction& rhs) const
{
    return (double)(*this) >= (double)(rhs);
}

Fraction& Fraction::operator=(const Fraction& rhs)
{
    if (this == &rhs) return *this;
    integer_part = rhs.integer_part;
    float_part = rhs.float_part;
    return *this;
}

Fraction& Fraction::operator+=(const Fraction& rhs)
{
    integer_part += rhs.integer_part;
    float_part += rhs.float_part;
    return *this;
}

const Fraction Fraction::operator+(const Fraction& rhs) const
{
    Fraction t((double)(*this) + (double)(rhs));
    return t;
}

const Fraction Fraction::operator-(const Fraction& rhs) const
{
    Fraction t((double)(*this) - (double)(rhs));
    return t;
}

const Fraction Fraction::operator*(const Fraction& rhs) const
{
    Fraction t((double)(*this) * (double)(rhs));
    return t;
}
