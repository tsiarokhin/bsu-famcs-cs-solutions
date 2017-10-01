#include <string>
#include <windows.h>
#ifndef INTERFACE_H
#define INTERFACE_H

class Interface
{

private:
    static HWND hwnd;
public:
    static void Init(HWND _hwnd);
    static void SetPoly1(std::string s);
    static void SetPoly2(std::string s);
    static void SetDegree(int deg);
    static void SetCount(int count);
    static std::string GetPoly2();

    static BOOL CALLBACK DlgMain(HWND, UINT, WPARAM, LPARAM);
};


#endif // INTERFACE_H
