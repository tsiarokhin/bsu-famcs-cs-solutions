/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <iomanip>
#include "Set.h"

using namespace std;

int main()
{
    cout << "Week #11, Task #1" << endl;
    cout << boolalpha << (Set("123") < Set("12345")) << endl;
    cout << boolalpha << (Set("123") == Set("123")) << endl;
    (Set("123")*Set("234")).print();
    (Set("123")+Set("234")).print();
    (Set("123")-Set("234")).print();
    (Set() << '3' << '4' << '4' << '5' << '6' << '6').print();
    return 0;
}
