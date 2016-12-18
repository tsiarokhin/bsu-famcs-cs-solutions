#ifndef BUS_H
#define BUS_H

#include "Vehicle.h"
#include <iostream>

class Bus : public Vehicle
{
    public:
        Bus(string man, double price, int year, int maxPassengers, double engineVolume, string model);
        Bus(const Bus& other);
        Bus& operator=(const Bus& other);
        void print(ostream& out = std::cout) const;
        const int getPrice() const;
    protected:
        int maxPassengers;
        double engineVolume;
        string model;
};

#endif // BUS_H
