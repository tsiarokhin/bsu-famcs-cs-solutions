/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;
typedef long long ll;

const int maxn = 10000;

int a[maxn] = {0}, b[maxn] = {0}, sum[maxn] = {0}, mult[2*maxn] = {0};

int main()
{
    cout << "Week #4, Task #3.\n";
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];

    cin >> m;
    for (int i = 0; i < m; i++)
        cin >> b[i];

    for (int i = 0; i < max(n, m); i++)
        sum[i] = a[i] + b[i];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mult[i + j] += a[i] * b[j];

    cout << "Sum: ";
    for ( int i = 0; i < max(n, m); i++ )
        cout << sum[i] << ' ';
    cout << '\n';
    cout << "Multiplication: ";
    for ( int i = 0; i < n + m - 1; i++ )
        cout << mult[i] << ' ';
    cout << '\n';
    return 0;
}
