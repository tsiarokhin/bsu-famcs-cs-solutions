#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>
#include <iostream>

using namespace std;

class Vehicle
{
    public:
        Vehicle(string man, double price, int year);
        Vehicle(const Vehicle& other);
        virtual Vehicle& operator=(const Vehicle& other);
        void setManufacturer(const string newMan);
        void setYear(const int newYear);
        const int getYear() const;
        const string getManufacturer() const;
        virtual void print(ostream& out = std::cout) const = 0;
        virtual const int getPrice() const = 0;
    protected:
        string manufacturer;
        double price;
        int year;
};

#endif // VEHICLE_H
