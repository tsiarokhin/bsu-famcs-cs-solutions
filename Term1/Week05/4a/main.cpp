/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include<iostream>
#include<climits>

using namespace std;
bool c[100000000] = {0};

int main()
{
    cout << "Week #5, Task #4. Proper solution" << endl;
    int n, m, mn = INT_MAX;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
        mn = min(mn, a[i]);
    }
    if (mn > 0)
        mn = 0;
    for (int i = 0; i < n; i++)
        c[a[i]-mn] = true;
    cin >> m;
    int t;
    for (int i = 0; i < m; i++)
    {
        cin >> t;
        if (t-mn < 0)
        {
            cout << "Not a subset";
            return 0;
        }
        if (!c[t-mn])
        {
            cout << "Not a subset";
            return 0;
        }
    }
    cout << "Array B is subset of A";
    delete[] a;
    return 0;
}
