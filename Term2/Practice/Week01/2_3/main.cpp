/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#include "./vector_list.h"
#include <algorithm>
#include <iostream>

using namespace std;

template <class T>
void vlist_print(const T& v)
{
    cout << "[";
    for (auto it = v.begin(); it != v.end(); it++)
        cout << *it << ", ";
    cout << "]\n";
}

int main()
{
    vector_list<int> arr;
    arr.push_back(1);
    vlist_print(arr);
    arr.push_back(2);
    vlist_print(arr);
    arr.push_back(3);
    vlist_print(arr);
    arr.push_front(0);
    arr.push_front(1);
    arr.push_front(2);
    arr.push_front(3);
    vlist_print(arr);
    cout << "First item: " << *arr.begin() << ", size: " << arr.size();
    arr[0] = 100;
    cout << "\nAnd now first item = " << *arr.begin() << endl;
    vlist_print(arr);

    int a[] = { 1, 6, 2, 3, 4, 7 };
    cout << "\nVector-list constructed from array: ";
    vlist_print(vector_list<int>(a, 6));

    return 0;
}