#ifndef SERIES_H
#define SERIES_H


class Series
{
    public:
        Series(int first = 0, int diff = 0);
        virtual const double operator[](const unsigned int j) const = 0;
        virtual const double sum(const unsigned int to, const unsigned int from = 1) const = 0;
    protected:
        double first;
        double diff;
};

#endif // SERIES_H
