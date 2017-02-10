/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include<iostream>
using namespace std;


int* check(int* a, int n, int* b, int m)
{
    for (int i = 0; i < n; i++)
    {
        int j = i, k = 0;
        while(j < n && k < m && a[j] == b[k])
        {
            j++;
            k++;
        }
        if(k == m)
            return a + i;
    }
    return nullptr;
}
int main()
{
    cout << "Week #5, Task #4" << endl;
    int n, m;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cin >> m;
    int *b = new int[m];
    for (int i = 0; i < m; i++)
        cin >> b[i];
    cout << "Array B is subset of A from " <<  check(a, n, b, m);
    delete[] a;
    delete[] b;
    return 0;
}
