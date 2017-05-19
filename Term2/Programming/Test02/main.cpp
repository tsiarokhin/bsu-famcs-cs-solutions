#undef UNICODE
#include <iostream>
#include <algorithm>
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "Particle.h"
#include <vector>
#include <string>
#include <cmath>

const int DX[] = {1,0, 0,-1};
const int DY[] = {0,1,-1, 0};

HINSTANCE hInst;
HWND mainDlgHWND;
const int timerID = 1;
int timerState = 0;
int lastCreationTime = 0;

bool SIMULATION_RUNNING;
int DRAW_LAST_K_TRACES = 10;
int TIMER_T = 500;
int LINES_N = 10;
int LINES_M = 10;
int PART_RAD = 10; // particle radius in px
auto linePen = CreatePen(PS_DASH, 1, RGB(0,0, 255));
auto particlePen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
vector <Particle> Particles;
Particle fake_part(-1,-1, RGB(255, 255, 0));

void CalculateClientCoord(int& cx, int& cy, int x, int y, int cwidth = -1, int cheight = -1)
// Converts x, y of particle to on-screen coordinates cx, cy
{
    if (cwidth == -1) {
        RECT temp_rect;
        GetClientRect(mainDlgHWND, &temp_rect);
        cwidth = temp_rect.right - temp_rect.left;
        cheight = temp_rect.bottom - temp_rect.top;
    }
    int nodeW = cwidth/(LINES_N+1);
    int nodeH = cheight/(LINES_M+1);
    cx = x*nodeW;
    cy = y*nodeH;
}

void CalculateNearestGridPoint(int& x, int& y, int cx, int cy, int cwidth = -1, int cheight = -1)
// Converts x, y of particle to on-screen coordinates cx, cy
{
    if (cwidth == -1) {
        RECT temp_rect;
        GetClientRect(mainDlgHWND, &temp_rect);
        cwidth = temp_rect.right - temp_rect.left;
        cheight = temp_rect.bottom - temp_rect.top;
    }
    int nodeW = cwidth/(LINES_N+1);
    int nodeH = cheight/(LINES_M+1);
    x = (cx+PART_RAD)/nodeW;
    y = (cy+PART_RAD)/nodeH;
}

bool isGridOccupied(int tx, int ty)
{
    return (Particles.end() != std::find_if(Particles.begin(), Particles.end(),
            [&tx, &ty](Particle& part){
                return (part.x == tx && part.y == ty);
            }));
}

bool MoveOrDestroyPartcle(Particle& particle) // ret true to destroy
{
    if (particle.x <= 0 || particle.y <= 0 || particle.x >= LINES_N+1 || particle.y >= LINES_M+1)
        return true;
    int DIRECTIONS[] = {0, 1, 2, 3};
    std::random_shuffle(DIRECTIONS, DIRECTIONS+4);
    for (int i = 0; i < 4; i++){
        int newx = particle.x + DX[DIRECTIONS[i]];
        int newy = particle.y + DY[DIRECTIONS[i]];
        if (newx < 0 || newx > LINES_N+1 || newy < 0 || newy > LINES_M+1) continue;

        if(isGridOccupied(newx, newy)) continue;

        particle.Move(newx, newy);
        break;
    }
    return false;
}

void CALLBACK OnTimer(HWND hWindow, UINT message, UINT_PTR idEvent, DWORD time)
{
    if (idEvent != timerID || !SIMULATION_RUNNING) return;
    timerState++;
    for (auto it = Particles.begin(); it != Particles.end(); )
        if (MoveOrDestroyPartcle(*it)){
            it = Particles.erase(it);
        }
        else it++;
    if (Particles.size() == 0) {
        SIMULATION_RUNNING = false;
        MessageBox(hWindow, "Simulation Complete", "Simulation", MB_OK | MB_ICONINFORMATION);
    }
    InvalidateRect(hWindow, nullptr, FALSE);
}

BOOL CALLBACK DlgSettings(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        SetDlgItemInt(hwndDlg, IDS_N, LINES_N, FALSE);
        SetDlgItemInt(hwndDlg, IDS_M, LINES_M, FALSE);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
        SIMULATION_RUNNING = true;

    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDS_CANCEL:{
            EndDialog(hwndDlg, 0);
            SIMULATION_RUNNING = true;
            break;
        }
        case IDS_OK:{
            /// TODO: check boundaries
            char buf[20];
            int temp_n, temp_m;

            GetDlgItemText(hwndDlg, IDS_N, buf, sizeof(buf));
            temp_n = atoi(buf);

            GetDlgItemText(hwndDlg, IDS_M, buf, sizeof(buf));
            temp_m = atoi(buf);

            if (temp_n > 2 && temp_m > 2){
                LINES_N = temp_n;
                LINES_M = temp_m;
                InvalidateRect(mainDlgHWND, nullptr, FALSE);
                EndDialog(hwndDlg, 0);
                SIMULATION_RUNNING = true;
            } else {
                MessageBox(hwndDlg, "Invalid variables\nN and M must be greater than 2", "Error", MB_OK | MB_ICONERROR);
            }
            break;
        }

        }
    }
    return TRUE;
    }
    return FALSE;
}

void DrawTrace(HDC hdc, Particle& particle)
{
    int cx, cy;
    CalculateClientCoord(cx, cy, particle.x, particle.y);
    MoveToEx(hdc, cx, cy, NULL);
    int count = DRAW_LAST_K_TRACES;
    for (auto it = particle.trace.rbegin(); it != particle.trace.rend() && count > 0; it++){
        CalculateClientCoord(cx, cy, it->first, it->second);
        int col = (DRAW_LAST_K_TRACES-count)*(255/DRAW_LAST_K_TRACES);
        auto pen = CreatePen(PS_SOLID, 3, RGB(col,col,col));
        SelectObject(hdc, pen);
        LineTo(hdc, cx, cy);
        DeleteObject(pen);
        count--;
    }

}

void DrawParticle(HDC hdc, Particle& particle)
{
    SelectObject(hdc, particlePen);
    auto particleBrush = CreateSolidBrush(particle.color);
    SelectObject(hdc, particleBrush);

    int cx, cy;
    CalculateClientCoord(cx, cy, particle.x, particle.y);
    Ellipse(hdc, cx-PART_RAD, cy-PART_RAD, cx+PART_RAD, cy+PART_RAD);

    DeleteObject(particleBrush);
}

void DrawAllParticles(HDC hdc)
{
    for (auto it = Particles.begin(); it != Particles.end(); it++)
        DrawTrace(hdc, *it);
    for (auto it = Particles.begin(); it != Particles.end(); it++)
        DrawParticle(hdc, *it);
}

void DrawGrid(HDC hdc, int width, int height, int nodeW, int nodeH)
{
    SelectObject(hdc, linePen);
    for (int i = 1; i <= LINES_N; i++){
        MoveToEx(hdc, nodeW*i, 0, NULL);
        LineTo(hdc, nodeW*i, height);
    }
    for (int i = 1; i <= LINES_M; i++){
        MoveToEx(hdc, 0, nodeH*i, NULL);
        LineTo(hdc, width, nodeH*i);
    }
}

void OnPaint(HWND hwndDlg)
{
    PAINTSTRUCT ps;
    RECT temp_rect;
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
    int nodeW = width/(LINES_N+1);
    int nodeH = height/(LINES_M+1);

    DrawGrid(hdc, width, height, nodeW, nodeH);

    DrawParticle(hdc, fake_part);

    DrawAllParticles(hdc);

    TextOut(hdc, 0, 0, std::to_string(timerState).c_str(), std::to_string(timerState).size());
    // Double-buffering
    BitBlt( hRealDC, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
    SelectObject(hdc, oldBmp );
    DeleteObject(hScreen);
    DeleteDC(hdc);
    // Double-buffering
    EndPaint(hwndDlg, &ps);
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        SIMULATION_RUNNING = true;
        mainDlgHWND = hwndDlg;
        SetTimer(hwndDlg, timerID, TIMER_T, OnTimer);
        Particles.push_back(Particle(4,4));
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_PAINT:
        OnPaint(hwndDlg);
        break;

    case WM_LBUTTONUP: {
        int cx = LOWORD(lParam);
        int cy = HIWORD(lParam);
        int x, y;
        CalculateNearestGridPoint(x, y, cx, cy);
        if (!isGridOccupied(x, y) && lastCreationTime != timerState){
            Particles.push_back(Particle(x, y, RGB(rand()%256,rand()%256,rand()%256)));
            lastCreationTime = timerState;
            SIMULATION_RUNNING = true;
            InvalidateRect(hwndDlg, nullptr, FALSE);
        }
        break;
    }

    case WM_MOUSEMOVE: {
        int cx = LOWORD(lParam);
        int cy = HIWORD(lParam);
        int x, y;
        CalculateNearestGridPoint(x, y, cx, cy);
        if (!isGridOccupied(x, y) ){
            fake_part.x = x;
            fake_part.y = y;
            InvalidateRect(hwndDlg, nullptr, FALSE);
        }
        break;
    }

    case WM_SIZE:
        InvalidateRect(hwndDlg, nullptr, FALSE);
        break;

    case WM_KEYDOWN:
    {
        if (wParam == 0x45){ //key: E
            Particles.clear();
            InvalidateRect(hwndDlg, nullptr, FALSE);
        }
        break;
    }

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case MENU_SETTINGS:{
            SIMULATION_RUNNING = false;
            DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwndDlg, (DLGPROC)DlgSettings);
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
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
