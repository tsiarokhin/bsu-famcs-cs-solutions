#include "Linear.h"

Linear::Linear(int first, int diff): Series(first, diff)
{
}

const double Linear::operator[](const unsigned int j) const
{
    return (first + (j-1)*diff);
}

const double Linear::sum(const unsigned int to, const unsigned int from) const
{
    return ((*this)[from] + (*this)[to])/2.0 * (to-from+1);
}
