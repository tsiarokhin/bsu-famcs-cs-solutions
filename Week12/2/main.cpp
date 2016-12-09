/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include "DArray.h"
#include "DStack.h"
#include "DQueue.h"


using namespace std;

int main()
{
    cout << "Week #12, Task #2" << endl;
    DArray a(10);
    a[0] = 777;
    a.print();
    cout << endl << a[0] << endl;
    DStack st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.print(); cout << endl;
    DQueue q;
    q.push(5);
    q.push(6);
    q.push(7);
    q.print(); cout << endl;
    q.pop();
    q.print(); cout << endl;
    return 0;
}
