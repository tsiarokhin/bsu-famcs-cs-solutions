#include "Man.h"
#include <iostream>

Man::Man(string name, int age, bool sex, float weight): name(name), age(age), sex(sex), weight(weight) {}

const string& Man::getName() const
{
    return name;
}

const int Man::getAge() const
{
    return age;
}

const float Man::getWeight() const
{
    return weight;
}

void Man::setName(const string& newName)
{
    name = newName;
}

void Man::setAge(const int newAge)
{
    age = newAge;
}

void Man::setWeight(const float newWeight)
{
    weight = newWeight;
}

bool Man::operator==(const Man& rhs) const
{
    return (age == rhs.age);
}

Man& Man::operator=(const Man& rhs)
{
    if (this == &rhs) return *this;
    name = rhs.name;
    age = rhs.age;
    sex = rhs.sex;
    weight = rhs.weight;
    return *this;
}

void Man::print()
{
    cout << "Man     <name: \"" << name << "\", age: " << age << ", sex: " << (sex?"Male":"Female") << ", weight: " << weight << ">";
}
