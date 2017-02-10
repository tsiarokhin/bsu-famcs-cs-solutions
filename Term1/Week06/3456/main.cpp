/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

void insert_line(int**& a, int& n, int m, int k, int*ins)
{
    int **b = new int*[n+1];
    for (int i = 0; i < n+1; i++)
        b[i] = new int[m];

    for (int i = 0; i < n+1; i++)
        for (int j = 0; j < m; j++)
            if (i < k)
                b[i][j] = a[i][j];
            else if (i == k)
                b[i][j] = ins[j];
            else
                b[i][j] = a[i-1][j];

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    a = b;
    n = n+1;
}

void insert_column(int**& a, int n, int& m, int k, int*ins)
{
    int **b = new int*[n];
    for (int i = 0; i < n; i++)
        b[i] = new int[m+1];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m+1; j++)
            if (j < k)
                b[i][j] = a[i][j];
            else if (j == k)
                b[i][j] = ins[i];
            else
                b[i][j] = a[i][j-1];

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    a = b;
    m = m+1;
}

void delete_line(int**& a, int& n, int m, int k)
{
    int **b = new int*[n-1];
    for (int i = 0; i < n-1; i++)
        b[i] = new int[m];

    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < m; j++)
            if (i < k)
                b[i][j] = a[i][j];
            else
                b[i][j] = a[i+1][j];

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    a = b;
    n = n-1;
}

void delete_column(int**& a, int n, int &m, int k)
{
    int **b = new int*[n];
    for (int i = 0; i < n; i++)
        b[i] = new int[m-1];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m-1; j++)
            if (j < k)
                b[i][j] = a[i][j];
            else
                b[i][j] = a[i][j+1];

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;

    a = b;
    m = m-1;
}

int main()
{
    cout << "Week #6, Tasks #3, 4, 5, 6 combined" << endl;
    cout << "Input array dimensions: ";
    int n, m;
    cin >> n >> m;
    int** a = new int*[n];
    for (int i = 0; i < n; i++)
        a[i] = new int[m];

    cout << "Input array elements:\n\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    cout << "\nSelect operation:\n" << "\t1. Insert line\n" << "\t2. Insert column\n"
                                    << "\t3. Delete line\n" << "\t4. Delete column\n" << "Your's choice(1-4): ";
    char c;
    cin >> c;

    int k, p;
    int* ins;
    cout << "Input line/column index (starting from 1): ";
    cin >> k; k--;

    if (c == '1' || c == '2'){
        p = (c=='1')?m:n;
        ins = new int[p];
        cout << "Input line/column (" << p << " numbers): ";
        for (int i = 0; i < p; i++)
            cin >> ins[i];
    }

    switch (c){
        case '1': insert_line(a, n, m, k, ins); break;
        case '2': insert_column(a, n, m, k, ins); break;
        case '3': delete_line(a, n, m, k); break;
        case '4': delete_column(a, n, m, k); break;
    }

    cout << "\nResulting array:\n\n";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++)
            cout << a[i][j] << ' ';
        cout << '\n';
    }

    for (int i = 0; i < n; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}
