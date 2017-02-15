/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

using namespace std;

char proc_char(char c)
{
    if (c == -127) c = -111;
    else if (c <= -81) c += 32;
    if (c >= -74) c++;
    if (c == -111) c = -74;
    return c;    
}

bool cmp(char c1, char c2)
{
    if ((c1 == -48 || c1 == -47) && (c2 == -48 || c2 == -47)) return false;
    return proc_char(c1) < proc_char(c2);
}

int main()
{
    int n;
    string s; 
    cin >> n;
    list<string> lst;
    for (int i = 0; i< n; i++)
    {
        cin >> s;
        lst.push_back(s);
    }
    lst.sort();
    lst.reverse();

    cout << "\nSorted + reversed:\n";
    for (auto i = lst.begin(); i != lst.end(); i++)
        cout << *i << endl;

    cout << "\nRemoved strings with digits in first place:\n";

    lst.remove_if([](string& s){return isdigit(s[0]);});

    for (auto i = lst.begin(); i != lst.end(); i++)
        cout << *i << endl;

    cout << "\nRussian strings sorted properly:\n";

    lst.sort([](string& s1, string& s2){return lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(), cmp);});

    for (auto i = lst.begin(); i != lst.end(); i++)
        cout << *i << endl;

    
    return 0;
}
