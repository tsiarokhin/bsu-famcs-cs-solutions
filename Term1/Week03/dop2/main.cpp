/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <ctime>

using namespace std;

typedef long long ll;

int main ()
{
    time_t timer;
    struct tm bDay;
    ll sec, days;
    bDay.tm_hour = bDay.tm_min = bDay.tm_sec = 0;
    cout << "Week #3, Additional task #2.\nEnter your birthday (dd mm yyyy): ";
    cin >> bDay.tm_mday >> bDay.tm_mon >> bDay.tm_year;
    bDay.tm_mon--;
    bDay.tm_year -= 1900;
    time(&timer);

    sec = difftime(timer,mktime(&bDay));
    days = sec /(60*60*24);
    cout << "You have lived " << days << " days. Yay!\n";
    return 0;
}
