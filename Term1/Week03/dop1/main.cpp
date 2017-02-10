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



int main()
{
    ll n;
    cout << "Week #3, Additional task #1.\n";
    for (int n = 0; n < 100; n++)
    {
        bool has = false;
        for (ll i = n; i < 100000000*n; i+=n)
        {
            ll a = i;
            int b = a%10;
            while (a && a%10 == b)
                a /= 10;
            if (!a)
            {
                has = true;
                break;
            }
        }
        if (!has)
            cout << n << ' ';
    }
    return 0;
}
