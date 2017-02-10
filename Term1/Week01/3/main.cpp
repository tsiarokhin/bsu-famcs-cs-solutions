/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int a[4];
    cout << "Finding max even number" << endl << "Enter 4 numbers: ";
    cin >> a[0] >> a[1] >> a[2] >> a[3];
    sort(a, a+4);
    for (int i = 3; i >= 0; i--)
        if (a[i] % 2 == 0)
        {
            cout << "Max even number is " << a[i];
            return 0;
        }
    cout << "There are no even numbers";
    return 0;
}
