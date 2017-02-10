/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

typedef long long ll;

int digCount (ll n)
{
    int len = 0;
    do {
        n /= 10;
        len++;
    } while (n);
    return len;
}

ll intPow (int n, int pow)
{
    ll r = 1;
    for (int i = 0; i < pow; i++)
        r *= n;
    return r;
}

int main()
{
    ll n;
    cout << "Week #3, Task #5.\n";
    cin >> n;
    for (ll i = 0; i < n; i++)
    {
        ll a = i, sum = 0;
        int digC = digCount(a);
        while (a)
        {
            sum += intPow(a%10, digC);
            a /= 10;
        }
        if (sum == i)
            cout << i << '\n';
    }

    return 0;
}
