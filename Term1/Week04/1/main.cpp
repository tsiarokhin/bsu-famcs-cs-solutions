/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

int main()
{
    cout << "Week #4, Task #1.\n";
    int n;
    cin >> n;
    int *a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++){
        int cnt = 1;
        for (int j = 0; j < n; j++){
            if (i == j) continue;
            if (a[i] == a[j]) cnt++;
        }
        if (cnt % 2 == 1)
        {
            cout << a[i];
            return 0;
        }
    }
    return 0;
}
