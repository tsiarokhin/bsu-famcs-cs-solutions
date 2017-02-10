#include "DArray.h"

#include <iostream>

DArray::DArray(unsigned int size): size(size)
{
    arr = new int[size];
}

DArray::DArray(int* a, unsigned int size): DArray(size)
{
    for (unsigned int i = 0; i < size; i++)
        arr[i] = a[i];
}

DArray::DArray(const DArray& other): DArray(other.arr, other.size) {}


DArray::~DArray()
{
    delete[] arr;
}

void DArray::print()
{
    std::cout << "DArray(" << size << ") <";
    for (unsigned int i = 0; i < size; i++){
        std::cout << arr[i];
        if (i != size-1)
            std::cout << ", ";
    }
    std::cout << ">";
}

DArray& DArray::operator=(const DArray& rhs)
{
    if (this == &rhs) return *this;
    delete[] arr;
    size = rhs.size;
    arr = new int[size];
    for (unsigned int i = 0; i < size; i++)
        arr[i] = rhs.arr[i];
    return *this;
}

int& DArray::operator[](const unsigned int idx)
{
    return arr[idx];
}
