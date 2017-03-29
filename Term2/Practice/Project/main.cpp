/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>
#include <stdio.h>
#include <cmath>
#include "resource.h"
#include "plot_utils.h"
#include "Function.h"
#include <map>
#include <vector>

HINSTANCE hInst;
HWND hDlg;
PAINTSTRUCT _paintstruct;
RECT rect;

int centerX, centerY;
int width, height;
bool clicked = false;
double clickedX, clickedY;
bool drag = false;
int oldX, oldY;

int DP = 25;

std::map<HWND, Function> functions;

int PLOT_PEN_WIDTH = 3;
COLORREF PLOT_PEN_COLOR = RGB(255, 0, 0);

auto axisPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
auto markPen = CreatePen(PS_SOLID, 1+(DP>5), RGB(0, 0, 0));
auto dashPen = CreatePen(PS_DASH, 1, RGB(0, 0, 0));
auto nanPen  = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
auto nanBrush = CreateSolidBrush(RGB(255, 255, 255));


namespace Functions {
    double ASin(double x, double A, double B, double C, double D) {
        return A*asin(B*x) + C;
    }
    double ACos(double x, double A, double B, double C, double D) {
        return A*acos(B*x) + C;
    }
    double ATg(double x, double A, double B, double C, double D) {
        return A*atan(B*x) + C;
    }
    double Poly3(double x, double A, double B, double C, double D) {
        return A*x*x*x + B*x*x + C*x + D;
    }
    double Sin(double x, double A, double B, double C, double D) {
        return A*sin(B*x) + C;
    }
    double Cos(double x, double A, double B, double C, double D) {
        return A*cos(B*x) + C;
    }
    double Tg(double x, double A, double B, double C, double D) {
        return A*tan(B*x) + C;
    }
    double AX(double x, double A, double B, double C, double D) {
        return pow(A, x) + B;
    }
    double XA(double x, double A, double B, double C, double D) {
        return pow(x, A) + B;
    }
    double Ln(double x, double A, double B, double C, double D) {
        return A*log(B*x) + C;
    }
    double Other1(double x, double A, double B, double C, double D) {
        return (A*pow(1+x, C) - 1) / (B + pow(x, C)) ;
    }
    double Other2(double x, double A, double B, double C, double D) {
        return (A*pow(1+x, C) - 1) / (B + pow(x, C)) ;
    }

};

WORD new_func_id;
const std::map <WORD, double (*)(double, double, double, double, double)> FUNC_POINTER_BY_ID {
  {MENU_F_X3,  Functions::Poly3},
  {MENU_F_ASIN,Functions::ASin},
  {MENU_F_ACOS,Functions::ACos},
  {MENU_F_ATG, Functions::ATg},
  {MENU_F_AX,  Functions::AX},
  {MENU_F_XA,  Functions::XA},
  {MENU_F_LN,  Functions::Ln},
  {MENU_F_O1,  Functions::Other1},
  {MENU_F_O2,  Functions::Other2},
  {MENU_F_SIN, Functions::Sin},
  {MENU_F_COS, Functions::Cos},
  {MENU_F_TG,  Functions::Tg}
};

int numberOnEveryNMark()
{
    if (DP <= 1) return 50;
    if (DP <= 2) return 25;
    if (DP <= 4) return 10;
    if (DP <= 6) return 5;
    if (DP <= 8) return 4;
    if (DP <= 10) return 3;
    if (DP <= 20) return 2;
    return 1;
}


void SavePlot()
{
    static OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "plot.bmp";
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = (LPCSTR)"Bitmap Image(*.bmp)\0*.txt\0All Files (*.*)\0*.*\0";
    ofn.lpstrFile = (LPSTR)szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = (LPCSTR)"bmp";

    GetSaveFileName(&ofn);
    ScreenShot(ofn.lpstrFile, hDlg);
}

void DrawNaNPoint(HDC& hDC, double fx, double fy, int rad)
{
    auto oldPen = SelectObject(hDC, nanPen);
    auto oldBrush = SelectObject(hDC, nanBrush);
    Ellipse(hDC, centerX + fx*DP-rad, centerY - fy*DP-rad, centerX + fx*DP+rad, centerY - fy*DP+rad);
    SelectObject(hDC, oldBrush);
    SelectObject(hDC, oldPen);
}

void DrawAxes(HDC& hDC, int width, int height)
{
    SelectObject(hDC, axisPen);

    MoveToEx(hDC, centerX, 0, NULL);
    LineTo(hDC, centerX, height);

    MoveToEx(hDC, 0, centerY, NULL);
    LineTo(hDC, width, centerY);
}

void DrawMarks(HDC& hDC, int maxXMarks, int maxYMarks)
{
    SelectObject(hDC, markPen);
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(0, 0, 255));
    char t[20];

    SetTextAlign(hDC, TA_CENTER);
    for (int i = -maxXMarks; i <= maxXMarks; i++){
        MoveToEx(hDC, centerX + i*DP, centerY - 3, NULL);
        LineTo(hDC,   centerX + i*DP, centerY + 3);
        if (i % numberOnEveryNMark() == 0 && i != 0) {
            sprintf(t, "%d", i);
            TextOut(hDC,  centerX + i*DP, centerY + 6, t, strlen(t));
        }
    }

    SetTextAlign(hDC, TA_RIGHT);
    for (int i = -maxYMarks; i <= maxYMarks; i++){
        MoveToEx(hDC, centerX - 3, centerY - i*DP, NULL);
        LineTo(hDC,   centerX + 3, centerY - i*DP);
        if (i % numberOnEveryNMark() == 0 && i != 0) {
            sprintf(t, "%d", i);
            TextOut(hDC,  centerX - 6, centerY - i*DP - 10, t, strlen(t));
        }
    }
}

void DrawPlots(HDC& hDC, int maxXMarks, int maxYMarks)
{
    const double UNIT = 1.0/DP;
    for (auto it = functions.begin(); it != functions.end(); it++)
    {
        MoveToEx(hDC, 0, 0, NULL);
        Function& CUR_F = it->second;
        auto funcPen = CreatePen(PS_SOLID, CUR_F.line_width, CUR_F.plot_col);
        auto func_incPen = CreatePen(PS_SOLID, CUR_F.line_width, CUR_F.inc_col);
        auto func_decPen = CreatePen(PS_SOLID, CUR_F.line_width, CUR_F.dec_col);
        bool wasNaN = false;
        std::vector< std::pair<double, double> > NaNpoints;
        SelectObject(hDC, funcPen);
        for (double i = -maxXMarks/2 - 10; i < maxXMarks/2 + 10; i+=UNIT){
            double Y = CUR_F.func(i);
            if (Y != Y) {
                if (!wasNaN)
                    NaNpoints.push_back(std::make_pair(i-UNIT, CUR_F.func(i-UNIT)));
                wasNaN = true;
                continue;
            }
            if(CUR_F.inc_dec) {
                if (CUR_F.func(i-UNIT) < Y)
                    SelectObject(hDC, func_incPen);
                else if (CUR_F.func(i-UNIT) > Y)
                    SelectObject(hDC, func_decPen);
            }
            if (wasNaN){
                MoveToEx(hDC, centerX + i*DP, centerY - Y*DP, NULL);
                NaNpoints.push_back(std::make_pair(i, Y));
                wasNaN = false;
            }
            else
                LineTo(hDC, centerX + i*DP, centerY - Y*DP);
        }
        while (!NaNpoints.empty()) {
            DrawNaNPoint(hDC, NaNpoints.back().first, NaNpoints.back().second, CUR_F.line_width);
            NaNpoints.pop_back();
        }
        DeleteObject(funcPen);
        DeleteObject(func_incPen);
        DeleteObject(func_decPen);
    }
}

void DrawClickedPoint(HDC& hDC, int width, int height)
{
    char t[20];
    if (clicked) {
        SelectObject(hDC, dashPen);
        SetTextColor(hDC, RGB(0, 0, 0));
        SetTextAlign(hDC, TA_LEFT | TA_BOTTOM);

        MoveToEx(hDC, centerX + (clickedX*DP), centerY - (clickedY*DP), NULL);
        LineTo(hDC,   centerX + (clickedX*DP), centerY);
        MoveToEx(hDC, centerX + (clickedX*DP), centerY - (clickedY*DP), NULL);
        LineTo(hDC,   centerX, centerY - clickedY*DP);
        sprintf(t, "X = %.2f | Y = %.2f", clickedX, clickedY);
        TextOut(hDC, 0, height, t, strlen(t));
    }
}

void OnPaint()
{
    auto hRealDC = BeginPaint(hDlg, &_paintstruct);

    // Double-buffering
    auto hDC = CreateCompatibleDC(hRealDC);
    auto hScreen = CreateCompatibleBitmap(hRealDC, width, height);
    auto oldBmp = (HBITMAP)SelectObject(hDC, hScreen);
    PatBlt(hDC, 0, 0, width, height, WHITENESS);
    // Double-buffering

    DrawAxes(hDC, width, height);

    int maxXMarks = (abs(centerX)+width)/DP;
    int maxYMarks = (abs(centerY)+height)/DP;
    DrawMarks(hDC, maxXMarks, maxYMarks);

    DrawPlots(hDC, maxXMarks, maxYMarks);

    DrawClickedPoint(hDC, width, height);

    // Double-buffering
    BitBlt( hRealDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY);
    SelectObject(hDC, oldBmp );
    DeleteObject(hScreen);
    DeleteDC(hDC);
    // Double-buffering

    EndPaint(hDlg, &_paintstruct);
}

void SelectColor(HWND hwndDlg, COLORREF& color)
{
    static CHOOSECOLOR cc;
    static COLORREF acrCustClr[16];

    ZeroMemory(&cc, sizeof(CHOOSECOLOR));
    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = hwndDlg;
    cc.lpCustColors = (LPDWORD)acrCustClr;
    cc.rgbResult = color;
    cc.Flags = CC_FULLOPEN | CC_RGBINIT;

    if (ChooseColor(&cc)==TRUE)
        color = cc.rgbResult;
}


BOOL CALLBACK DlgFunc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        char buf[100];
        MENUITEMINFO MenuItem;
        memset(&MenuItem,0, sizeof(MenuItem));
        MenuItem.cbSize = sizeof(MenuItem);
        MenuItem.fMask =MIIM_TYPE;
        MenuItem.fType = MFT_STRING;
        MenuItem.cch = 100;
        MenuItem.dwTypeData = buf;
        GetMenuItemInfo(GetMenu(hDlg), new_func_id, FALSE, &MenuItem);
        SetWindowText(hwndDlg, MenuItem.dwTypeData);

        Function& CUR_F = functions.insert(std::make_pair(hwndDlg, Function(FUNC_POINTER_BY_ID.at(new_func_id)))).first->second;
        sprintf(buf, "%.1f", CUR_F.A); SetDlgItemText(hwndDlg, FX_A, buf);
        sprintf(buf, "%.1f", CUR_F.B); SetDlgItemText(hwndDlg, FX_B, buf);
        sprintf(buf, "%.1f", CUR_F.C); SetDlgItemText(hwndDlg, FX_C, buf);
        sprintf(buf, "%.1f", CUR_F.D); SetDlgItemText(hwndDlg, FX_D, buf);
        SendDlgItemMessage(hwndDlg, FX_LINE_WIDTH, TBM_SETRANGE, TRUE, MAKELONG(1, 30));
        SendDlgItemMessage(hwndDlg, FX_LINE_WIDTH, TBM_SETPOS, TRUE, CUR_F.line_width);

        //sprintf(buf, "%d", CUR_F.line_width); SetDlgItemText(hwndDlg, FX_LINE_WIDTH, buf);

        InvalidateRect(hDlg, NULL, FALSE);

    }
    return TRUE;

    case WM_CLOSE:
        functions.erase(hwndDlg);
        InvalidateRect(hDlg, NULL, FALSE);
        EndDialog(hwndDlg, 0);
        return TRUE;

    case WM_HSCROLL:
    case WM_VSCROLL:
        if ((HWND)lParam == GetDlgItem(hwndDlg, FX_LINE_WIDTH)) {
            auto t = SendDlgItemMessage(hwndDlg, FX_LINE_WIDTH, TBM_GETPOS, 0, 0);
            functions.at(hwndDlg).line_width = t;
            InvalidateRect(hDlg, NULL, FALSE);
            return TRUE;
        }

    case WM_COMMAND: {
        switch(LOWORD(wParam))
        {
        char buf[100];
        case FX_LINE_WIDTH:
            if (HIWORD(wParam) == EN_CHANGE){
                GetDlgItemText(hwndDlg, FX_LINE_WIDTH, buf, 100);
                int t = atoi(buf);
                if (t > 0)
                    functions.at(hwndDlg).line_width = t;
                InvalidateRect(hDlg, NULL, FALSE);
            }
            break;
        case FX_A:
            if (HIWORD(wParam) == EN_CHANGE){
                GetDlgItemText(hwndDlg, FX_A, buf, 100);
                double t = atof(buf);
                functions.at(hwndDlg).A = t;
                InvalidateRect(hDlg, NULL, FALSE);
            }
            break;
        case FX_B:
            if (HIWORD(wParam) == EN_CHANGE){
                GetDlgItemText(hwndDlg, FX_B, buf, 100);
                double t = atof(buf);
                functions.at(hwndDlg).B = t;
                InvalidateRect(hDlg, NULL, FALSE);
            }
            break;
        case FX_C:
            if (HIWORD(wParam) == EN_CHANGE){
                GetDlgItemText(hwndDlg, FX_C, buf, 100);
                double t = atof(buf);
                functions.at(hwndDlg).C = t;
                InvalidateRect(hDlg, NULL, FALSE);
            }
            break;
        case FX_D:
            if (HIWORD(wParam) == EN_CHANGE){
                GetDlgItemText(hwndDlg, FX_D, buf, 100);
                double t = atof(buf);
                functions.at(hwndDlg).D = t;
                InvalidateRect(hDlg, NULL, FALSE);
            }
            break;
        case FX_LINE_COLOR: {
            SelectColor(hwndDlg, functions.at(hwndDlg).plot_col);
            InvalidateRect(hDlg, NULL, FALSE);
            break;
        }
        case FX_INC_COLOR: {
            SelectColor(hwndDlg, functions.at(hwndDlg).inc_col);
            InvalidateRect(hDlg, NULL, FALSE);
            break;
        }
        case FX_DEC_COLOR: {
            SelectColor(hwndDlg, functions.at(hwndDlg).dec_col);
            InvalidateRect(hDlg, NULL, FALSE);
            break;
        }
        case FX_INC_DEC: {
            functions.at(hwndDlg).inc_dec = IsDlgButtonChecked(hwndDlg, FX_INC_DEC);
            EnableWindow(GetDlgItem(hwndDlg, FX_INC_COLOR), functions.at(hwndDlg).inc_dec);
            EnableWindow(GetDlgItem(hwndDlg, FX_DEC_COLOR), functions.at(hwndDlg).inc_dec);
            InvalidateRect(hDlg, NULL, FALSE);
            break;
        }
        }
    }
    return TRUE;

    }
    return FALSE;
}

void MB_ABOUT()
{
    MessageBox(hDlg, "Программа построения и исследования графиков функций\n\nАвтор: Максим Терёхин, БГУ, ФПМИ, 2017 год.", "О программе Function Plotter", MB_ICONINFORMATION | MB_OK);
}

void RESET_FOCUS()
{
    centerX = width/2;
    centerY = height/2;
    InvalidateRect(hDlg, NULL, FALSE);
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        GetClientRect(hwndDlg, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;
        centerX = width/2;
        centerY = height/2;
        hDlg = hwndDlg;
    }
    return TRUE;

    case WM_CLOSE:
    {
        for (auto it = functions.begin(); it != functions.end(); it++)
            EndDialog(it->first, 0);
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_PAINT:
        OnPaint();
        break;

    case WM_SIZE:
        GetClientRect(hDlg, &rect);
        width = rect.right - rect.left;
        height = rect.bottom - rect.top;
        InvalidateRect(hwndDlg, NULL, FALSE);
        break;

    case WM_LBUTTONUP:{
        if (functions.empty()) break;
        double x = (LOWORD(lParam)-centerX)/(1.0*DP);
        double y = -(HIWORD(lParam)-centerY)/(1.0*DP);
        double min_dist = INFINITY, min_X, temp_d;
        for (double i = x-5; i <= x + 5; i += 1.0/DP)
        {
            temp_d = sqrt(pow(x-i, 2.0) + pow(y-functions.begin()->second.func(i), 2.0));
            if (temp_d < min_dist){
                min_dist = temp_d;
                min_X = i;
            }
        }
        clickedX = min_X;
        clickedY = functions.begin()->second.func(min_X);
        clicked = true;
        InvalidateRect(hwndDlg, NULL, FALSE);
        //printf("[%f] X = %f; Y = %f\n", min_dist, clickedX, clickedY);
        break;
    }

    case WM_RBUTTONDOWN:{
        drag = true;
        oldX = oldY = -1;
        break;
    }
    case WM_RBUTTONDBLCLK:
        clicked = false;
        InvalidateRect(hwndDlg, NULL, FALSE);
        break;
    case WM_RBUTTONUP:
        drag = false;
        InvalidateRect(hwndDlg, NULL, FALSE);
        break;
    case WM_MOUSEMOVE: {
        if (drag){
            if (oldX != -1){
                int deltaX = LOWORD(lParam)-oldX;
                int deltaY = HIWORD(lParam)-oldY;
                centerX += deltaX;
                centerY += deltaY;
            }
            oldX = LOWORD(lParam);
            oldY = HIWORD(lParam);
            InvalidateRect(hwndDlg, NULL, FALSE);
        }
        break;
    }
    case WM_MOUSEWHEEL: {
        DP += GET_WHEEL_DELTA_WPARAM(wParam)/120;
        if (DP < 1) DP = 1;
        InvalidateRect(hwndDlg, NULL, FALSE);
        break;
    }
    case WM_CTLCOLORDLG:
        return (INT_PTR)GetStockObject(WHITE_BRUSH);

    case WM_KEYDOWN: {
        switch (wParam){
        case 0x70:
            MB_ABOUT();
            break;
        case 0x20:
            RESET_FOCUS();
            break;
        }
    }

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case MENU_ABOUT: {
            MB_ABOUT();
            break;
        }
        case MENU_SAVE: {
            SavePlot();
            break;
        }

        case MENU_RESET_FOCUS: {
            RESET_FOCUS();
            break;
        }

        case MENU_F_X3:
        case MENU_F_ASIN:
        case MENU_F_ACOS:
        case MENU_F_ATG:
        case MENU_F_AX:
        case MENU_F_XA:
        case MENU_F_LN:
        case MENU_F_O1:
        case MENU_F_O2:
        case MENU_F_SIN:
        case MENU_F_COS:
        case MENU_F_TG:
            new_func_id = LOWORD(wParam);
            DialogBox(hInst, MAKEINTRESOURCE(DLG_FUNC), NULL, (DLGPROC)DlgFunc);
            break;



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
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
