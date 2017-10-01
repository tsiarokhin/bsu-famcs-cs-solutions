#include "KPolynomial.h"
#include <string>

#ifndef CONTROLLER_H
#define CONTROLLER_H

/// CHOOSE COEFFICENT TYPE
#define C_TYPE int

class Controller
{
private:
    static KPolynomial<C_TYPE> POLY;
    static KPolynomial<C_TYPE> POLY2;
public:

    static void UpdateFields();
    static void Clear();
    static void Swap();
    static void Plus(std::string poly2_str);
    static void Minus(std::string poly2_str);
    static void Mult(std::string poly2_str);

};


#endif // CONTROLLER_H
