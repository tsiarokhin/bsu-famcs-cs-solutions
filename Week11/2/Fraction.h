#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
using namespace std;

class Fraction
{
    public:
        Fraction(const int a = 0, const double b = 0);
        Fraction(double other);
        Fraction(const Fraction& other);
        operator double() const;
        friend istream& operator>>(istream& input, Fraction& F);
        friend ostream& operator<<(ostream& output, const Fraction& F);

        Fraction& operator=(const Fraction& rhs);
        Fraction& operator+=(const Fraction& rhs);

        const Fraction operator+(const Fraction& rhs) const;
        const Fraction operator-(const Fraction& rhs) const;
        const Fraction operator*(const Fraction& rhs) const;

        bool operator<=(const Fraction& rhs) const;
        bool operator>=(const Fraction& rhs) const;
    private:
        int integer_part;
        double float_part;
};

#endif // FRACTION_H
