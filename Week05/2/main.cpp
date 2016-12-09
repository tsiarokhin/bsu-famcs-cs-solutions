/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

int* min_elem(int *a, int n)
{
    int *mn = a;
    for(int i = 1; i < n; i++)
        if(a[i] < *mn)
            mn = a + i;
    return mn;
}

void selection_sort(int *a, int n)
{
    for (int i = 0; i < n-1; i++)
        swap(a[i],*min_elem(a+i,n-i));
}

int main()
{
    cout << "Week #5, Task #2" << endl;
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    selection_sort(a, n);
    for (int i = 0; i < n; i++)
        cout << a[i] <<  ' ';

    delete[] a;
    return 0;
}
