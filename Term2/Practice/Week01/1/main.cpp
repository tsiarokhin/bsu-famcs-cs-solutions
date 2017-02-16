#include "./vect.h"
#include <iostream>

int main()
{
    vector<double> v(5);
    vector<double>::iterator p;
    int i = 0;
    for (p = v.begin(); p != v.end(); ++p)
        *p = 1.5 + i++;
    do {
        --p;
        cout << *p << " , ";
    } while (p != v.begin());
    cout << endl;

    vectorex<int> ve(3);
    ve[0] = 1;
    ve[1] = 2;
    ve[2] = 3;
    for (auto p = ve.begin(); p != ve.end(); p++)
        cout << *p << ' ';
    cout << endl;
    ve.push_front(123);
    ve.push_front(222);
    ve.push_front(333);
    for (auto p = ve.begin(); p != ve.end(); p++)
        cout << *p << ' ';
}
