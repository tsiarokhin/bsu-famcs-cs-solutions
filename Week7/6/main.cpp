/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_STRING_LEN = 256;

int main()
{
    cout << "Week #7, Task #6" << endl;
    cout << "Input string: ";
    char s[MAX_STRING_LEN], str1[MAX_STRING_LEN/2], new_s[MAX_STRING_LEN*2]= {'\0'};
    cin.getline(s, MAX_STRING_LEN);
    cout << "What to delete: ";
    cin.getline(str1, MAX_STRING_LEN/2);

    char* ptr = strstr(s, str1);
    *ptr = '\0';
    strcat(new_s, s);
    strcat(new_s, ptr+strlen(str1));

    cout << new_s;
    return 0;
}



