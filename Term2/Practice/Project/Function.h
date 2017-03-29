#ifndef FUNCTION_H
#define FUNCTION_H
#include <windows.h>
#include <cstdlib>

class Function
{
    public:
        Function(double (*func_pointer)(double, double, double, double, double), double A = 1.0, double B = 1.0, double C = 0, double D = 0);
        double func(double x);

        double A;
        double B;
        double C;
        double D;
        COLORREF plot_col;
        bool     inc_dec;
        COLORREF inc_col;
        COLORREF dec_col;
        int line_width;
        double (*func_pointer)(double, double, double, double, double);
};

#endif // FUNCTION_H
