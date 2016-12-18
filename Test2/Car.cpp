#include "Car.h"
#include <iostream>

Car::Car(string man, double price, int year, double maxSpeed, double engineVolume, string model):
    Vehicle(man, price, year), maxSpeed(maxSpeed), engineVolume(engineVolume), model(model) {}

void Car::print(ostream& out) const
{
    out << "Car (" << manufacturer << " - " << model <<"):" <<
    "\n\tPrice: " << getPrice() <<
    "\n\tYear: " << year <<
    "\n\tMax. speed: " << maxSpeed <<
    "\n\tEng. volume: " << engineVolume << '\n';
}

const int Car::getPrice() const
{
    return price * (year%10) * (engineVolume/10.0);
}

Car::Car(const Car& other): Car(other.manufacturer, other.price, other.year, other.maxSpeed, other.engineVolume, other.model)
{}

Car& Car::operator=(const Car& other)
{
    if (this == &other)
        return *this;
    manufacturer = other.manufacturer;
    price = other.price;
    year = other.year;
    maxSpeed = other.maxSpeed;
    engineVolume = other.engineVolume;
    model = other.model;
    return *this;
}
