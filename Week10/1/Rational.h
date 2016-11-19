#ifndef RATIONAL_H
#define RATIONAL_H

class Rational
{
private:
    int a, b;
    void reduce();
public:
    Rational(int a = 0, int b = 0): a(a), b(b) {}
    Rational(const Rational &rat) {*this = rat;}
    void print();
    Rational add(const Rational &rhs) const;
    Rational mul(const Rational &rhs) const;
    Rational div(const Rational &rhs) const;
    bool equal(Rational &rhs);
    bool greater(Rational &rhs);
    bool less(Rational &rhs);
};


#endif //RATIONAL_H
