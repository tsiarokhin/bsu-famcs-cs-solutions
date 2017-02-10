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
    cout << "Week #7, Task #4" << endl;
    cout << "Input string: ";
    char s[MAX_STRING_LEN], str1[MAX_STRING_LEN/2], str2[MAX_STRING_LEN/2], new_s[MAX_STRING_LEN*2]= {'\0'};
    cin.getline(s, MAX_STRING_LEN);
    cout << "Replace: ";
    cin.getline(str1, MAX_STRING_LEN/2);
    int str1_len = strlen(str1);
    cout << "with: ";
    cin.getline(str2, MAX_STRING_LEN/2);
    char *ptr = s, *last_ptr = s;
    while (ptr = strstr(ptr, str1)){
        *ptr = '\0';
        strcat(new_s, last_ptr);
        strcat(new_s, str2);
        last_ptr = ptr += str1_len;
    }
    strcat(new_s, last_ptr);
    cout << new_s;
    return 0;
}



