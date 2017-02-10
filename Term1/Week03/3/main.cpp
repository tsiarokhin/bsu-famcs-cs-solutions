/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;


int gcd(int a, int b)
{
    while ((a %= b) && (b %= a));
    return a | b;
}

int main()
{
    int n;
    cout << "Week #3, Task #3.\nAssuming that only proper fractions are required\n";
    cin >> n;
    for (int i = 2; i < n; i++)
    {
        for (int j = 1; j < i; j++)
            if (gcd(i, j) == 1)
                cout << j << '/' << i << ' ';
        cout << '\n';
    }
    return 0;
}
