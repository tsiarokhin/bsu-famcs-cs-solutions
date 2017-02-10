/*
	Copyright (c) 2016 Maxim Teryokhin
	This code is licensed under MIT. See LICENSE file for more details.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Train.h"

using namespace std;

const int MAX_STRING_LEN = 256;
const int MAX_DESTINATIONS = 11;
const int MAX_TRAINS = 50;
const char DESTINATIONS[MAX_DESTINATIONS][15] = {"Minsk", "Grodno", "Gomel", "Mogilev", "Vitebsk", "Brest", "Moskow", "Vilnius", "Warsaw", "Riga", "Kiev"};

int random_route()
{
    return 100 + (rand()%900);
}

const char* random_destination()
{
    return DESTINATIONS[rand()%MAX_DESTINATIONS];
}

bool random_bool()
{
    return rand()%2;
}

int main()
{
    srand(time(NULL));
    char dest[MAX_STRING_LEN], c;
    bool express;
    cout << "Week #10, Task #2" << endl;
    cout << "\nList of all trains:" << endl;
    Train** trains = new Train*[MAX_TRAINS];
    for (int i = 0; i < MAX_TRAINS; i++){
        trains[i] = new Train(random_route(), random_destination(), random_bool());
        cout << '\t';
        trains[i]->print();
        cout << '\n';
    }

    cout << "\n\nEnter destination: ";
    cin.getline(dest, MAX_STRING_LEN);
    cout << "Express or Normal? (e/n): ";
    cin >> c;
    express = (c == 'e')?true:false;

    cout << "\nList of " << ((express)?"express":"normal") << " trains going to " << dest << ":\n";
    for (int i = 0; i < MAX_TRAINS; i++)
        if (trains[i]->goesTo(dest, express)){
            cout << '\t';
            trains[i]->print();
            cout << '\n';
        }
    return 0;
}
