/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_STRING_LEN = 256;

bool is_alphabetic(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'ÿ'))
        return true;
    else return false;
}
 bool is_numeric(char c)
 {
     if (c >= '0' && c <= '9')
        return true;
     else return false;
 }

int main()
{
    cout << "Week #7, Task #5" << endl;
    char s[MAX_STRING_LEN];
    cin.getline(s, MAX_STRING_LEN);
    int i = -1, alphabetic = 0, numeric = 0, other = 0;
    while (s[++i])
        if (is_alphabetic(s[i]))
            alphabetic++;
        else if (is_numeric(s[i]))
            numeric++;
        else other++;
    cout << "Total:\n\t" << alphabetic << " alphabetic char.\n\t" << numeric << " numeric char.\n\t" << other << " other char.";
    return 0;
}
