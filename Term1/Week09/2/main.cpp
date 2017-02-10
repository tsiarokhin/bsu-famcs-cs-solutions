/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

const int MAX_STRING_LEN = 256;

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
    int t = stack->data;
    St *temp = stack->next;
    delete stack;
    stack = temp;
    //cout << "st pop " << t << " ("<<(char)t <<")"<< endl;
    return t;
}


int main()
{
    cout << "Week #9, Task #2" << endl;
    cout << "Enter string: ";
    char s[MAX_STRING_LEN];
    cin.getline(s, MAX_STRING_LEN);
    St *num = NULL;
    St *op = NULL;
    int i = 0;
    while(s[i])
    {
        //while (s[i++] == ' ');
        if (s[i] == 'a' || s[i] == 'i'){
            push(op, s[i]);
            i+=2;
        }
        else if (isdigit(s[i]) || s[i] == '-'){
            push(num, atoi(s+i));
            while (isdigit(s[i]) || s[i] == '-') i++;
        }
        else if (s[i] == ')') {
            int operand1, operand2, operation;
            operation = pop(op);
            switch(operation)
            {
                case 'a':
                    operand2 = pop(num);
                    operand1 = pop(num);
                    push(num, max(operand1, operand2));
                    break;
                case 'i':
                    operand2 = pop(num);
                    operand1 = pop(num);
                    push(num, min(operand1, operand2));
                    break;
            }
            i++;
        }
        else if (s[i] == '(' || s[i] == ' ' || s[i] == ',' || s[i] == 'm') i++;
    }
    cout << pop(num);
    return 0;
}
