#include "DQueue.h"
#include <iostream>

DQueue::DQueue(unsigned int size): DStack(size), start(0) {}


int DQueue::pop()
{
    return arr[start++];
}

int DQueue::top()
{
    return arr[start];
}

bool DQueue::empty()
{
    return end-start <= 0;
}

void DQueue::print()
{
    std::cout << "DQueue(" << end-start << "/" << size << ") <";
    for (unsigned int i = start; i < end; i++){
        std::cout << arr[i];
        if (i != end-1)
            std::cout << ", ";
    }
    std::cout << ">";
}
