/*
    Copyright (c) 2017 Maxim Teryokhin
    This code is licensed under MIT. See LICENSE file for more details.
*/
#undef UNICODE
#include <windows.h>
#include "resource.h"
#include "Interface.h"


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    return DialogBox(hInstance, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)Interface::DlgMain);
}
