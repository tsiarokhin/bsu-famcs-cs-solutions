/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

int* bin_search(int* a, int n, int key)
{
    int l = 0, r = n;
    while (l < r){
        int m = (l + r) / 2;
        if (a[m] < key)
            l = m+1;
        else
            r = m;
    }
    return a+l;
}

void bin_insertion_sort(int* a, int n)
{
    for (int i = 1; i < n; i++){
        int* k = bin_search(a, i, a[i]);
        for (int j = i-1; j >= (k-a); j--)
            swap(a[j], a[j+1]);
    }
}

int main()
{
    cout << "Week #5, Task #3" << endl;
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    bin_insertion_sort(a, n);
    for (int i = 0; i < n; i++)
        cout << a[i] <<  ' ';

    delete[] a;
    return 0;
}
