#undef UNICODE
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include "TabControl.h"
#include <cmath>
#include <ctime>

HINSTANCE hInst;
HWND hDialog;
TabControl TC;
HWND _dummyLabel;
HWND _listBox;
HWND _addButton;
HWND _deleteButton;
HWND _clearButton;


namespace ControlID
{
	const int TabControl = 1001;
    const int DummyLabel = 1003;
    const int ListBox = 1002;
    const int AddButton = 1004;
    const int DeleteButton = 1005;
    const int ClearButton = 1006;

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

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        srand(time(NULL));
        hDialog = hwndDlg;
        TC =
            TabControl( CreateControl(WC_TABCONTROL, NULL, 10, 10, 800-20, 800-20, ControlID::TabControl));
        TC.AddItem("Random List");
        TC.AddItem("Dummy Text");

        _dummyLabel = CreateControl(WC_STATIC, NULL, 30, 50, 700, 700, ControlID::DummyLabel);
		SetWindowText(_dummyLabel, LOREM);
		TC.Register(1, _dummyLabel);

		_listBox = CreateControl(WC_LISTBOX, LBS_NOTIFY, 20, 50, 100, 800-115, ControlID::ListBox);
        TC.Register(0, _listBox);
        SendMessage(_listBox, LB_ADDSTRING, NULL, (LPARAM)"42");

        _addButton = CreateControl(WC_BUTTON, BS_DEFPUSHBUTTON, 200, 100, 60, 30, ControlID::AddButton);
        SetWindowText(_addButton, "[+]");
        TC.Register(0, _addButton);
        _deleteButton = CreateControl(WC_BUTTON, BS_DEFPUSHBUTTON, 200, 150, 60, 30, ControlID::DeleteButton);
        SetWindowText(_deleteButton, "[-]");
        TC.Register(0, _deleteButton);
        _clearButton = CreateControl(WC_BUTTON, BS_DEFPUSHBUTTON, 200, 200, 60, 30, ControlID::ClearButton);
        SetWindowText(_clearButton, "[Clear]");
        TC.Register(0, _clearButton);

        TC.UpdateTabLayout(0);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_NOTIFY:
    {
        if(TC.TryProcessMessage(uMsg, wParam, lParam))
            return TRUE;
    }

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case ControlID::AddButton:{
            char buf[50];
            sprintf(buf, "%d", rand()%101);
            SendMessage (_listBox, LB_ADDSTRING, 0, (LPARAM)buf);
            break;
        }

        case ControlID::DeleteButton:{
            auto sel = SendMessage (_listBox, LB_GETCURSEL, 0, 0);
            SendMessage (_listBox, LB_DELETESTRING, sel, 0);
            break;
        }

        case ControlID::ClearButton: {
            SendMessage (_listBox, LB_RESETCONTENT, 0, 0);
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
