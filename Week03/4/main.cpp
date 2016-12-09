/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

typedef long long ll;

int main()
{
    ll n;
    cout << "Week #3, Task #4.\n";
    cin >> n;
    for (ll i = 6; i < n; i++)
    {
        ll divSum = 1;
        for (ll j = 2; j < i; j++)
            if (i % j == 0)
            {
                divSum += j;
                if (divSum > i) break;
            }
        if (divSum == i)
            cout << i << ' ';
    }
    return 0;
}
