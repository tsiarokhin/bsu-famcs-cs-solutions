#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
using namespace std;

class Array
{
    protected:
        int size;
        int *ptr;
        static const int MAX=100;

    public:
        class TooBigExeption {};
        class IndexOutOfBoundsExeption {};

        Array(int s,int def=0);
        Array(const Array &p);
        ~Array ();

        virtual void print(ostream &out = cout) const;
        virtual const Array operator+ (const Array &p) const;
        int& operator[](unsigned int n);
        Array operator= (Array &p);
};

#endif // ARRAY_H
