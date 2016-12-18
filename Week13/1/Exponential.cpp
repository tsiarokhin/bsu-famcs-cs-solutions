#include "Exponential.h"
#include <math.h>

Exponential::Exponential(int first, int diff): Series(first, diff)
{
}

const double Exponential::operator[](const unsigned int j) const
{
    return (first * pow(diff,j-1));
}

const double Exponential::sum(const unsigned int to, const unsigned int from) const
{
    if (diff == 1)
        return (*this)[from] * (to-from+1);
    return (*this)[from] * (pow(diff, to-from+1) - 1.0) / (diff - 1.0);
}

