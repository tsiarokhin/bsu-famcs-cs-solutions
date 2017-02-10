#include "Set.h"
#include <iostream>
#include <cstring>

Set::Set()
{
    set_container = new char[CONTAINER_LENGTH];
    set_container[0] = 0;
}

Set::~Set()
{
    delete[] set_container;
}

Set::Set(const char* s): Set()
{
    for (int i = 0; i < strlen(s); i++){
        bool already_in = false;
        for (int j = 0; j < strlen(set_container); j++)
            if (s[i] == set_container[j]){
                already_in = true;
                break;
            }
        if (!already_in){
            char t[2] = {s[i], '\0'};
            strcat(set_container, t);
        }
    }
}

Set::Set(const Set& other): Set(other.set_container){}

Set& Set::operator=(const Set& rhs)
{
    if (this == &rhs) return *this;
    strcpy(set_container, rhs.set_container);
    return *this;
}

void Set::print()
{
    std::cout << set_container << std::endl;
}

Set& Set::operator<<(const char rhs)
{
    for (int i = 0; i < strlen(set_container); i++)
        if (set_container[i] == rhs)
            return *this;
    char t[2] = {rhs, '\0'};
    strcat(set_container, t);
    return *this;
}

Set& Set::operator>>(char& rhs)
{
    rhs = set_container[strlen(set_container)-1];
    set_container[strlen(set_container)-1] = '\0';
    return *this;
}

Set Set::operator*(const Set& rhs) const
{
    Set t;
    for (int i = 0; i < strlen(set_container); i++)
        for (int j = 0; j < strlen(rhs.set_container); j++)
            if (set_container[i] == rhs.set_container[j])
                t << set_container[i];
    return t;
}

Set Set::operator+(const Set& rhs) const
{
    Set t;
    for (int i = 0; i < strlen(set_container); i++)
        t << set_container[i];
    for (int i = 0; i < strlen(rhs.set_container); i++)
        t << rhs.set_container[i];
    return t;
}

Set Set::operator-(const Set& rhs) const
{
    Set t;
    for (int i = 0; i < strlen(set_container); i++){
        bool in_rhs = false;
        for (int j = 0; j < strlen(rhs.set_container); j++)
            if (set_container[i] == rhs.set_container[j]){
                in_rhs = true;
                break;
            }
        if (!in_rhs)
            t << set_container[i];
    }
    return t;
}

bool Set::operator<(const Set& rhs) const
{
    for (int i = 0; i < strlen(set_container); i++){
        bool in_rhs = false;
        for (int j = 0; j < strlen(rhs.set_container); j++)
            if (set_container[i] == rhs.set_container[j]){
                in_rhs = true;
                break;
            }
        if (!in_rhs) return false;
    }
    return true;
}

bool Set::operator==(const Set& rhs) const
{
    if (strlen(set_container) != strlen(rhs.set_container)) return false;
    return (*this < rhs);
}

