#include "TabControl.h"

TabControl::TabControl()
{
}

TabControl::TabControl(HWND _hwnd): _hwnd(_hwnd)
{
}

TabControl::~TabControl()
{
}

TabControl::operator HWND() const
{
	return _hwnd;
}

void TabControl::AddItem(const char* itemText)
{
    char buffer[50];
    strcpy(buffer, itemText);
    TCITEM tabControlItem;
    tabControlItem.mask = TCIF_TEXT;
    tabControlItem.pszText = buffer;
    auto newTabIndex = TabCtrl_GetItemCount(_hwnd);
    TabCtrl_InsertItem(_hwnd, newTabIndex, &tabControlItem);
}

BOOL TabControl::TryProcessMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
    auto notificationMessageHandler = (NMHDR*)lParam;
    if (notificationMessageHandler->hwndFrom != _hwnd) return FALSE;

    switch (notificationMessageHandler->code)
    {
        case TCN_SELCHANGE:
        {
            auto tabIndex = TabCtrl_GetCurSel(_hwnd);
            UpdateTabLayout(tabIndex);
            return TRUE;
        }
    }

    return FALSE;
}
void TabControl::UpdateTabLayout(int idx)
{
    for(auto it = controls.begin(); it != controls.end(); it++)
        ShowWindow(it->second, (it->first == idx)? SW_SHOW : SW_HIDE);
}

void TabControl::Register(int tabIndex, HWND control)
{
    controls.push_back(std::make_pair(tabIndex, control));
}

