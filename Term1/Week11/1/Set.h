#ifndef SET_H
#define SET_H
const int MAX_SIZE = 256;
const int CONTAINER_LENGTH = MAX_SIZE+1;

class Set
{
    public:
        Set();
        Set(const char* s);
        Set(const Set& other);
        ~Set();
        void print();
        Set& operator=(const Set& rhs);
        Set& operator<<(const char rhs);
        Set& operator>>(char& rhs);
        Set operator*(const Set& rhs) const;
        Set operator+(const Set& rhs) const;
        Set operator-(const Set& rhs) const;
        bool operator<(const Set& rhs) const;
        bool operator==(const Set& rhs) const;
    private:
        char* set_container;
};

#endif // SET_H
