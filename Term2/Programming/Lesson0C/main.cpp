#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include <vector>
#include <cmath>
#include <string>

#define M_PI 3.14159
HINSTANCE hInst;

using namespace std;


PAINTSTRUCT _paintstruct;
HWND        hDlg;
HINSTANCE hInstance;
HBRUSH PointBrush =  CreateSolidBrush(RGB(255, 127, 0));

int prev_timer = 0;
int OffsetX = 0;
int OffsetY = 0;

static int ticks = 0;
double cur_angle = 0.0;
int cx, cy;

POINT point;
HWND UP, DOWN, LEFT, RIGHT;

const int   ID_Up=1002,
            ID_Down=1003,
            ID_Left=1004,
            ID_Right = 1005,
            SCALE = 100,
            AXIS_LEN= 1000,
            F_RAD = 500,
            P_RAD = 30,
            AXIS_MOVING = 50;

const double F_K = 4.0/3.0,
             F_PERIOD = 6*M_PI;


POINT Figure(double angle)
{
    POINT p;
    p.x = F_RAD*(cos(F_K*angle))*cos(angle) + OffsetX;
    p.y = F_RAD*(cos(F_K*angle))*sin(angle) + OffsetY;
    return p;
}

void SetImage(const char* caption, HWND& control)
{
    auto bmp = (HBITMAP)LoadImage(nullptr, caption, IMAGE_BITMAP, NULL, NULL, LR_LOADFROMFILE);
    SendMessage(control, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)bmp);
}

HWND CreateControl(HWND &parent, const char* className, long style, int x, int y, int width, int heigth, int id)
{
    return CreateWindow(
               className, "",
               WS_CHILD | WS_VISIBLE | style,
               x, y,
               width, heigth,
               parent,
               (HMENU)id,
               hInst,
               nullptr);
}

void CreateButtons(HWND hwndDlg)
{
    UP = CreateControl(hwndDlg,WC_BUTTON, BS_BITMAP, 650, 10, 50, 50, ID_Up);
    RIGHT = CreateControl(hwndDlg, WC_BUTTON, BS_BITMAP, 700, 60, 50, 50, ID_Right);
    DOWN = CreateControl(hwndDlg, WC_BUTTON, BS_BITMAP, 650, 110, 50, 50, ID_Down);
    LEFT = CreateControl(hwndDlg, WC_BUTTON, BS_BITMAP, 600, 60, 50, 50, ID_Left);

    SetImage("up.bmp", UP);
    SetImage("right.bmp", RIGHT);
    SetImage("down.bmp", DOWN);
    SetImage("left.bmp", LEFT);
}


void CALLBACK TimerProc(HWND hwndDlg, UINT _, UINT_PTR __, DWORD ms)
{
    auto delta = ms - prev_timer;
    prev_timer = ms;

    cur_angle -= 0.001 * delta;
    point = Figure(cur_angle);
    if (cur_angle < -F_PERIOD) cur_angle = 0.0;

    InvalidateRect(hwndDlg, NULL, FALSE);
}

void OnPaint(HWND &hwndDlg)
{
    HDC hRealDC;
    RECT rect;
    hRealDC = BeginPaint(hwndDlg, &_paintstruct);
    GetClientRect(hwndDlg, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    //Double buffering
    auto hdc = CreateCompatibleDC(hRealDC);
    auto CompBitmap = CreateCompatibleBitmap(hRealDC, width, height);
    auto OldBitmap = (HBITMAP)SelectObject(hdc, CompBitmap);
    PatBlt(hdc, 0, 0, width, height, WHITENESS);

    //Coord transformation
    SetMapMode(hdc, MM_ANISOTROPIC);
    SetWindowExtEx(hdc, 1000, 1000, nullptr);
    SetViewportExtEx(hdc, (rect.right - rect.left) / 2, -(rect.bottom - rect.top) / 2, 0);
    SetViewportOrgEx(hdc, (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2, 0);

    //Axises drawing
    MoveToEx(hdc, -AXIS_LEN, 0, 0);
    LineTo(hdc, AXIS_LEN, 0);
    MoveToEx(hdc, 0, AXIS_LEN, 0);
    LineTo(hdc, 0, -AXIS_LEN);

    //Numbers drawing
    SetTextAlign(hdc, TA_CENTER);
    for (int i = 0, a = -10; i <= 20; i++, a++)
    {
        MoveToEx(hdc, -AXIS_LEN + SCALE*i, -10, 0);
        LineTo(hdc, -AXIS_LEN + SCALE*i, 10);
        MoveToEx(hdc, -10, -AXIS_LEN + SCALE*i, 0);
        LineTo(hdc, 10, -AXIS_LEN + SCALE*i);
        if (a != 0)
        {
            TextOut(hdc,-AXIS_LEN + SCALE*i, -20, (LPCSTR)to_string(a).c_str(), to_string(a).size());
            TextOut(hdc, -40, 25-AXIS_LEN + SCALE*i, (LPCSTR)to_string(a).c_str(), to_string(a).size());
        }
    }

    //Figure drawing
    MoveToEx(hdc, F_RAD+OffsetX, OffsetY, 0);
    for (double angle = 0.0; angle < F_PERIOD; angle += 0.05)
    {
        POINT p = Figure(angle);
        LineTo(hdc, p.x, p.y);
    }

    //Point drawing
    SelectObject(hdc, PointBrush);
    Ellipse(hdc, point.x - P_RAD, point.y - P_RAD, point.x + P_RAD, point.y + P_RAD);

    //Coord transformation
    SetMapMode(hdc, MM_TEXT);
    SetWindowExtEx(hdc, (rect.right - rect.left) / 2, (rect.bottom - rect.top) / 2, nullptr);
    SetViewportExtEx(hdc, 0, 0, 0);
    SetViewportOrgEx(hdc, 0, 0, 0);

    //Double buffering
    BitBlt(hRealDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
    DeleteObject(CompBitmap);
    DeleteDC(hdc);
    EndPaint(hwndDlg, &_paintstruct);
}

void OnCommand(WPARAM wParam, HINSTANCE hInstance, HWND hwndDlg)
{
    switch (LOWORD(wParam))
    {
    case ID_Up:
        OffsetY += AXIS_MOVING;
        break;

    case ID_Down:
        OffsetY -= AXIS_MOVING;
        break;

    case ID_Right:
        OffsetX += AXIS_MOVING;
        break;

    case ID_Left:
        OffsetX -= AXIS_MOVING;
        break;
    }
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
        hDlg = hwndDlg;
        SetTimer(hwndDlg, 1, 10, TimerProc);
        CreateButtons(hwndDlg);
        return TRUE;

    case WM_CLOSE:
        DestroyWindow(hwndDlg);
        return TRUE;

    case WM_COMMAND:
        OnCommand(wParam, hInstance, hwndDlg);
        break;

    case WM_PAINT:
        OnPaint(hwndDlg);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
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
