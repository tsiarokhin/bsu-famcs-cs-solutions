/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

int row_column_sum(int **a, int n, int idx, bool isRow)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += (isRow)?(a[idx][i]):(a[i][idx]);
    return sum;
}


int main()
{
    cout << "Week #5, Task #1" << endl;
    int n;
    cin >> n;
    int **a = new int*[n];
    for (int i = 0; i < n; i++)
        a[i] = new int[n];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    int sum = row_column_sum(a, n, 0, true);
    for (int i = 0; i < n; i++)
        if (row_column_sum(a, n, i, true) != sum && row_column_sum(a, n, i, false) != sum){
            cout << "Matrix is NOT magic";
            return 0;
        }
    cout << "Matrix IS magic";
    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}
