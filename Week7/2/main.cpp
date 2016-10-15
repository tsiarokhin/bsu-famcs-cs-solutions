/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_STRING_LEN = 256;

bool is_delimiter(char c)
{
    switch (c){
        case ' ':case '.':case ',':case ';':case ':':case '!':case '-':case '\0': return true;
        default: return false;
    }
}

int main()
{
    cout << "Week #7, Task #2" << endl;
    char os[MAX_STRING_LEN], s[MAX_STRING_LEN];
    cin.getline(os, MAX_STRING_LEN);
    strcpy(s, os);
    int st = 0, en = 0;
    while (s[st] != '\0')
        if (!is_delimiter(s[st])){
            en = st + 1;
            while (!is_delimiter(s[en])) en++;
            for (int i = 0; i < (en-st)/2; i++)
                swap(s[st+i], s[en-i-1]);
            st = en;

        } else st++;
    cout << s;
    return 0;
}
