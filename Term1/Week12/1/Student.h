#ifndef STUDENT_H
#define STUDENT_H

#include <Man.h>


class Student : public Man
{
    public:
        Student(string name, int age = 0, bool sex = MALE, float weight = 0, int edYear = 0);

        const int getEdYear() const;
        void setEdYear(const int newEdYear);
        void incEdYear();
        virtual void print();
        Student& operator=(const Student& rhs);
        virtual bool operator==(const Student& rhs) const;

    protected:
        int edYear;
};

#endif // STUDENT_H
