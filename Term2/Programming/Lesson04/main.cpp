#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include <cstdlib>
#include <cstring>

namespace Resources
{
	const int SliderID = 1002;
	const int LabelID = 1003;
	const int ImageID = 1004;
}

HINSTANCE hInst;
HWND hDialog = nullptr;
HWND slider = nullptr;
HWND label = nullptr;
HWND image = nullptr;
int value = 0;
const int MinValue = 0;
const int MaxValue = 10;

void ChangeImageTo(const char* name)
{
    auto bmp = (HBITMAP)LoadImage(nullptr, name, IMAGE_BITMAP, NULL, NULL, LR_LOADFROMFILE);
    SendMessage(image, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
}

void SetValue(int val)
{
    value = val;
    SendMessage(slider, TBM_SETPOS, TRUE, value);
    char temp_s[10];
    sprintf(temp_s,"%d",value);
    SetWindowText(label, temp_s);
    if (value < 4)
        ChangeImageTo("Sad.bmp");
    else if (value > 7)
        ChangeImageTo("Happy.bmp");
    else
        ChangeImageTo("Neutral.bmp");
}

BOOL OnScroll(WPARAM wParam, LPARAM lParam)
{
    auto hControl = (HWND)lParam;
    if (hControl != slider) return FALSE;
    auto value = SendMessage(slider, TBM_GETPOS, NULL, NULL);
    SetValue(value);
    return TRUE;
}

HWND CreateControl(const char* className, long style, int x, int y, int width, int heigth, int id)
{
    return CreateWindow(
        className, "",
        WS_CHILD | WS_VISIBLE | style,
        x, y,
        width, heigth,
        hDialog,
        (HMENU)id,
        hInst,
        nullptr);
}

void CreateControls()
{

    SetWindowPos(hDialog, nullptr, NULL, NULL, 300, 200, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
	SetWindowText(hDialog, "Lesson 04");

    slider = CreateControl(TRACKBAR_CLASS, WS_TABSTOP | TBS_AUTOTICKS | TBS_HORZ, 20, 60, 150, 32, Resources::SliderID);
    SendMessage(slider, TBM_SETRANGE, TRUE, MAKELONG(MinValue, MaxValue));

    label = CreateControl("static", NULL, 20, 100, 150, 32, Resources::LabelID);

    image = CreateControl("STATIC", SS_BITMAP, 200, 20, NULL, NULL, Resources::ImageID);
    SetValue(0);
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        hDialog = hwndDlg;
        CreateControls();
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        //switch(LOWORD(wParam))
        //{
        //}
    }
    return TRUE;

    case WM_HSCROLL:
    case WM_VSCROLL:
        return (INT_PTR)OnScroll(wParam, lParam);

    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
