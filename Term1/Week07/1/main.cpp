/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_STRING_LEN = 256;

namespace hash
{
    static char hash_array[15000] = {0};
    static int s_hash(char* s)
    {
        int hash = 7;
        for (int i = 0; i < strlen(s); i++) {
            hash = hash*31 + s[i];
        }
        return hash%15000;
    }
    static int get_count(char* s){ return hash_array[s_hash(s)]; }
    static void inc_count(char* s){ hash_array[s_hash(s)]++; }
    static void zero_count(char* s){ hash_array[s_hash(s)] = 0; }
}



int main()
{
    cout << "Week #7, Task #1" << endl;
    char s[MAX_STRING_LEN], s2[MAX_STRING_LEN];
    char* word;
    cin.getline(s, MAX_STRING_LEN);
    strcpy(s2, s);
    word = strtok (s, " .,;:!-");
    while (word){
        if (strlen(word) == 2)
            hash::inc_count(word);
        word = strtok (NULL, " .,;:!-");
    }
    word = strtok (s2, " .,;:!-");
    while (word){
        if (strlen(word) == 2 && hash::get_count(word) > 0){
            cout << word << " - " << hash::get_count(word) << '\n';
            hash::zero_count(word);
        }
        word = strtok (NULL, " .,;:!-");
    }
    return 0;
}
