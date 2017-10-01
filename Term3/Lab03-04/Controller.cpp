#include <string>
#include "Controller.h"
#include "KPolynomial.h"
#include "Interface.h"

KPolynomial<C_TYPE> Controller::POLY = {{1, 2}, {-2, 1}, {1, 0}};
KPolynomial<C_TYPE> Controller::POLY2;

void Controller::UpdateFields(){
    GetStringRepr<C_TYPE> visitor;
    POLY.accept(visitor);

    Interface::SetPoly1(visitor.string_repr);
    Interface::SetDegree(POLY.Degree());
    Interface::SetCount(POLY.Count());
}

void Controller::Clear(){
    POLY.Clear();
    POLY2.Clear();
    UpdateFields();
    Interface::SetPoly2("");
}

 void Controller::Swap(){
    POLY.Swap(POLY2);
    UpdateFields();
    Interface::SetPoly2(POLY2.toString());
}

 void Controller::Plus(std::string poly2_str){
    POLY2.fromString(poly2_str);
    POLY += POLY2;
    UpdateFields();
}

 void Controller::Minus(std::string poly2_str){
    POLY2.fromString(poly2_str);
    POLY -= POLY2;
    UpdateFields();
}

 void Controller::Mult(std::string poly2_str){
    POLY2.fromString(poly2_str);
    POLY *= POLY2;
    UpdateFields();
}



