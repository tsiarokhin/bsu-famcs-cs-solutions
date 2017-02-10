#include "DStack.h"
#include <iostream>

DStack::DStack(unsigned int size):DArray(size), end(0){}

void DStack::push(int el)
{
    arr[end++] = el;
}

int DStack::pop()
{
    return arr[--end];
}

int DStack::top()
{
    return arr[end-1];
}

void DStack::print()
{
    std::cout << "DStack(" << end  << "/" << size << ") <";
    for (unsigned int i = 0; i < end; i++){
        std::cout << arr[i];
        if (i != end-1)
            std::cout << ", ";
    }
    std::cout << ">";
}

bool DStack::empty()
{
    return end == 0;
}
