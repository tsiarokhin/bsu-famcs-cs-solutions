/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

int main()
{
    cout << "Calculating the sum of the digits of n\nEnter n: ";
    long long n, sum = 0;
    cin >> n;
    while (n != 0)
    {
        sum += (n%10);
        n /= 10;
    }
    cout << "Result: " << sum;
    return 0;
}
