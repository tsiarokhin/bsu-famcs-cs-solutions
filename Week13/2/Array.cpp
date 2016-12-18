#include "Array.h"

Array::Array(int s, int def): size(s)
{
    if (size > MAX)
        throw TooBigExeption();
    else {
        ptr = new int[size];
        for(int i = 0; i < size; i++)
            ptr[i] = def;
    }
}

Array::Array(const Array &p): size(p.size)
{
    ptr=new int [p.size];
    for(int i=0; i < size; i++)
        ptr[i] = p.ptr[i];
}

Array::~Array()
{
    delete[] ptr;
}

int& Array::operator[](unsigned int n)
{
    if(n >= size)
        throw IndexOutOfBoundsExeption();
    else
        return ptr[n];
}

void Array::print(ostream &out) const
{
    out << "< ";
    for(int i = 0; i < size; i++)
        out << ptr[i] << ' ';
    out << ">";
}

Array Array::operator=(Array &p)
{
    if (&p == this) return *this;

    delete[] ptr;
    size = p.size;
    ptr = new int[size];
    for(int i = 0; i < size; i++)
        ptr[i] = p.ptr[i];
    return *this;
}

const Array Array::operator+ (const Array &p) const
{
    Array t = (size > p.size)?(*this):p;

    int newSize = max(size, p.size);
    for (int i = 0; i < min(size, p.size); i++)
        t[i] = this->ptr[i] + p.ptr[i];
    return t;

}
