#ifndef DSTACK_H
#define DSTACK_H

#include "DArray.h"


class DStack : protected DArray
{
    public:
        DStack(unsigned int size=128);
        virtual void push(int el);
        virtual int pop();
        virtual int top();
        virtual bool empty();
        virtual void print();
    protected:
        unsigned int end;
    private:
};

#endif // DSTACK_H

