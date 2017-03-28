#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <string>
#include "resource.h"

HINSTANCE hInst;

RECT temp_rect;
RECT rectField1;
RECT rectField2;

const int OBJECT_COUNT = 4;
const bool ONE_OBJECT_DRAG = true;
RECT rectObject[OBJECT_COUNT];
bool dragObject[OBJECT_COUNT];
int field1Count = 4;
int field2Count = 0;

int oldX = 0;
int oldY = 0;

auto fieldBrush = CreateSolidBrush(RGB(255, 255, 255));
auto objectBrush = CreateSolidBrush(RGB(0, 255, 0));
auto selectedObjectBrush = CreateSolidBrush(RGB(255, 255, 0));
auto draggedObjectBrush = CreateSolidBrush(RGB(255, 0, 0));

void DrawRectangle(const HDC& deviceContext, const RECT& rect)
{
    Rectangle(deviceContext, rect.left, rect.top, rect.right, rect.bottom);
}

void SetRectFields(RECT* rect, int x, int y, int width, int height)
{
    SetRect(rect, x, y, x + width, y + height);
}

void updateDragState(HWND hwndDlg, bool newState)
{
    POINT mousePosition;
    GetCursorPos(&mousePosition);
    ScreenToClient(hwndDlg, &mousePosition);
    for (int i = OBJECT_COUNT-1; i >= 0; i--){
        auto isHoverRect = PtInRect(&rectObject[i], mousePosition);
        if (isHoverRect){
            dragObject[i] = newState;
            if (newState && ONE_OBJECT_DRAG) break;
        }
    }
}

bool someObjectBeingDragged()
{
    for (int i = 0; i < OBJECT_COUNT; i++)
        if (dragObject[i]){
            SetCursor(LoadCursor(NULL, IDC_SIZEALL));
            return true;
        }
    SetCursor(LoadCursor(NULL, IDC_ARROW));
    return false;
}

bool rectEqual(const RECT& r1, const RECT& r2)
{
    return (r1.bottom == r2.bottom &&
            r1.left == r2.left &&
            r1.right == r2.right &&
            r1.top == r2.top);
}

void updateObjectCountLabel(HWND hwndDlg)
{
    field1Count = 0;
    field2Count = 0;
    for (int i = 0; i < OBJECT_COUNT; i++) {
		IntersectRect(&temp_rect, &rectField1, &rectObject[i]);
		if (rectEqual(temp_rect, rectObject[i]))
            field1Count++;
		IntersectRect(&temp_rect, &rectField2, &rectObject[i]);
		if (rectEqual(temp_rect, rectObject[i]))
            field2Count++;
    }
}

void InitDialog(HWND hwndDlg)
{
    auto top = 50;
    auto left = 50;
    auto rectSize = 350;
    auto objectSize = 100;
    auto offset = 50;

    SetRectFields(&rectField1, left, top, rectSize, rectSize);
    SetRectFields(&rectField2, left + rectSize + offset, top, rectSize, rectSize);

    SetRectFields(&rectObject[0], left+offset, top+offset, objectSize, objectSize);
    SetRectFields(&rectObject[1], left+objectSize+2*offset, top+offset, objectSize, objectSize);
    SetRectFields(&rectObject[2], left+offset, top+objectSize+2*offset, objectSize, objectSize);
    SetRectFields(&rectObject[3], left+objectSize+2*offset, top+objectSize+2*offset, objectSize, objectSize);
    for (int i = 0; i < OBJECT_COUNT; i++)
        dragObject[i] = false;
}

void DrawFields(HDC& hdc)
{
    SelectObject(hdc, fieldBrush);
    DrawRectangle(hdc, rectField1);
    DrawRectangle(hdc, rectField2);
}

void DrawObjects(HDC& hdc, HWND hwndDlg)
{
    POINT mousePosition;
    GetCursorPos(&mousePosition);
    ScreenToClient(hwndDlg, &mousePosition);

    for (int i = 0; i < OBJECT_COUNT; i++){
        auto isHoverRect = PtInRect(&rectObject[i], mousePosition);
        SelectObject(hdc, objectBrush);
        if (isHoverRect)
            SelectObject(hdc, selectedObjectBrush);
        if (dragObject[i])
            SelectObject(hdc, draggedObjectBrush);
        DrawRectangle(hdc, rectObject[i]);
    }
}

void DrawFieldCounters(HDC& hdc)
{
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc,  215, 20, std::to_string(field1Count).c_str(), std::to_string(field1Count).size());
    TextOut(hdc,  615, 20, std::to_string(field2Count).c_str(), std::to_string(field2Count).size());
}

void OnPaint(HWND hwndDlg)
{
    PAINTSTRUCT ps;
    GetClientRect(hwndDlg, &temp_rect);
    int width = temp_rect.right - temp_rect.left;
    int height = temp_rect.bottom - temp_rect.top;
    auto hRealDC = BeginPaint(hwndDlg, &ps);
    // Double-buffering
    auto hdc = CreateCompatibleDC(hRealDC);
    auto hScreen = CreateCompatibleBitmap(hRealDC, width, height);
    auto oldBmp = (HBITMAP)SelectObject(hdc, hScreen);
    PatBlt(hdc, 0, 0, width, height, WHITENESS);
    // Double-buffering

    DrawFields(hdc);
    DrawObjects(hdc, hwndDlg);
    DrawFieldCounters(hdc);

    // Double-buffering
    BitBlt( hRealDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
    SelectObject(hdc, oldBmp );
    DeleteObject(hScreen);
    DeleteDC(hdc);
    // Double-buffering
    EndPaint(hwndDlg, &ps);
}

void ClipCursorToClientRect(HWND hwndDlg)
{
    RECT client_rect;
    GetClientRect(hwndDlg, &client_rect);

    POINT positionLeftTop = { client_rect.left, client_rect.top };
    ClientToScreen(hwndDlg, &positionLeftTop);
    POINT positionRightBottom = { client_rect.right, client_rect.bottom };
    ClientToScreen(hwndDlg, &positionRightBottom);

    RECT rectCapture;
    SetRect(&rectCapture, positionLeftTop.x, positionLeftTop.y, positionRightBottom.x, positionRightBottom.y);
    ClipCursor(&rectCapture);
}

void MoveObject(RECT& rect, int deltaX, int deltaY)
{
    rect.left += deltaX;
    rect.right += deltaX;
    rect.top += deltaY;
    rect.bottom += deltaY;
}

void OnMouseMove(HWND hwndDlg, int X, int Y)
{
    int deltaX = X-oldX;
    int deltaY = Y-oldY;

    for (int i = 0; i < OBJECT_COUNT; i++)
        if (dragObject[i])
            MoveObject(rectObject[i], deltaX, deltaY);

    oldX = X;
    oldY = Y;

    if (someObjectBeingDragged())
        ClipCursorToClientRect(hwndDlg);
    else
        ClipCursor(nullptr);
    updateObjectCountLabel(hwndDlg);
    InvalidateRect(hwndDlg, nullptr, false);
}


BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
        InitDialog(hwndDlg);
        return TRUE;

    case WM_CLOSE:
        EndDialog(hwndDlg, 0);
        return TRUE;
    case WM_PAINT:
        OnPaint(hwndDlg);
        break;
    case WM_MOUSEMOVE:
        OnMouseMove(hwndDlg, LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_LBUTTONDOWN:{
        oldX = LOWORD(lParam);
        oldY = HIWORD(lParam);
        updateDragState(hwndDlg, true);
        InvalidateRect(hwndDlg, nullptr, false);
        break;
    }
    case WM_LBUTTONUP:{
        updateDragState(hwndDlg, false);
        InvalidateRect(hwndDlg, nullptr, false);
        break;
    }

    }
    return FALSE;
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
