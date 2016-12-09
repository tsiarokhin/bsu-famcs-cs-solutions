/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <math.h>

using namespace std;

int* delete_primes(int* a, int n)
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
    int *b = new int[n-m+1];
    int j = 0;
    for(int i = 0; i < n; i++)
        if(!c[i])
            b[j++] = a[i];
    b[j] = 0;
    return b;
}

int main()
{
    cout << "Week #5, Task #5" << endl;
    int n, m;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    int *b = delete_primes(a, n);
    for (int i = 0; b[i] != 0; i++)
        cout << b[i] << ' ';
    delete[] a;
    delete[] b;
    return 0;
}



