/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_CODE_LEN = 10000;
const int MAX_OPERATORS = 36;

const char operators[MAX_OPERATORS][3] = {"+", "-", "*", "/", "!", "=", "%", "~", "&", "|", "^", "*", ".", "?", ":", ">", "<",
                                          "<<", ">>", "<=", "<=", "++", "--", "==", "!=", "&&", "||", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "+=", "^="};
int operators_count[MAX_OPERATORS] = {0};
char code[MAX_CODE_LEN];

void count_operator(char* c)
{
    for (int i = 0; i < MAX_OPERATORS; i++)
        if (strcmp(c, operators[i]) == 0){
            operators_count[i]++;
            break;
        }
}

bool is_operator(char c)
{
    for (int i = 0; i < 17; i++)
        if (c == operators[i][0]) return true;
    return false;
}

int main()
{
    cout << "Week #7, Task #3" << endl;
    cout << "To stop inputing, type @" << endl;
    cin.getline(code, MAX_CODE_LEN, '@');
    int len = strlen(code);
    int i = 0;
    while (i < len)
    {
        if (is_operator(code[i])){
            if (is_operator(code[i+1])){
                code[i+2] = '\0';
                count_operator(code+i);
                i+=3;
            } else {
                code[i+1] = '\0';
                count_operator(code+i);
                i+=2;
            }
        }
        else if (code[i] == '\"'){
            while (code[++i] != '\"');
            i++;
        }
        else i++;
    }
    for (int i = 0; i < MAX_OPERATORS; i++)
        if (operators_count[i])
            cout << "Operator " <<  operators[i] << " is used " << operators_count[i] << ((operators_count[i]>1)?" times\n":" time\n");
    return 0;
}



/* Example input:


#include <iostream>
using namespace std;

int main ()
{
  int a, b;
  a = 10;
  b = 4;
  cin >> a;
  cin >> b;
  cout << "Эти подсчитаны не будут: *****************************";
  a *= (b+1)/(b%2);
  for (int i = 0; i <= 10; i++)
    if (i%2 != 0) --b;
    cout << a << "12345678765432" << b;
  return 0;
}



*/
