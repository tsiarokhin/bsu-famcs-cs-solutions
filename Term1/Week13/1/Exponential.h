#ifndef Exponential_H
#define Exponential_H

#include "Series.h"

class Exponential : public Series
{
    public:
        Exponential(int first = 0, int diff = 0);
        const double operator[](const unsigned int j) const;
        const double sum(const unsigned int to, const unsigned int from = 1) const;
    protected:

    private:
};

#endif // Exponential_H
