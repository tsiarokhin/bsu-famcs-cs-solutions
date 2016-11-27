#include <iostream>
#include "Rational.h"

using namespace std;

void Rational::print()
{
    cout << a << '/' << b;
}

int gcd(int a, int b)
{
    while ((a %= b) && (b %= a));
    return a | b;
}

void Rational::reduce()
{
    int t = gcd(a, b);
    a /= t;
    b /= t;
    if (b < 0){
        a *= -1;
        b *= -1;
    }
}

Rational Rational::add(const Rational &rhs) const
{
    Rational t(a*rhs.b + rhs.a*b, b*rhs.b);
    t.reduce();
    return t;
}

Rational Rational::mul(const Rational &rhs) const
{
    Rational t(a*rhs.a, b*rhs.b);
    t.reduce();
    return t;
}

Rational Rational::div(const Rational &rhs) const
{
    Rational t(a*rhs.b, b*rhs.a);
    t.reduce();
    return t;
}

bool Rational::equal(Rational &rhs)
{
    reduce();
    rhs.reduce();
    return (a == rhs.a && b == rhs.b);
}

bool Rational::greater(Rational &rhs)
{
    reduce();
    rhs.reduce();
    return (a*rhs.b > b*rhs.a);
}

bool Rational::less(Rational &rhs)
{
    reduce();
    rhs.reduce();
    return (a*rhs.b < b*rhs.a);
}
