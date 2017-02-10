#include "Train.h"
#include <cstring>
#include <iostream>

using namespace std;

Train::Train(int rt, const char* dst, bool expr)
{
    route = rt;
    express = expr;
    dest = new char[strlen(dst)+1];
    strcpy(dest, dst);
}
Train::~Train()
{
    delete[] dest;
}

void Train::print() const
{
    cout << "Train #" << route << "  ->\t" << dest << ((express)?("\t(Express)"):("\t(Normal)"));
}

bool Train::goesTo(char* dst, bool expr) const
{
    return (express == expr && strcmp(dest, dst) == 0);
}
