/*
    Author: Maxim Teryokhin
*/
#include <iostream>
#include <fstream>
#include "Vehicle.h"
#include "Car.h"
#include "Bus.h"

using namespace std;

const int MAX_VEHICLES = 3;

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    Vehicle* arr[MAX_VEHICLES];
    //arr[0] = new Car("LADA", 1000, 2012, 120, 1.5, "2107");
    //arr[1] = new Bus("MAZ", 5000, 2014, 150, 47.5, "103");
    //arr[0]->print();
    //arr[1]->print();
    char type;
    string man;
    double price;
    int year;
    double maxPassOrSpeed;
    double engineVolume;
    string model;
    for (int i = 0; i < MAX_VEHICLES; i++){
        fin >> type >> man >> price >> year >> maxPassOrSpeed >> engineVolume >> model;
        if (type == 'c')
            arr[i] = new Car(man, price, year, maxPassOrSpeed, engineVolume, model);
        else if (type == 'b')
            arr[i] = new Bus(man, price, year, (int)maxPassOrSpeed, engineVolume, model);
    }
    for (int i = 0; i < MAX_VEHICLES; i++){
        arr[i]->print();
        arr[i]->print(fout);
    }
    cout << "Enter year: ";
    cin >> year;
    for (int i = 0; i < MAX_VEHICLES; i++)
        if (arr[i]->getYear() == year)
            cout << "Vehicle #" << i+1 << ", calculated price: " << arr[i]->getPrice() << '\n';
    for (int i = 0; i < MAX_VEHICLES; i++)
        for (int j = i+1; j < MAX_VEHICLES; j++)
            if (arr[i]->getManufacturer() == arr[j]->getManufacturer())
                cout << "Vehicles #" << i+1 << " and #" << j+1 << " have same manufacturer\n";
    fout.close();
    return 0;
}
