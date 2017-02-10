#ifndef DQUEUE_H
#define DQUEUE_H

#include "DStack.h"


class DQueue : public DStack
{
    public:
        DQueue(unsigned int size=128);
        virtual int pop();
        virtual int top();
        virtual bool empty();
        virtual void print();
    protected:
        unsigned int start;
    private:
};

#endif // DQUEUE_H
