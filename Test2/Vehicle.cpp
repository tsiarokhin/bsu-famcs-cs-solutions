#include "Vehicle.h"

Vehicle::Vehicle(string man, double price, int year): manufacturer(man), price(price), year(year)
{}

void Vehicle::setManufacturer(const string newMan)
{
    manufacturer = newMan;
}

void Vehicle::setYear(const int newYear)
{
    year = newYear;
}

Vehicle::Vehicle(const Vehicle& other): Vehicle(other.manufacturer, other.price, other.year)
{}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
    if (this == &other)
        return *this;
    manufacturer = other.manufacturer;
    price = other.price;
    year = other.year;
    return *this;
}

const int Vehicle::getYear() const
{
    return year;
}


const string Vehicle::getManufacturer() const
{
    return manufacturer;
}
