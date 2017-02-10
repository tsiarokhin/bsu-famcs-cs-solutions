#ifndef MAN_H
#define MAN_H
#include <string>
using namespace std;

class Man
{
    public:
        Man(string name, int age = 0, bool sex = MALE, float weight = 0);

        const string& getName() const;
        const int     getAge() const;
        const float   getWeight() const;

        void setName(const string& newName);
        void setAge(const int newAge);
        void setWeight(const float newWeight);

        virtual bool operator==(const Man& rhs) const;
        Man& operator=(const Man& rhs);
        virtual void print();

        static const bool MALE = true;
        static const bool FEMALE = false;
    protected:
        string name;
        int age;
        bool sex;
        float weight;

};

#endif // MAN_H
