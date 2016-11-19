/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include "Rational.h"

using namespace std;

int main()
{
    cout << "Week #10, Task #1" << endl;
    int a, b, c, d;
    char temp_c;
    cout << "Enter first ratio (A/B): ";
    cin >> a >> temp_c >> b;
    cout << "Enter second ratio (B/D): ";
    cin >> c >> temp_c >> d;

    Rational ratio1(a, b);
    Rational ratio2(c, d);
    cout << endl;
    cout << "Their sum is\t\t"; ratio1.add(ratio2).print(); cout << endl;
    cout << "Their multiplication is\t"; ratio1.mul(ratio2).print(); cout << endl;
    cout << "Their quotient is\t"; ratio1.div(ratio2).print(); cout << endl;
    cout << endl;

    if (ratio1.equal(ratio2))
        {ratio1.print(); cout << " is equal to "; ratio2.print(); cout << endl;}
    else if (ratio1.less(ratio2))
        {ratio1.print(); cout << " is less than "; ratio2.print(); cout << endl;}
    else if (ratio1.greater(ratio2))
        {ratio1.print(); cout << " is bigger than "; ratio2.print(); cout << endl;}

    return 0;
}
