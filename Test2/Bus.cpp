#include "Bus.h"

#include <iostream>

Bus::Bus(string man, double price, int year, int maxPassengers, double engineVolume, string model):
    Vehicle(man, price, year), maxPassengers(maxPassengers), engineVolume(engineVolume), model(model) {}

void Bus::print(ostream& out) const
{
    out << "Bus (" << manufacturer << " - " << model <<"):" <<
    "\n\tPrice: " << getPrice() <<
    "\n\tYear: " << year <<
    "\n\tMax. passengers: " << maxPassengers <<
    "\n\tEng. volume: " << engineVolume << '\n';
}

const int Bus::getPrice() const
{
    return price * (year%10) * (maxPassengers/100.0);
}

Bus::Bus(const Bus& other): Bus(other.manufacturer, other.price, other.year, other.maxPassengers, other.engineVolume, other.model)
{}

Bus& Bus::operator=(const Bus& other)
{
    if (this == &other)
        return *this;
    manufacturer = other.manufacturer;
    price = other.price;
    year = other.year;
    maxPassengers = other.maxPassengers;
    engineVolume = other.engineVolume;
    model = other.model;
    return *this;
}
