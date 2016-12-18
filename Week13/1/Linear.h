#ifndef LINEAR_H
#define LINEAR_H

#include "Series.h"


class Linear : public Series
{
    public:
        Linear(int first = 0, int diff = 0);
        const double operator[](const unsigned int j) const;
        const double sum(const unsigned int to, const unsigned int from = 1) const;
    protected:

    private:
};

#endif // LINEAR_H
