#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include <vector>
#include <iostream>

namespace Colors
{
	static COLORREF FromHex(int hex)
	{
		auto r = (hex & 0xFF0000) >> 16;
		auto g = (hex & 0x00FF00) >> 8;
		auto b = (hex & 0x0000FF) >> 0;
		return RGB(r, g, b);
	}

    static const COLORREF Red = FromHex(0xFF0000);
    static const COLORREF Orange = FromHex(0xFF8000);
    static const COLORREF Yellow = FromHex(0xFFFF00);
    static const COLORREF Green = FromHex(0x00FF00);
    static const COLORREF Blue = FromHex(0x0000FF);
    static const COLORREF LightBlue = FromHex(0x00FFFF);
    static const COLORREF Purple = FromHex(0x7F00FF);
    static const COLORREF Black = FromHex(0x000000);
	static const COLORREF White = FromHex(0xFFFFFF);
	static const COLORREF Gray = FromHex(0x808080);
}

struct LineEx {
    COLORREF Color;
    int Thickness;
    std::vector<POINT> Points;
    LineEx(): Points(0) {}
};

HINSTANCE hInst;
PAINTSTRUCT _paintstruct;
RECT rect;
auto blackPen = CreatePen(PS_SOLID, 2, Colors::Black);

int _thickness = 10;
COLORREF _primaryColor = Colors::Black;
COLORREF _secondaryColor = Colors::White;
std::vector<LineEx> _lines(1);
int _current = 0;
int _showLinesTo = _current;
int _possibleRedoTo = _current;
int _drawingInProcess = 0;
//#define _DEBUG

void debugOutput()
{
#ifdef _DEBUG
        std::cout << _current << ' ' << _showLinesTo << ' ' << _possibleRedoTo << ' ' << _lines.size() << '\n';
#endif // _DEBUG
}

void ProcessAccelerators(WPARAM keyCode)
{
    switch(keyCode){
    case 0x5A: //Z
        _showLinesTo--;
        if (_showLinesTo < 0) _showLinesTo = 0;
        debugOutput();
        break;
    case 0x59: //Y
        _showLinesTo++;
        if (_showLinesTo > _possibleRedoTo) _showLinesTo = _possibleRedoTo;
        debugOutput();
        break;
    case 0x30: //0
        _primaryColor = Colors::White;
        break;
    case 0x31: //1
        _primaryColor = Colors::Black;
        break;
    case 0x32: //2
        _primaryColor = Colors::Red;
        break;
    case 0x33: //3
        _primaryColor = Colors::Orange;
        break;
    case 0x34: //4
        _primaryColor = Colors::Yellow;
        break;
    case 0x35: //5
        _primaryColor = Colors::Green;
        break;
    case 0x36: //6
        _primaryColor = Colors::LightBlue;
        break;
    case 0x37: //7
        _primaryColor = Colors::Blue;
        break;
    case 0x38: //8
        _primaryColor = Colors::Purple;
        break;
    case 0x39: //9
        _primaryColor = Colors::Gray;
        break;
    }

}


RECT* GetSurroundingRect(int x, int y, int rad)
{
    rect.left = x - rad/2;
    rect.top = y - rad/2;
    rect.right = x + rad/2;
    rect.bottom = y + rad/2;
    return &rect;
}

RECT* GetThicknessRect(int w, int h)
{
    rect.left = 0;
    rect.top = h*9/10;
    rect.right = w/10;
    rect.bottom = h;
    return &rect;
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

void OnMouseMove(HWND hwndDlg, LPARAM lParam, WPARAM wParam)
{
    if (wParam & MK_LBUTTON || wParam & MK_RBUTTON) {
        _drawingInProcess = 1;
        if (_showLinesTo < _current){
            _lines.resize(_showLinesTo);
            _lines.push_back(LineEx());
            _possibleRedoTo = _current = _showLinesTo;
        }
        debugOutput();
        POINT cur_point;
        auto x = LOWORD(lParam);
        auto y = HIWORD(lParam);
        cur_point.x = x; cur_point.y = y;
        _lines[_current].Color = (wParam & MK_LBUTTON )?_primaryColor:_secondaryColor;
        _lines[_current].Thickness = _thickness;
        _lines[_current].Points.push_back(cur_point);
        InvalidateRect(hwndDlg, nullptr, FALSE);

    }
}

void OnPaint(HWND hwndDlg)
{
    auto hDeviceContext = BeginPaint(hwndDlg, &_paintstruct);
    GetClientRect(hwndDlg, &rect);
    auto width = rect.right - rect.left;
    auto height = rect.bottom - rect.top;
    for (int i = 0; i < _showLinesTo + _drawingInProcess; i++)
    {
        auto pen = SelectObject(hDeviceContext, CreatePen(PS_SOLID, _lines[i].Thickness, _lines[i].Color));
        int jsize = _lines[i].Points.size();
        for (int j = 0; j < jsize - 1 && jsize > 1; j++) {
            MoveToEx(hDeviceContext,_lines[i].Points[j].x , _lines[i].Points[j].y, nullptr);
            LineTo(hDeviceContext, _lines[i].Points[j+1].x, _lines[i].Points[j+1].y);

        }
        DeleteObject(pen);
    }

    SelectObject(hDeviceContext, blackPen);
    auto primaryBrush =  CreateSolidBrush(_primaryColor);
    auto secondaryBrush =  CreateSolidBrush(_secondaryColor);
    auto font = CreateFont("Consolas", width/10, FW_BOLD);

    SelectObject(hDeviceContext, primaryBrush);
    Rectangle(hDeviceContext, 0, height*8/10, width/10, height*9/10);

    SelectObject(hDeviceContext, secondaryBrush);
    Rectangle(hDeviceContext, width/10, height*9/10,width*2/10,height);

    SelectObject(hDeviceContext, font);
    //SetBkMode(hDeviceContext, TRANSPARENT);
    char text[3];
    sprintf(text, "%d", _thickness);
    DrawText(hDeviceContext, text, -1, GetThicknessRect(width, height), DT_SINGLELINE | DT_CENTER | DT_VCENTER);


    DeleteObject(primaryBrush);
    DeleteObject(secondaryBrush);
    DeleteObject(font);

    ValidateRect(hwndDlg, nullptr);
    EndPaint(hwndDlg, &_paintstruct);
}


BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
        #ifdef _DEBUG
        for (int i = 0; i < _lines.size(); i++){
            for (int j = 0; j < _lines[i].Points.size(); j++)
                std::cout << "[" << _lines[i].Points[j].x << ", " << _lines[i].Points[j].y << "], ";
            std::cout << std::endl << std::endl;
        }
        #endif // _DEBUG
    }
    return TRUE;

    case WM_RBUTTONUP:
    case WM_LBUTTONUP:
        _current++;
        _possibleRedoTo = _showLinesTo = _current;
        _lines.push_back(LineEx());
        _drawingInProcess = 0;
        debugOutput();
        InvalidateRect(hwndDlg, nullptr, FALSE);
    return TRUE;

    case WM_MOUSEMOVE:
        OnMouseMove(hwndDlg, lParam, wParam);
    return TRUE;

     case WM_PAINT:
        OnPaint(hwndDlg);
    return TRUE;

    case WM_KEYDOWN:
    {
        bool shiftState = ((GetKeyState(VK_LSHIFT) & 0x8000) || (GetKeyState(VK_RSHIFT) & 0x8000));
        bool ctrlState = ((GetKeyState(VK_LCONTROL) & 0x8000) || (GetKeyState(VK_RCONTROL) & 0x8000));
        switch (wParam){
        case 0xBB: // + key
            _thickness += (shiftState)?5:1;
            break;
        case 0xBD: // - key
            _thickness -= (shiftState)?5:1;
            break;
        case 0xBF: // / key
            std::swap(_primaryColor, _secondaryColor);
            break;
        case 0x70: MB_ABOUT;
        case VK_DELETE:
            _lines.clear();
            _lines.resize(1);
            _showLinesTo = _possibleRedoTo = _current = 0;
            break;
        default:
            if (ctrlState) ProcessAccelerators(wParam);
        }
        if (_thickness < 1)  _thickness = 1;
        if (_thickness > 19) _thickness = 19;
        InvalidateRect(hwndDlg, nullptr, TRUE);
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
