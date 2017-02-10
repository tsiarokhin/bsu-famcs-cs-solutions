#ifndef DARRAY_H
#define DARRAY_H


class DArray
{
    public:
        DArray(unsigned int size=128);
        DArray(const DArray& other);
        DArray(int* a, unsigned int size);

        virtual ~DArray();
        virtual void print();

        DArray& operator=(const DArray& rhs);
        int& operator[](const unsigned int idx);
    protected:
        unsigned int size;
        int* arr;
    private:
};

#endif // DARRAY_H
