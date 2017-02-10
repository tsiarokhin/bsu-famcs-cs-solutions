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

int top(St *&stack)
{
    return stack->data;
}

void to_OPZ(char *&s)
{
    char* a = new char[MAX_STRING_LEN*2];
    int j = 0;
    St *stack = NULL;
    int i = 0;
    while(s[i])
    {
        if (isdigit(s[i]) || (s[i] == '-' && isdigit(s[i+1])) ) {
            while (isdigit(s[i]) || s[i] == '-')
                a[j++] = s[i++];
            a[j++] = ' ';
            i--;
        }
        else if ((!stack) && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'))
            push(stack, s[i]);
        else if (s[i] == '+' || s[i] == '-'){
            if (top(stack) != '(') {
                a[j++] = pop(stack);
                a[j++] = ' ';
            }
            push(stack, s[i]);
        }
        else if (s[i] == '*' || s[i] == '/'){
            if (top(stack) == '+' || top(stack) == '-')
                push(stack, s[i]);
            else {
                a[j++] = pop(stack);
                a[j++] = ' ';
                push(stack, s[i]);
            }
        }
        else if (s[i] == '(')
            push(stack, s[i]);
        else if (s[i] == ')'){
            while (top(stack) != '('){
                a[j++] = pop(stack);
                a[j++] = ' ';
            }
            pop(stack);
        }
        i++;
    }
    while (stack) {
        a[j++] = pop(stack);
        a[j++] = ' ';
    }
    a[j] = '\0';
    delete[] s;
    s = a;
}

int main()
{
    cout << "Week #9, Task #4" << endl;
    cout << "Enter string:\n\t";
    char* s = new char[MAX_STRING_LEN];
    cin.getline(s, MAX_STRING_LEN);
    to_OPZ(s);
    cout << "In postfix form: \n\t" << s << endl;
    St *num = NULL;
    St *op = NULL;
    int i = 0;
    while(s[i])
    {
        if (isdigit(s[i]) || (s[i] == '-' && isdigit(s[i+1]))){
            push(num, atoi(s+i));
            while (isdigit(s[i]) || s[i] == '-') i++;
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'){
            int operand1, operand2;
            operand2 = pop(num);
            operand1 = pop(num);
            switch(s[i])
            {
                case '+': push(num, (operand1 + operand2)); break;
                case '-': push(num, (operand1 - operand2)); break;
                case '*': push(num, (operand1 * operand2)); break;
                case '/': push(num, (operand1 / operand2)); break;
            }
            i++;
        }
        else if (s[i] == ' ') i++;
    }
    cout << "Result:\n\t" << pop(num);
    return 0;
}

// 3 + 4 * 2 / (3 - 2)
