//#include <iostream>
#include <iterator>

#ifndef VECTOR_LIST_H_INCLUDED
#define VECTOR_LIST_H_INCLUDED

template <class T>
class vector_list {
protected:
    struct list_item {
        T value;
        list_item* next;
    };
    list_item* head;
    list_item* tail;
    int sz;

public:
    class iterator : public std::iterator<std::input_iterator_tag, T> {
        list_item* p;

    public:
        iterator(list_item* x)
            : p(x)
        {
        }
        iterator(const iterator& it)
            : p(it.p)
        {
        }
        iterator& operator++()
        {
            p = p->next;
            return *this;
        }
        iterator operator++(int)
        {
            iterator tmp(*this);
            operator++();
            return tmp;
        }
        bool operator==(const iterator& rhs) { return p == rhs.p; }
        bool operator!=(const iterator& rhs) { return p != rhs.p; }
        T& operator*() { return p->value; }
    };

    vector_list();
    vector_list(const vector_list<T>& v);
    vector_list(const T* a, int n);
    vector_list<T>& operator=(const vector_list<T>& v);
    ~vector_list();
    T& operator[](int i);
    void push_back(const T& val);
    void push_front(const T& val);
    const int size() const;
    const bool empty() const;
    //void print() const; // Use iterator instead
    void clear();
    iterator begin() const { return iterator(head); }
    iterator end() const { return iterator(tail->next); }
};

template <class T>
vector_list<T>::vector_list()
    : head(nullptr)
    , tail(nullptr)
    , sz(0)
{
}

template <class T>
vector_list<T>::vector_list(const vector_list<T>& v)
    : head(nullptr)
    , tail(nullptr)
    , sz(0)
{
    if (this == &v)
        return;
    list_item* t = v.head;
    while (t) {
        this->push_back(t->value);
        t = t->next;
    }
}

template <class T>
vector_list<T>& vector_list<T>::operator=(const vector_list<T>& v)
{
    if (this == &v)
        return *this;
    this->clear();
    list_item* t = v.head;
    while (t) {
        this->push_back(t->value);
        t = t->next;
    }
}

template <class T>
vector_list<T>::vector_list(const T* a, int n)
    : head(nullptr)
    , tail(nullptr)
    , sz(0)
{
    for (int i = 0; i < n; i++)
        this->push_back(a[i]);
}

template <class T>
void vector_list<T>::clear()
{
    list_item* t = head;
    list_item* prev;
    while (t) {
        prev = t;
        t = t->next;
        delete prev;
    }
    head = tail = nullptr;
    sz = 0;
}

template <class T>
vector_list<T>::~vector_list()
{
    this->clear();
}

template <class T>
void vector_list<T>::push_back(const T& val)
{
    list_item* t = new list_item;
    t->value = val;
    t->next = nullptr;
    if (this->empty())
        head = tail = t;
    else {
        tail->next = t;
        tail = t;
    }
    sz++;
}

template <class T>
void vector_list<T>::push_front(const T& val)
{
    list_item* t = new list_item;
    t->value = val;
    t->next = head;
    if (this->empty())
        head = tail = t;
    else
        head = t;
    sz++;
}

template <class T>
const int vector_list<T>::size() const
{
    return sz;
}

template <class T>
const bool vector_list<T>::empty() const
{
    return sz == 0;
}
/* 
template <class T>
void vector_list<T>::print() const
{
    using namespace std;
    cout << "[";
    list_item* t = head;
    int i = 1;
    while (t) {
        cout << t->value << ((i < this->size()) ? ", " : "");
        t = t->next;
        i++;
    }
    cout << "]\n";
}
*/

template <class T>
T& vector_list<T>::operator[](int i)
{
    if (i >= this->size())
        throw "Out of bounds";
    list_item* t = head;
    int cur = 0;
    while (t && cur < i) {
        t = t->next;
        cur++;
    }
    return t->value;
}

#endif // VECTOR_LIST_H_INCLUDED