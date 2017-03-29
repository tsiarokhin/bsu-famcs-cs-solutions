#include "Function.h"

Function::Function(double (*func_pointer)(double, double, double, double, double), double A, double B, double C, double D):
    A(A),
    B(B),
    C(C),
    D(D),
    plot_col(RGB(rand()%256, rand()%256, rand()%256)),
    inc_dec(false),
    inc_col(RGB(255, 0, 0)),
    dec_col(RGB(0, 0, 255)),
    line_width(3),
    func_pointer(func_pointer)
{
}

double Function::func(double x)
{
    return func_pointer(x, A, B, C, D);
}



