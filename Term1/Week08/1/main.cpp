/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX_STRING_LEN = 256;

const char delims[]  = " .,;:!-";

int glob_len;

char *strrev(char *s)
{
    size_t len = strlen(s);
    for (int i = 0; i < len/2; i++)
        swap(s[i], s[len-i-1]);
    return s;
}

bool is_palindrome(char *s)
{
    return !strcmp(s, strrev(strdup(s)));
}

void delete_word(char *&s, int from)
{
    char *to = strpbrk(s+from, delims);
    if (!to) to = s+strlen(s);
    char *new_s = new char[strlen(s)+1];
    for (int i = 0; i < strlen(s)+1; i++) new_s[i] = '\0';
    memcpy(new_s, s, from);
    strcat(new_s, to);
    delete[] s;
    s = new_s;
}

void swap_words(char *&s, int pos1, int len1, int pos2, int len2)
{
    if (pos1 > pos2) { swap(pos1,pos2); swap(len1,len2); }
    char *new_s = new char[strlen(s)+1];
    /* I'm so sorry for the following code: */
    memcpy(new_s, s, pos1); // Copying everything before first word
    memcpy(new_s+pos1, s+pos2, len2); // Copying second word
    memcpy(new_s+pos1+len2, s+pos1+len1, pos2-(pos1+len1)); // Copying everything beetween two words
    memcpy(new_s+pos1+len2+pos2-(pos1+len1), s+pos1, len1); // Copying first word
    memcpy(new_s+pos1+len2+pos2-(pos1+len1)+len1, s+pos2+len2, strlen(s)-(pos2+len2)+1); // Copying everything after second word
    delete[] s;
    s = new_s;
}

void replace_word_with_word(char *&s, int pos, char *word)
{
    char *to = strpbrk(s+pos, delims);
    if (!to) to = s+strlen(s);
    glob_len = to - (s+pos);
    char *new_s = new char[strlen(s)+strlen(word)+1];
    for (int i = 0; i < strlen(s)+strlen(word)+1; i++) new_s[i] = '\0';
    memcpy(new_s, s, pos);
    strcat(new_s, word);
    strcat(new_s, to);
    delete[] s;
    s = new_s;
}

char *find_int_in_str(char *s, bool first_time = false)
{
    char* start = strpbrk(s, "0123456789");
    //char* delim = strpbrk(s, delims);
    if (!start) return NULL;
    //if (delim > start && first_time == false) return find_int_in_str(delim);

    char* end = strpbrk(start, delims);
    if (!end) end = s+strlen(s);
    bool b = true;
    for (int i = start-s; i < (end-s); i++)
        if(!isdigit(s[i])){
            b = false;
            break;
        }
    if (b) return start;
    else return find_int_in_str(end);
}

int main()
{
    cout << "Week #8, Task #1" << endl;
    cout << "Enter string: ";
    char os[MAX_STRING_LEN];
    char *s = new char[MAX_STRING_LEN];
    cin.getline(s, MAX_STRING_LEN);
    strcpy(os, s);
    int op;
    do {
        delete[] s;
        s = new char[MAX_STRING_LEN];
        strcpy(s, os);
        cout << "\n\n\n--------------------Your string is:---------------------\n" << s << "\n--------------------------------------------------------";
        cout << "\nSelect operation:\n";
        cout << "\t1. Remove palindromes\n" << "\t2. Swap longest palindrome with biggest int_palindrome\n" << "\t3. Replace int_palindromes\n" << "\t0. Exit\nYour choise: ";
        cin >> op;
        char *w, temp[MAX_STRING_LEN], rep_word[MAX_STRING_LEN];
        int len_diff = 0, pos1, len1, pos2, len2 = 0, max_int_pal=-1;
        switch (op)
        {
            case 1:
                strcpy(temp, s);
                w = strtok(temp, delims);
                while (w) {
                    if (is_palindrome(w)) {
                        delete_word(s, w-temp+len_diff);
                        len_diff-=strlen(w);
                    }
                    w = strtok(NULL, delims);
                }
                cout << "========================Result:=========================\n" << s << "\n========================================================";
                break;
            case 2:
                strcpy(temp, s);
                w = strtok(temp, delims);
                while (w) {
                    if (is_palindrome(w))
                        if(isdigit(w[0])){
                            int t = atoi(w);
                            if (t > max_int_pal){
                                max_int_pal = t;
                                pos1 = w-temp;
                                len1 = strlen(w);
                            }
                        }
                        else if (strlen(w) > len2){
                                len2 = strlen(w);
                                pos2 = w-temp;
                            }
                    w = strtok(NULL, delims);
                }
                swap_words(s, pos1, len1, pos2, len2);
                cout << "========================Result:=========================\n" << s << "\n========================================================";
                break;
            case 3:
                cout << "Enter replacement word: ";
                cin >> rep_word;
                strcpy(temp, s);
                w = find_int_in_str(temp, true);
                while (w) {
                    replace_word_with_word(s, w-temp+len_diff, rep_word);
                    len_diff-=(strlen(rep_word)-glob_len);
                    w = find_int_in_str(w+glob_len);
                }
                cout << "========================Result:=========================\n" << s << "\n========================================================";
                break;


        }

    } while (op);

    return 0;
}

/*Example string:
11 232 abc aba kmmk qwe
*/
