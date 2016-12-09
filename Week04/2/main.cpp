/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;
typedef long long ll;

int main()
{
    cout << "Week #4, Task #2.\n";
    int n;
    cin >> n;
    ll *a = new ll[n];
    ll maxm = 0, ma, mb, mc;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                if (i!=j && j!=k && i!=k)
                    if (a[i]*a[j]*a[k] >= maxm){
                        maxm = a[i]*a[j]*a[k];
                        ma = a[i]; mb = a[j]; mc = a[k];
                    }
    cout << ma << " * " << mb << " * " << mc << " = " << maxm;
    return 0;
}
