/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Solving ax^2 + bx + c = 0" << endl << "Enter a, b, c: ";
    int a, b, c;
    cin >> a >> b >> c;
    int d = b*b - 4*a*c;
    double r1, r2;
    if (a == 0)
    {
        cout << "One solution x = " << (double)(-c)/b;
        return 0;
    }
    if (d < 0)
        cout << "No solutions";
    else if (d == 0)
    {
        r1 =(-b)/(2.0*a);
        cout << "One solution x = " << r1;
    }
    else
    {
        r1 = (-b+sqrt(d))/(2.0*a);
        r2 = (-b-sqrt(d))/(2.0*a);
        cout << "Two solutions x1 = " << r1 << "; x2 = " << r2;
    }
    return 0;
}
