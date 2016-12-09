/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Can circle be placed inside of square?" << endl;
    cout << "Enter circle area: ";
    double circleArea, squareArea;
    cin >> circleArea;
    cout <<  "Enter square area: ";
    cin >> squareArea;
    if (2.0*sqrt(circleArea / M_PI) <= sqrt(squareArea))
        cout << "YES!";
    else
        cout << "NO!";
    return 0;
}
