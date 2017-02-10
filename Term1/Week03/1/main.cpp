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
    cout << "Week #3, Task #1.\n";
    cin >> n;
    bool a[10] = {0};
    do
    {
        a[n%10] = true;
        n /= 10;
    } while (n);
    for (int i = 0; i < 10; i++)
        if (a[i]) n++;
    cout << n;
    return 0;
}
