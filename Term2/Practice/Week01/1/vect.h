#ifndef VECT_H_INCLUDED
#define VECT_H_INCLUDED
#include <assert.h>
#include <iostream>
using namespace std;

template <class T>
class vector {
public:
    typedef T* iterator;
    explicit vector(int n = 100); //create a size n array
    vector(const vector<T>& v); //copy vector
    vector(const T* a, int n); //copy an array
    ~vector()
    {
        delete[] p;
    }
    iterator begin()
    {
        return p;
    }
    iterator end()
    {
        return p + size;
    }
    //T& operator[](int i);      //range checked element
    vector<T>& operator=(const vector<T>& v);
    //protected:
    T* p; //base pointer
    int size; //number of elements
protected:
    int actual_size;
};

template <class T>
vector<T>::vector(int n)
    : size(n)
    , actual_size(n)
{
    assert(n > 0);
    p = new T[actual_size];
    assert(p != 0);
}
template <class T>
vector<T>::vector(const T a[], int n)
{
    assert(n > 0);
    actual_size = size = n;
    p = new T[actual_size];
    assert(p != 0);
    for (int i = 0; i < size; ++i)
        p[i] = a[i];
}
template <class T>
vector<T>::vector(const vector<T>& v)
{
    size = v.size;
    actual_size = v.actual_size;
    p = new T[actual_size];
    assert(p != 0);
    for (int i = 0; i < size; ++i)
        p[i] = v.p[i];
}
template <class T>
vector<T>& vector<T>::operator=(const vector<T>& v)
{
    assert(v.size == size);
    for (int i = 0; i < size; ++i)
        p[i] = v.p[i];
    return *this;
}

template <class T>
class vectorex : public vector<T> {
public:
    vectorex(int n = 10)
        : vector<T>::vector(n)
    {
        assert(n > 0);
        this->size = n;
        this->actual_size = n;
        this->p = new T[this->actual_size];
        assert(this->p != 0);
    }
    T& operator[](int i)
    {
        assert(i >= 0 && i < this->size);
        return (this->p[i]);
    }
    void push_front(T element)
    {
        if (this->size + 1 <= this->actual_size) {
            for (int i = this->size; i > 0; --i)
                this->p[i] = this->p[i - 1];
        } else {
            this->actual_size *= 2;
            auto temp_p = new T[this->actual_size];
            for (int i = 0; i < this->size; ++i)
                temp_p[i + 1] = this->p[i];
            delete[] this->p;
            this->p = temp_p;
        }
        this->p[0] = element;
        this->size++;
    }
};

#endif // VECT_H_INCLUDED
