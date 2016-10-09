/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

int main()
{
    cout << "Is the number a power of 2?\nEnter number: ";
    int n;
    cin >> n;
    cout << (((n & (n - 1)) || !n)?"NO!":"YES!");
    return 0;
}
