/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <fstream>

#include "Linear.h"
#include "Exponential.h"

using namespace std;

int main()
{
    Linear as(1, 2);
    for (int i = 1; i <= 10; i++)
        cout << as[i] << ' ';
    cout << "...\nSum from 1 to 10: " << as.sum(10) << "\n\n";

    Exponential gs(1, 2);
    for (int i = 1; i <= 10; i++)
        cout << gs[i] << ' ';
    cout << "...\nSum from 1 to 10: " << gs.sum(10) << "\n\n";

    ofstream fout("output.txt");
    fout << "Exponential series:\n";
    for (int i = 1; i <= 10; i++)
        fout << gs[i] << ' ';

    Series* arr[2];
    arr[0] = &as;
    arr[1] = &gs;
    for (int i = 0; i < 2; i++){
        cout << "Series #" << i+1 << ":\n";
        for (int j = 1; j <= 10; j++)
            cout << (*arr[i])[j] << ' ';
        cout << "...\nSum from 1 to 10: " << arr[i]->sum(10) << "\n\n";
    }

    return 0;
}
