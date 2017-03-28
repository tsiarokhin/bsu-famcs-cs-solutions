#ifndef TABCONTROL_H
#define TABCONTROL_H
#include <windows.h>
#include <commctrl.h>
#include <cstring>
#include <cstdio>
#include <vector>

class TabControl
{
    public:
        TabControl();
        TabControl(HWND _hwnd);
        void AddItem(const char* itemText);
        BOOL TryProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);
        void Register(int tabIndex, HWND control);
        void UpdateTabLayout(int idx);
        virtual ~TabControl();
        operator HWND() const;
    protected:
        HWND _hwnd;
        std::vector< std::pair<int, HWND> > controls;
};

#endif // TABCONTROL_H
