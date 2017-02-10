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

ll nthpow10 (int n)
{
    ll r = 1;
    for (int i = 0; i < n; i++)
        r *= 10LL;
    return r;
}


int main()
{
    ll n;
    cout << "Week #3, Task #2.\n";
    cin >> n;
    for (ll i = 0; i < n; i++)
        if (i*i%nthpow10(digCount(i)) == i)
            cout << i << ' ';
    return 0;
}
