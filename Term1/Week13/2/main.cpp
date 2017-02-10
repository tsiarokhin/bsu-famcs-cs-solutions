#include <iostream>

#include "Array.h"
#include "Polinom.h"

using namespace std;

int main ()
{
    Array a1(5, 1);
    Array a2(10, 2);
    a1.print(); cout << " + "; a2.print(); cout << " = "; (a1+a2).print(); cout << endl;

    Polinom a(3,4), b(5,7);
    Polinom t = a*b;
    a.print(); cout << " * "; b.print(); cout << " = "; t.print(); cout << endl;

    try {
        Array temp(3);
        temp[4] = 0;
    } catch (Array::IndexOutOfBoundsExeption){
        cerr << "ERROR! Index out of bounds!";
    }


    return 0;
}
