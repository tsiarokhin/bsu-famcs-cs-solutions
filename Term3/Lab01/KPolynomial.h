/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#ifndef KPOLYNOMIAL_H
#define KPOLYNOMIAL_H


/** Definition: **/

template <class T>
struct PolyTerm {
    T coef;
    int deg;
    PolyTerm(T coef, int deg): coef(coef), deg(deg) {}
    PolyTerm(const PolyTerm<T>& pt): coef(pt.coef), deg(pt.deg) {}
    T Coeff() const
    {
        return coef;
    }
    int Degree() const
    {
        return deg;
    }
};


template <class T>
class KPolynomial
{
    private:
        std::map<int, T> terms; // maps degree to coefficient

        class iterator
        {
            using map_it = typename std::map<int, T>::const_iterator ;
            map_it it;

            public:
                iterator(map_it it): it(it) {}
                iterator(const iterator& it): it(it.it){}
                iterator& operator++()
                {
                    it = std::next(it);
                    return *this;
                }
                iterator operator++(int)
                {
                    iterator tmp(*this);
                    operator++();
                    return tmp;
                }
                bool operator==(const iterator& rhs) { return it == rhs.it; }
                bool operator!=(const iterator& rhs) { return it != rhs.it; }
                const PolyTerm<T> operator*() { return PolyTerm<T>(it->second, it->first); }
        };

    public:
        KPolynomial();
        virtual ~KPolynomial() {}
        KPolynomial(const KPolynomial<T>& other); //copy ctr
        KPolynomial(const KPolynomial<T>&& other); //move ctr
        KPolynomial(const std::initializer_list<std::pair<T, int>> list); //init_list ctr
        KPolynomial(const std::string s);
        KPolynomial<T>& operator=(const KPolynomial<T>& other); //copy op
        KPolynomial<T>& operator=(const KPolynomial<T>&& other); //move op

        template <class... Args> std::pair<typename std::map<int, T>::iterator,bool> emplace ( Args&&... args )
        {
            return terms.emplace(std::forward<Args>(args)...);
        }

        template<class U> friend std::istream& operator>>(std::istream& input, KPolynomial<U>& P);
        template<class U> friend std::ostream& operator<<(std::ostream& output, const KPolynomial<U>& P);

        void insert(const T& coef, const int deg);

        iterator begin() const
        {
            return iterator(terms.begin());
        }
        iterator end() const
        {
            return iterator(terms.end());
        }

        void fromString(std::string s);
        std::string toString() const;

        PolyTerm<T> operator[](int i) const;
        bool operator==(const KPolynomial<T>& rhs) const;
        bool operator!=(const KPolynomial<T>& rhs) const;
        KPolynomial<T> operator+(const KPolynomial<T>& rhs) const;
        KPolynomial<T>& operator+=(const KPolynomial<T>& rhs);
        KPolynomial<T> operator-(const KPolynomial<T>& rhs) const;
        KPolynomial<T>& operator-=(const KPolynomial<T>& rhs);
        KPolynomial<T> operator*(const KPolynomial<T>& rhs) const;
        KPolynomial<T>& operator*=(const KPolynomial<T>& rhs);

        int Count() const;
        int Degree() const;
        void Clear();
        void Swap(KPolynomial<T>& other);

};

/** Implementation: **/

template <class T>
KPolynomial<T>::KPolynomial():
    terms()
{
    terms[0] = (T)0;

}

template <class T>
KPolynomial<T>::KPolynomial(const KPolynomial<T>& other)
{
    terms.insert(other.terms.begin(), other.terms.end());
}

template <class T>
KPolynomial<T>::KPolynomial(const KPolynomial<T>&& other)
{
    terms = std::move(other.terms);
}

template <class T>
KPolynomial<T>::KPolynomial(std::string s)
{
    fromString(s);
}

template <class T>
KPolynomial<T>::KPolynomial(const std::initializer_list<std::pair<T, int>>list)
{
    for (auto it = list.begin(); it != list.end(); ++it)
        terms[it->second] = it->first;
}

template <class T>
KPolynomial<T>& KPolynomial<T>::operator=(const KPolynomial<T>& other)
{
    if (this == &other)
        return *this;
    Clear();
    terms.insert(other.terms.begin(), other.terms.end());
}

template <class T>
KPolynomial<T>& KPolynomial<T>::operator=(const KPolynomial<T>&& other)
{
    if (this == &other)
        return *this;
    terms = std::move(other.terms);
    return *this;
}

template <class T>
std::ostream& operator<<(std::ostream& output, const  KPolynomial<T>& P)
{
    output << P.toString();
    return output;
}

template <class T>
std::istream& operator>>(std::istream& input,  KPolynomial<T>& P)
{
    std::string s;
    std::getline(input, s);
    P.fromString(s);
    return input;
}

template <class T>
PolyTerm<T> KPolynomial<T>::operator[](int i) const
{
    return PolyTerm<T>(terms.at(i), i);
}

template <class T>
bool KPolynomial<T>::operator==(const KPolynomial<T>& rhs) const
{
    return Degree() == rhs.Degree() && terms.size() == rhs.terms.size() && std::equal(terms.begin(), terms.end(), rhs.terms.begin());
}

template <class T>
bool KPolynomial<T>::operator!=(const KPolynomial<T>& rhs) const
{
    return !(operator==(rhs));
}

template <class T>
KPolynomial<T> KPolynomial<T>::operator+(const KPolynomial<T>& rhs) const
{
    KPolynomial<T> tmp = *this;
    for (auto it = rhs.terms.begin(); it != rhs.terms.end(); ++it){
        tmp.terms[it->first] += it->second;
    }
    return tmp;
}

template <class T>
KPolynomial<T>& KPolynomial<T>::operator+=(const KPolynomial<T>& rhs)
{
    for (auto it = rhs.terms.begin(); it != rhs.terms.end(); ++it){
        terms[it->first] += it->second;
    }
    return *this;
}

template <class T>
KPolynomial<T> KPolynomial<T>::operator-(const KPolynomial<T>& rhs) const
{
    KPolynomial<T> tmp = *this;
    for (auto it = rhs.terms.begin(); it != rhs.terms.end(); ++it){
        tmp.terms[it->first] -= it->second;
    }
    return tmp;
}

template <class T>
KPolynomial<T>& KPolynomial<T>::operator-=(const KPolynomial<T>& rhs)
{
    for (auto it = rhs.terms.begin(); it != rhs.terms.end(); ++it){
        terms[it->first] -= it->second;
    }
    return *this;
}

template <class T>
KPolynomial<T> KPolynomial<T>::operator*(const KPolynomial<T>& rhs) const
{
    KPolynomial<T> tmp;
    for (auto it = terms.begin(); it != terms.end(); ++it)
        for (auto it2 = rhs.terms.begin(); it2 != rhs.terms.end(); ++it2)
            tmp.terms[(it->first)+(it2->first)] += (it->second)*(it2->second);
    return tmp;
}

template <class T>
KPolynomial<T>& KPolynomial<T>::operator*=(const KPolynomial<T>& rhs)
{
    KPolynomial<T> tmp;
    for (auto it = terms.begin(); it != terms.end(); ++it)
        for (auto it2 = rhs.terms.begin(); it2 != rhs.terms.end(); ++it2)
            tmp.terms[(it->first)+(it2->first)] += (it->second)*(it2->second);
    *this = tmp;
    return *this;
}

template <class T>
void KPolynomial<T>::insert(const T& coef, const int deg)
{
    terms[deg] = coef;
}

template <class T>
int KPolynomial<T>::Count() const
{
    return terms.size();
}

template <class T>
int KPolynomial<T>::Degree() const
{
    return terms.rbegin()->first;
}

template <class T>
void KPolynomial<T>::Clear()
{
    terms.clear();
    terms[0] = 0;
}

template <class T>
void KPolynomial<T>::Swap(KPolynomial<T>& other)
{
    std::swap(*this, other);
}

template <class T>
void KPolynomial<T>::fromString(std::string s)
{
    Clear();
    std::string::size_type gsz = 0, sz = 0;
    double c;
    int d;
    while (gsz < s.size()){
        if (!((s[gsz] >= '0' && s[gsz] <= '9')  || s[gsz] == '-'))
            c = 1;
        else
            c = std::stod(s.substr(gsz),&sz);

        gsz += sz;

        while (!((s[gsz] >= '0' && s[gsz] <= '9')  || s[gsz] == '-') && gsz < s.size()) gsz++;

        if (gsz >= s.size())
            d = 0;
        else
            d = std::stoi(s.substr(gsz),&sz);

        gsz += sz;

        while (!((s[gsz] >= '0' && s[gsz] <= '9')  || s[gsz] == '-') && gsz < s.size()) gsz++;
        terms[d] = (T)c;
    }

}

template <class T>
std::string KPolynomial<T>::toString() const
{
    std::stringstream output;
    bool first_run = true;
    for (auto it = terms.rbegin(); it != terms.rend(); it++){
        int deg = it->first;
        T c = it->second;
        if (c == 0 && Degree() != 0)
            continue;

        if (!first_run && c > 0)
            output << '+';
        first_run = false;
        if (c != (T)1 || deg == 0)
            output << c;
        if (deg == 1)
             output << "x";
        else if (deg > 1)
            output << "x^" << deg;
    }
    return output.str();
}

#endif // KPOLYNOMIAL_H
