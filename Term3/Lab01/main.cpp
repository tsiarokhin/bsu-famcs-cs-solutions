/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/
#undef UNICODE
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include "resource.h"
#include "KPolynomial.h"

using namespace std;

HINSTANCE hInst;
KPolynomial<int> POLY = {{1, 2}, {-2, 1}, {1, 0}};
KPolynomial<int> POLY2;

void UpdateFields(HWND hwndDlg)
{
    SetDlgItemText(hwndDlg, ID_POLY, POLY.toString().c_str());
    SetDlgItemText(hwndDlg, ID_DEGREE, (string("Степень: ")+to_string(POLY.Degree())).c_str());
    SetDlgItemText(hwndDlg, ID_COUNT, (string("Кол-во чл.:  ")+to_string(POLY.Count())).c_str());
}

void GetPoly2(HWND hwndDlg)
{
    char buf[100];
    GetDlgItemText(hwndDlg, ID_POLY2, buf, sizeof(buf));
    POLY2.fromString(string(buf));
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        UpdateFields(hwndDlg);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
            case ID_CLEAR: {
                POLY.Clear();
                POLY2.Clear();
                UpdateFields(hwndDlg);
                SetDlgItemText(hwndDlg, ID_POLY2, "");
                break;
            }
            case ID_SWAP: {
                POLY.Swap(POLY2);
                UpdateFields(hwndDlg);
                SetDlgItemText(hwndDlg, ID_POLY2, POLY2.toString().c_str());
                break;
            }
            case ID_PLUS: {
                GetPoly2(hwndDlg);
                POLY += POLY2;
                UpdateFields(hwndDlg);
                break;
            }
            case ID_MINUS: {
                GetPoly2(hwndDlg);
                POLY -= POLY2;
                UpdateFields(hwndDlg);
                break;
            }
            case ID_MULT: {
                GetPoly2(hwndDlg);
                POLY *= POLY2;
                UpdateFields(hwndDlg);
                break;
            }
        }
    }
    return TRUE;
    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    //cin >> POLY;
//    KPolynomial<int> poly = {{1, 2}, {-2, 1}, {1, 0}};
//    KPolynomial<int> poly2 = string("1^2 2^1 1^0");

    //cin >> poly;
//    cout << '(' << poly << ") * (" << poly2 << ") == ";
//    cout << poly*poly2 << endl;
    //cout << "Coef at x^2 == " << poly[2].Coeff() << endl;

//    for (auto it = poly.begin(); it != poly.end(); it++)
//        cout << (*it).Coeff() << "x^" << (*it).Degree() << endl;


    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
