#include "Interface.h"
#include <windows.h>
#include <string>
#include "Controller.h"
#include "resource.h"

HWND Interface::hwnd = NULL;

void Interface::Init(HWND _hwnd){
    hwnd = _hwnd;
}

void Interface::SetPoly1(std::string s){
    SetDlgItemText(hwnd, ID_POLY, s.c_str());
}

void Interface::SetPoly2(std::string s){
    SetDlgItemText(hwnd, ID_POLY2, s.c_str());
}

void Interface::SetDegree(int deg){
    SetDlgItemText(hwnd, ID_DEGREE, (std::string("Степень: ")+std::to_string(deg)).c_str());
}

void Interface::SetCount(int count){
    SetDlgItemText(hwnd, ID_COUNT, (std::string("Кол-во чл.:  ")+std::to_string(count)).c_str());
}

std::string Interface::GetPoly2(){
    char buf[100];
    GetDlgItemText(hwnd, ID_POLY2, buf, sizeof(buf));
    return std::string(buf);
}


BOOL CALLBACK Interface::DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg){
        case WM_INITDIALOG:
            Init(hwndDlg);
            Controller::UpdateFields();
            break;

        case WM_CLOSE:
            EndDialog(hwndDlg, 0);
            break;

        case WM_COMMAND:{
            switch(LOWORD(wParam)){
                case ID_CLEAR:
                    Controller::Clear(); break;
                case ID_SWAP:
                    Controller::Swap(); break;
                case ID_PLUS:
                    Controller::Plus(GetPoly2()); break;
                case ID_MINUS:
                    Controller::Minus(GetPoly2()); break;
                case ID_MULT:
                    Controller::Mult(GetPoly2()); break;
            }
        }
        return TRUE;
    }
    return FALSE;
}
