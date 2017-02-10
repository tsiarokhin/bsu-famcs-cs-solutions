/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

/*
  По данному натуральному числу n найдите сумму чисел
  1+1/1!+1/2!+1/3!+...+1/n!.
  Эта сумма стремится к e;
*/

#include <iostream>

using namespace std;

int main()
{
    cout << "Solving task #5\nEnter n: ";
    long long n, currentFactorial = 1;
    cin >> n;
    double res = 1.0;
    for (int i = 0; i < n; i++)
        res += 1.0/(currentFactorial *= (i+1));
    cout << res;
    return 0;
}
