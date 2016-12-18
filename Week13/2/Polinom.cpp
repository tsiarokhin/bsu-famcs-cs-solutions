#include "Polinom.h"

Polinom::Polinom(int s, int def): Array(s, def) {}
Polinom::Polinom(const Array &p): Array(p) {}
Polinom::Polinom(const Polinom &p): Array(p) {}

bool Polinom::operator== (const Polinom &p) const
{
    if(size != p.size) return false;

    for(int i = 0; i < size; i++)
        if (this->ptr[i] != p.ptr[i])
            return false;
    return true;
}

bool Polinom::operator<(const Polinom &p) const
{
    return size < p.size;
}

bool Polinom::operator>(const Polinom &p) const
{
    return size > p.size;
}

int Polinom::operator()(int x)
{
    int sum = 0;

    for(int i = 0; i < size; i++)
        sum += ptr[i] * pow(x, i);

    return sum;
}

Polinom Polinom::operator-(const Polinom &p) const
{
    Array t = (size > p.size)?(*this):p;

    int newSize = max(size, p.size);
    for (int i = 0; i < min(size, p.size); i++)
        t[i] = this->ptr[i] - p.ptr[i];
    return t;
}

Polinom Polinom::operator*(const Polinom &p) const
{
    Polinom t(size+p.size-1);
    for (int i = 0; i < size; i++)
        for(int j = 0; j < p.size; j++)
            t[i+j] += ptr[i] * p.ptr[j];

    return t;
}
