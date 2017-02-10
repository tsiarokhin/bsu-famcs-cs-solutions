/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;

void b_sort(int* a, int n, bool order = true)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if ((order)?(a[i] > a[j]):(a[i] < a[j]))
                swap(a[i], a[j]);
}

int doTask(int *a, int n)
{
    int mn = a[0], mnc = 0;
    for (int i = 1; i < n; i++)
        if (a[i] < mn){ mn = a[i]; mnc = i; }
    b_sort(a, mnc, false);
    b_sort(a+mnc+1, n-mnc-1);
    return mnc;
}

int main()
{
    cout << "Week #4, Task #4.\n";
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Min element index is " << doTask(a, n) + 1 << '\n';
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    delete a;
    return 0;
}
