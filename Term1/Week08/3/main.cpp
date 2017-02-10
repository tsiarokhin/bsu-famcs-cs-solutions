/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX_STRING_LEN = 256;

const char delims[]  = " .,;:!-";

double* find_reals (char *s, int &res_size)
{
    double *a = new double[100];
    int i = 0, j = 0;
    while (s[i]){
        while (s[i] && !isdigit(s[i])) i++;
        if (s[i]) a[j++] = atof(s+i);
        while (s[i] && (isdigit(s[i]) || s[i] == '.')) i++;
    }
    res_size = j;
    return a;
}

int main()
{
    cout << "Week #8, Task #3" << endl;
    cout << "Enter string: ";
    char *s = new char[MAX_STRING_LEN];
    cin.getline(s, MAX_STRING_LEN);
    double *a;
    int n;
    a = find_reals(s, n);
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';


    return 0;
}
