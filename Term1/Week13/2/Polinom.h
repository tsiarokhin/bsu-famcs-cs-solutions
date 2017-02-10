#ifndef POLINOM_H
#define POLINOM_H

#include "Array.h"
#include <cmath>

class Polinom: public Array
{
    public:

        Polinom(int s, int def = 0);
        Polinom(const Array &p);
        Polinom(const Polinom &p);

        bool operator== (const Polinom &p) const;
        bool operator<(const Polinom &p) const;
        bool operator>(const Polinom &p) const;
        int operator()(int x);
        Polinom operator-(const Polinom &p) const;
        Polinom operator*(const Polinom &p) const;
};

#endif // POLINOM_H
