/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <math.h>

using namespace std;

int* primes(int* a, int& n)
{
    int m = 0;
    bool *c = new bool[n];
    for(int i = 0; i < n; i++)
    {
        bool prime = true;
        for (int j = 2; j <= (int)sqrt(a[i]); j++){
            if (a[i] % j == 0) {
                prime = false;
                break;
            }
        }
        if (prime && a[i] != 1){
            m++;
            c[i] = true;
        }
        else
            c[i]= false;
    }
    int *b = new int[m];
    int j = 0;
    for(int i = 0; i < n; i++)
        if(c[i])
            b[j++] = a[i];
    n = m;
    delete[] c;
    return b;

}

int* div_by_3(int* a, int& n)
{
    int m = 0;
    for(int i = 0; i < n; i++)
        if (a[i] % 3 == 0) m++;
    int *b = new int[m];
    int j = 0;
    for(int i = 0; i < n; i++)
        if(a[i] % 3 == 0)
            b[j++] = a[i];
    n = m;
    return b;
}

int* even(int* a, int& n)
{
    int m = 0;
    for(int i = 0; i < n; i++)
        if (a[i] % 2 == 0) m++;
    int *b = new int[m];
    int j = 0;
    for(int i = 0; i < n; i++)
        if(a[i] % 2 == 0)
            b[j++] = a[i];
    n = m;
    return b;
}

void filter(int* a, int n, int* (*f)(int*, int&))
{
    a = f(a, n);
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
}

int main()
{
    cout << "Week #6, Task #2" << endl;
    cout << "Input size of array: ";
    int n;
    cin >> n;
    cout << "Input array elements: ";
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Select operation:\n" << "\t1. Filter primes\n" << "\t2. Filter divisible by 3\n" << "\t3. Filter evens\n" << "Your's choice(1-3): ";
    char c;
    cin >> c;
    int* (*f)(int*, int&);
    switch (c){
        case '1': f = primes; break;
        case '2': f = div_by_3; break;
        case '3': f = even; break;
    }
    filter(a, n, f);
    return 0;
}
