/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

/*
   В первый день спортсмен пробежал x километров,
   а затем он каждый день увеличивал пробег на 10%
   от предыдущего значения. По данному числу y
   определите номер дня, на который пробег спортсмена
   составит не менее y километров.
   Например, при вводе 10 20 программа должна вывести 9.
   x и y – действительные числа, ответ – целое число.
*/
#include <iostream>

using namespace std;

int main()
{
    cout << "Solving task #2\nEnter x and y: " << endl;
    double x, y;
    int n = 1;
    cin >> x >> y;
    while (x < y)
    {
        x *= 1.1;
        n++;
    }
    cout << n;
    return 0;
}
