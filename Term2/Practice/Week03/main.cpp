/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/

#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <cstring>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Week03");
PAINTSTRUCT _paintstruct;
RECT rect;
int centerX, centerY;
bool clicked = false;
double clickedX, clickedY;
bool drag = false;
int oldX, oldY;

int DP = 25;
const int ACC = 1;

auto axisPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
auto markPen = CreatePen(PS_SOLID, 1+(DP>5), RGB(0, 0, 0));
auto funcPen = CreatePen(PS_SOLID, 2+(DP>10), RGB(255, 0, 0));
auto dashPen = CreatePen(PS_DASH
                         , 1, RGB(0, 0, 0));


double FUNC(double x)
{
    double A = 0.5;
    double B = -2.0;
    double C = -10.0;
    return A*x*x + B*x + C;
    //return sin(x);
    //return tan(x);
}


int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);; //COLOR_WINDOW

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           szClassName,         /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           800,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


int numberSizeForTextOut(int x)
{
    if (abs(x) < 10)
        return 1+(x<0);
    else if (abs(x) < 100)
        return 2+(x<0);
    else if (abs(x) < 1000)
        return 3+(x<0);
    else return 4+(x<0);
}

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

double distance(double x0, double y0, double x1)
{
    return sqrt(pow(x0-x1, 2.0) + pow(y0-FUNC(x1), 2.0));
}

void OnPaint(HWND hwnd)
{
    auto hDC = BeginPaint(hwnd, &_paintstruct);
    GetClientRect(hwnd, &rect);
    auto width = rect.right - rect.left;
    auto height = rect.bottom - rect.top;
    //centerX = width/2;
    //centerY = height/2;


    /* DRAW AXES */
    SelectObject(hDC, axisPen);

    MoveToEx(hDC, centerX, 0, NULL);
    LineTo(hDC, centerX, height);

    MoveToEx(hDC, 0, centerY, NULL);
    LineTo(hDC, width, centerY);
    /* END DRAW AXES */
    /* DRAW MARKS */
    SelectObject(hDC, markPen);
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(0, 0, 255));
    char t[20];

    int maxXMarks = width/DP;
    SetTextAlign(hDC, TA_CENTER);
    for (int i = -maxXMarks; i <= maxXMarks; i++){
        MoveToEx(hDC, centerX + i*DP, centerY - 3, NULL);
        LineTo(hDC,   centerX + i*DP, centerY + 3);
        if (i % numberOnEveryNMark() == 0 && i != 0) {
            sprintf(t, "%d", i);
            TextOut(hDC,  centerX + i*DP, centerY + 6, _T(t), numberSizeForTextOut(i));
        }
    }

    int maxYMarks = height/DP;
    SetTextAlign(hDC, TA_RIGHT);
    for (int i = -maxYMarks; i <= maxYMarks; i++){
        MoveToEx(hDC, centerX - 3, centerY - i*DP, NULL);
        LineTo(hDC,   centerX + 3, centerY - i*DP);
        if (i % numberOnEveryNMark() == 0 && i != 0) {
            sprintf(t, "%d", i);
            TextOut(hDC,  centerX - 6, centerY - i*DP - 10, _T(t), numberSizeForTextOut(i));
        }
    }
    /* END DRAW MARKS */

    /* DRAW FUNC */
    SelectObject(hDC, funcPen);
    for (double i = -maxXMarks/2 - 1; i < maxXMarks/2 + 1; i+=(1.0/(ACC*DP))){
        MoveToEx(hDC, centerX + i*DP, centerY - FUNC(i)*DP, NULL);
        LineTo(hDC,   centerX + (i+(1.0/(ACC*DP)))*DP, centerY - FUNC(i+(1.0/(ACC*DP)))*DP);
    }
    /* END DRAW FUNC */
    /* DRAW CLICKED POINT */
    if (clicked) {
        SelectObject(hDC, dashPen);
        SetTextColor(hDC, RGB(0, 0, 0));
        SetTextAlign(hDC, TA_LEFT | TA_BOTTOM);

        MoveToEx(hDC, centerX + (clickedX*DP), centerY - (clickedY*DP), NULL);
        LineTo(hDC,   centerX + (clickedX*DP), centerY);
        MoveToEx(hDC, centerX + (clickedX*DP), centerY - (clickedY*DP), NULL);
        LineTo(hDC,   centerX, centerY - clickedY*DP);
        sprintf(t, "X = %.2f | Y = %.2f\0", clickedX, clickedY);
        TextOut(hDC, 0, height, _T(t), strlen(t));
    }
    /* END DRAW CLICKED POINT */
    ValidateRect(hwnd, NULL);
    EndPaint(hwnd, &_paintstruct);
}

/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_CREATE:
            GetClientRect(hwnd, &rect);
            centerX = (rect.right - rect.left)/2;
            centerY = (rect.bottom - rect.top)/2;
            break;
        case WM_PAINT:
            OnPaint(hwnd);
            break;
        case WM_SIZE:
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case WM_LBUTTONUP:{
            double x = (LOWORD(lParam)-centerX)/(1.0*DP);
            double y = -(HIWORD(lParam)-centerY)/(1.0*DP);
            double min_dist = 99999.9, min_X, temp_d;
            for (double i = x-5; i <= x + 5; i += (1.0/(ACC*DP)))
            {
                temp_d = distance(x, y, i);
                if (temp_d < min_dist){
                    min_dist = temp_d;
                    min_X = i;
                }
            }
            clickedX = min_X;
            clickedY = FUNC(min_X);
            clicked = true;
            InvalidateRect(hwnd, NULL, TRUE);
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
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case WM_RBUTTONUP:
            drag = false;
            InvalidateRect(hwnd, NULL, TRUE);
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
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        }
        case WM_MOUSEWHEEL:
            DP += GET_WHEEL_DELTA_WPARAM(wParam)/120;
            if (DP < 1) DP = 1;
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
