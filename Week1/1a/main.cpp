/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Can square be placed inside of circle?" << endl;
    cout << "Enter square area: ";
    double circleArea, squareArea;
    cin >> squareArea;
    cout <<  "Enter circle area: ";
    cin >> circleArea;
    if (sqrt(squareArea)*sqrt(2.0) <= 2.0*sqrt(circleArea / M_PI))
        cout << "YES!";
    else
        cout << "NO!";
    return 0;
}
