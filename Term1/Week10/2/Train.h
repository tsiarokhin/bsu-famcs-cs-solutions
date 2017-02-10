#ifndef TRAIN_H
#define TRAIN_H

class Train
{
    public:
        Train(): dest(0), route(0), express(false) {}
        Train(int rt, const char* dst, bool expr);
        ~Train();
        Train(const Train& other) {*this = other;}
        void print() const;
        bool goesTo(char* dst, bool expr=false) const;
    private:
        char* dest;
        int route;
        bool express;
};

#endif // TRAIN_H
