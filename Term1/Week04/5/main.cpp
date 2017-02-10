/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <algorithm>

using namespace std;

void b_sort(int* a, int n, bool order = true)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ((order)?(a[i] > a[j]):(a[i] < a[j]))
                swap(a[i], a[j]);
}

int gcd(int a, int b)
{
    while ((a %= b) && (b %= a));
    return a | b;
}

int main()
{
    cout << "Week #4, Task #5.\n";
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    b_sort (a, n);
    int d = a[1]-a[0];
    for (int i = 2; i < n; i++)
        d = gcd(d, a[i]- a[i-1]);
    for (int i = 0; i < n - 1; i++)
        while (a[i] != a[i + 1]){
            cout << a[i] << ' ';
            a[i] += d;
        }
    cout << a[n-1];
    delete[] a;
    return 0;
}
