#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"
#include <iostream>


class Car : public Vehicle
{
    public:
        Car(string man, double price, int year, double maxSpeed, double engineVolume, string model);
        Car(const Car& other);
        Car& operator=(const Car& other);
        void print(ostream& out = std::cout) const;
        const int getPrice() const;
    protected:
        double maxSpeed;
        double engineVolume;
        string model;
};

#endif // CAR_H
