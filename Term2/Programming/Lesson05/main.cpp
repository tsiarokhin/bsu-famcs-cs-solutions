#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

#define PLAIN_RECT(rect) rect.left,rect.top,rect.right,rect.bottom


namespace Colors
{
	static COLORREF FromHex(int hex)
	{
		auto r = (hex & 0xFF0000) >> 16;
		auto g = (hex & 0x00FF00) >> 8;
		auto b = (hex & 0x0000FF) >> 0;
		return RGB(r, g, b);
	}

    static const COLORREF lightRed = FromHex(0xFF0000);
    static const COLORREF lightYellow = FromHex(0xFFFF00);
    static const COLORREF lightGreen = FromHex(0x00FF00);
    static const COLORREF darkRed = FromHex(0x800000);
    static const COLORREF darkYellow = FromHex(0x808000);
    static const COLORREF darkGreen = FromHex(0x008000);

	static const COLORREF Gold = FromHex(0xFDD017);
	static const COLORREF Blue = FromHex(0x0000FF);
    static const COLORREF SteelBlue2 = FromHex(0x5CACEE);
	static const COLORREF Black = FromHex(0x000000);
	static const COLORREF White = FromHex(0xFFFFFF);
}



HINSTANCE hInst;

const int MinDialogWidth = 400;
const int MinDialogHeight = 600;
const int Timer1ID = 1;

const int RED_SCHEDULE[] =    {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0};
const int YELLOW_SCHEDULE[] = {0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1};
const int GREEN_SCHEDULE[] =  {0,0,0,0,0,0,0,0,1,1,1,0,1,0,1,0,0};
const int TIME_SCHEDULE[] =   {8,7,6,5,4,3,2,1,9,8,7,6,5,4,3,2,1};

int timerState = 0;

PAINTSTRUCT _paintstruct;
RECT rect;

namespace Pens {
    auto line = CreatePen(PS_DASHDOTDOT, 1, Colors::SteelBlue2);

    auto dark = CreatePen(PS_SOLID, 2, Colors::Black);
    auto light = CreatePen(PS_SOLID, 4, Colors::Gold);
}

namespace Brushes {
    auto lightRed = CreateSolidBrush(Colors::lightRed);
    auto lightGreen = CreateSolidBrush(Colors::lightGreen);
    auto lightYellow = CreateSolidBrush(Colors::lightYellow);
    auto darkRed = CreateSolidBrush(Colors::darkRed);
    auto darkGreen = CreateSolidBrush(Colors::darkGreen);
    auto darkYellow = CreateSolidBrush(Colors::darkYellow);
}

RECT CreateRect(int left, int top, int rigth, int bottom)
{
    auto rect = RECT();
    rect.left = left;
    rect.top = top;
    rect.right = rigth;
    rect.bottom = bottom;
    return rect;
}

RECT CalculateShapeRect(int xCenter, int yCenter, double width, double heigth)
{
    auto x = xCenter - (int)width / 2;
    auto y = yCenter - (int)heigth / 2;
    return CreateRect(x, y, x + (int)width, y + (int)heigth);
}

HFONT CreateFont(const char* name, int size, int weight)
{
    auto lf = LOGFONT{};
    strcpy(lf.lfFaceName, name);
    lf.lfHeight = size;
    lf.lfWeight = weight;
    lf.lfCharSet = DEFAULT_CHARSET;
    return CreateFontIndirect(&lf);
}

void OnPaint(HWND _hDialog)
{
    auto hDeviceContext = BeginPaint(_hDialog, &_paintstruct);

    GetClientRect(_hDialog, &rect);
    auto width = rect.right - rect.left;
    auto height = rect.bottom - rect.top;
    auto unit = min(width, height) / 3;

    /* BEGIN LINES */
    auto hOldPen = SelectObject(hDeviceContext, Pens::line);

    //Vertical line
    MoveToEx(hDeviceContext, width / 2, 0, nullptr);
    LineTo(hDeviceContext, width / 2, height);

    //5 Horizontal Lines
    MoveToEx(hDeviceContext, 0, height / 6, nullptr);
    LineTo(hDeviceContext, width, height / 6);
    MoveToEx(hDeviceContext, 0, 2*height / 6, nullptr);
    LineTo(hDeviceContext, width, 2*height / 6);
    MoveToEx(hDeviceContext, 0, 3*height / 6, nullptr);
    LineTo(hDeviceContext, width, 3*height / 6);
    MoveToEx(hDeviceContext, 0, 4*height / 6, nullptr);
    LineTo(hDeviceContext, width, 4*height / 6);
    MoveToEx(hDeviceContext, 0, 5*height / 6, nullptr);
    LineTo(hDeviceContext, width, 5*height / 6);
    /* END LINES */

    /* BEGIN CIRCLES */
    SelectObject(hDeviceContext, (RED_SCHEDULE[timerState]) ? Brushes::lightRed : Brushes::darkRed);
    SelectObject(hDeviceContext, (RED_SCHEDULE[timerState]) ? Pens::light : Pens::dark );
    Ellipse(hDeviceContext, PLAIN_RECT(CalculateShapeRect(width / 2, height / 6, unit, unit)));

    SelectObject(hDeviceContext, (YELLOW_SCHEDULE[timerState]) ? Brushes::lightYellow : Brushes::darkYellow);
    SelectObject(hDeviceContext, (YELLOW_SCHEDULE[timerState]) ? Pens::light : Pens::dark );
    Ellipse(hDeviceContext, PLAIN_RECT(CalculateShapeRect(width / 2, 3*height / 6, unit, unit)));

    SelectObject(hDeviceContext, (GREEN_SCHEDULE[timerState]) ? Brushes::lightGreen : Brushes::darkGreen);
    SelectObject(hDeviceContext, (GREEN_SCHEDULE[timerState]) ? Pens::light : Pens::dark );
    Ellipse(hDeviceContext, PLAIN_RECT(CalculateShapeRect(width / 2, 5*height / 6, unit, unit)));
    /* END CIRCLES */

    /* BEGIN TIME */
    SelectObject(hDeviceContext, CreateFont("Consolas", 0.7*unit, FW_BOLD));
    SetTextColor(hDeviceContext, Colors::Blue);
    SetBkMode(hDeviceContext, TRANSPARENT);
    auto textRectangle = CalculateShapeRect(width / 2, 3*height / 6, unit, unit);
    char text[10];
    sprintf(text, "%d", TIME_SCHEDULE[timerState]);
    DrawText(hDeviceContext, text, -1, &textRectangle, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
    /* END TIME */
}


BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        SetWindowPos(hwndDlg, nullptr, NULL, NULL, MinDialogWidth, MinDialogHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
        SetTimer(hwndDlg, Timer1ID, 1000, nullptr);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_TIMER:
    {
        auto timerID = (int)wParam;
        if (timerID == Timer1ID)
        {
            ++timerState;
            if (timerState > 16)
                timerState = 0;
            InvalidateRect(hwndDlg, nullptr, TRUE);
        }
        return TRUE;
    }

    case WM_PAINT:
        OnPaint(hwndDlg);
        return TRUE;

    case WM_GETMINMAXINFO:
    {
        auto sizeInfo = (LPMINMAXINFO)lParam;
        sizeInfo->ptMinTrackSize.x = MinDialogWidth;
        sizeInfo->ptMinTrackSize.y = MinDialogHeight;
        return TRUE;
    }

    case WM_SIZE:
        InvalidateRect(hwndDlg, nullptr, TRUE);
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
