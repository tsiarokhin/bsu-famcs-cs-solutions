/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX_STRING_LEN = 256;

void fail()
{
    cout << "Bracket sequence is WRONG!";
    exit(1);
}

struct St
{
    int data;
    St* next;
};

void push(St *&stack, int el)
{
    St *t = new St;
    t->data=el;
    t->next=stack;
    stack = t;
    //cout << "st push " << el << " ("<<(char)el <<")"<< endl;
}

int pop(St *&stack)
{
    if (!stack) fail();
    int t = stack->data;
    St *temp = stack->next;
    delete stack;
    stack = temp;
    //cout << "st pop " << t << " ("<<(char)t <<")"<< endl;
    return t;
}

char corresponding_opening_bracket(char c)
{
    if (c == ')') return '(';
    else if (c == ']') return '[';
    else if (c == '}') return '{';
    else return '\0';
}


int main()
{
    cout << "Week #9, Task #1" << endl;
    cout << "Enter string: ";
    char s[MAX_STRING_LEN];
    cin.getline(s, MAX_STRING_LEN);
    St* stack = NULL;
    char c;
    for (int i = 0; i < strlen(s); i++)
        if (s[i] == '(' || s[i] == '[' || s[i] == '{')
            push(stack, s[i]);
        else {
            c = pop(stack);
            if (c != corresponding_opening_bracket(s[i]))
                fail();
        }
    if (stack) fail();
    else cout << "Bracket sequence is OK!";

    return 0;
}

