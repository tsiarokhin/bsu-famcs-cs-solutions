#include "Student.h"
#include <iostream>

Student::Student(string name, int age, bool sex, float weight, int edYear): Man(name, age, sex, weight), edYear(edYear){}

const int Student::getEdYear() const
{
    return edYear;
}

void Student::setEdYear(const int newEdYear)
{
    edYear = newEdYear;
}

void Student::incEdYear()
{
    edYear++;
}

void Student::print()
{
    cout << "Student <name: \"" << name << "\", age: " << age << ", sex: " << (sex?"Male":"Female") << ", weight: " << weight << ", ed.year: " << edYear << ">";
}

Student& Student::operator=(const Student& rhs)
{
    if (this == &rhs) return *this;
    name = rhs.name;
    age = rhs.age;
    sex = rhs.sex;
    weight = rhs.weight;
    edYear = rhs.edYear;
    return *this;
}

bool Student::operator==(const Student& rhs) const
{
    return edYear == rhs.edYear;
}
