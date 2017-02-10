/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Fraction.h"

using namespace std;

void b_sort(Fraction** a, int n, bool order = true)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ( order ? *a[i]>=*a[j] : *a[i]<=*a[j] )
                swap(*a[i], *a[j]);
}


int main()
{
    cout << "Week #11, Task #2" << endl;
    Fraction a, b;
    cout << "\nEnter a = ";
    cin >> a;
    cout << "\nEnter b = ";
    cin >> b;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << a << " <= " << b << " -- " << boolalpha << (a<=b) << endl;
    cout << a << " >= " << b << " -- " << boolalpha << (a>=b) << endl;
    cout << a << " + " << b << " -- " << boolalpha << (a+b) << endl;
    cout << a << " - " << b << " -- " << boolalpha << (a-b) << endl;
    cout << a << " * " << b << " -- " << boolalpha << (a*b) << endl;
    cout << a << " += " << b << endl;
    a += b;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;

    const int FRACTION_ARRAY_SIZE = 10;
    Fraction** arr = new Fraction*[FRACTION_ARRAY_SIZE];
    cout << "Array sorting test\nInitial array: ";
    for (int i = 0; i < FRACTION_ARRAY_SIZE; i++){
        arr[i] = new Fraction((double)(rand()%10000)/100.0);
        cout << *arr[i] << ' ';
    }
    cout << "\nSorted  array: ";
    b_sort(arr, FRACTION_ARRAY_SIZE);

    for (int i = 0; i < FRACTION_ARRAY_SIZE; i++){
        cout << *arr[i] << ' ';
        delete arr[i];
    }
    delete[] arr;


    Fraction sum;
    int start, end;
    cout << "\n\nCounting sum from ";
    cin >> start;
    cout << " to ";
    cin >> end;

    for (double i = start; i < end; i++)
        sum += Fraction(i);

    cout << "\n Sum = " << sum;

    return 0;
}
