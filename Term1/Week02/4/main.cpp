/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>

using namespace std;

enum {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC};

int main()
{
    cout << "Calculating tommorow's date" << endl;
    cout << "Enter today's date (dd mm yyyy): ";
    int day, month, year, daysInMonth;
    cin >> day >> month >> year;
    switch (month)
    {
        case JAN:
        case MAR:
        case MAY:
        case JUL:
        case AUG:
        case OCT:
        case DEC:
            daysInMonth = 31;
            break;
        case FEB:
            daysInMonth = ((year%4 == 0 && year%100 != 0) || year%400 == 0)?29:28;
            break;
        default:
            daysInMonth = 30;
    }
    if (day >= daysInMonth)
    {
        day = 1;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }
    else day++;
    cout << "Tommorow's date: " << (day<10?"0":"") << day << '.' << (month<10?"0":"") << month << '.' << year;

    return 0;
}
