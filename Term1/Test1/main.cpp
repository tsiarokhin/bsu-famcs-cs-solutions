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
    char s[MAX_STRING_LEN];
    cin.getline(s, MAX_STRING_LEN);
    St *num = NULL;
    St *op = NULL;
    int i = 0;
    while(s[i])
    {
        //while (s[i++] == ' ');
        if (s[i] == 'm' || s[i] == 's' || s[i] == 'a'){
            push(op, s[i]);
            i+=3;
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
                    operand1 = pop(num);
                    push(num, abs(operand1));
                    break;
                case 's':
                    operand2 = pop(num);
                    operand1 = pop(num);
                    push(num, operand1-operand2);
                    break;
                case 'm':
                    operand2 = pop(num);
                    operand1 = pop(num);
                    push(num, min(operand1,operand2));
                    break;
            }
            i++;
        }
        else if (s[i] == '(' || s[i] == ' ' || s[i] == ',') i++;
    }
    cout << pop(num);
    return 0;
}

/// min(abs(-7),sub(3,abs(-4)))
/// abs(sub(sub(6, min(abs(-7),sub(3,abs(-4)))), 14))
