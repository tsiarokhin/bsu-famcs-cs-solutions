/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

double add(double a, double b) {return a+b;}
double sub(double a, double b) {return a-b;}
double mult(double a, double b) {return a*b;}
double div(double a, double b) {return a/b;}

double calc(double a, double b, double (*f)(double,double))
{
    return (*f)(a,b);
}

int main()
{
    cout << "Week #6, Task #1" << endl;
    cout << "Enter A<operation>B: ";
    char c;
    double a, b;
    double (*f)(double,double);
    cin >> a >> c >> b;
    switch (c){
        case '+': f = add; break;
        case '-': f = sub; break;
        case '*': f = mult; break;
        case '/': f = div; break;
    }
    cout << " = " << calc(a, b, f);
    return 0;
}
