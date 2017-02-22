#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include <cstdlib>
#include <cstring>

#define MD_A 1
#define MD_C 0

int MD = MD_A;
HINSTANCE hInst;

void cb_init_mode_a(HWND hwndDlg)
{
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_RESETCONTENT, 0, 0);
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_ADDSTRING, 0, (LPARAM)"+");
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_ADDSTRING, 0, (LPARAM)"-");
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_ADDSTRING, 0, (LPARAM)"*");
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_ADDSTRING, 0, (LPARAM)"/");
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_SETCURSEL, 0, 0);
    MD = MD_A;
}

void cb_init_mode_c(HWND hwndDlg)
{
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_RESETCONTENT, 0, 0);
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_ADDSTRING, 0, (LPARAM)"<");
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_ADDSTRING, 0, (LPARAM)">");
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_ADDSTRING, 0, (LPARAM)"=");
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_ADDSTRING, 0, (LPARAM)"!=");
    SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_SETCURSEL, 0, 0);
    MD = MD_C;
}


void refresh_result(HWND hwndDlg)
{
    char operand1[100];
    char operand2[100];
    int op1, op2, sign;
    GetDlgItemText(hwndDlg, OPERAND1, operand1, sizeof(operand1));
    GetDlgItemText(hwndDlg, OPERAND2, operand2, sizeof(operand2));
    op1 = atoi(operand1);
    op2 = atoi(operand2);
    sign = SendDlgItemMessage(hwndDlg, SIGN_BOX, CB_GETCURSEL, 0, 0);
    int res;
    switch(sign){
    case 0: // + (<)
        res = (MD)?op1+op2:op1<op2;
        break;
    case 1: // - (>)
        res = (MD)?op1-op2:op1>op2;
        break;
    case 2: // * (=)
        res = (MD)?op1*op2:op1==op2;
        break;
    case 3: // / (!+)
        if (MD == MD_A){
            if (op2 == 0) {
                MessageBox(hwndDlg, "Division by zero", "Error", MB_ICONERROR | MB_OK);
                return;
            }
            res = op1/op2;
        }
        else
            res = op1!=op2;
        break;
    }
    char result[100];
    if (MD == MD_A)
        itoa(res, result, 10);
    else
        strcpy(result, (res)?"true":"false");

    SetDlgItemText(hwndDlg, RESULT_FIELD, result);

}


BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        cb_init_mode_a(hwndDlg);
        SendDlgItemMessage(hwndDlg, A_MODE, BM_SETCHECK, BST_CHECKED, 0);

    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case REFRESH_BUTTON:
            refresh_result(hwndDlg);
            break;
        case OPERAND1:
        case OPERAND2:
            if((HIWORD(wParam) == EN_CHANGE && IsDlgButtonChecked(hwndDlg, AUTO_REFRESH_CHKBOX)))
                refresh_result(hwndDlg);
            break;
        case AUTO_REFRESH_CHKBOX:
            EnableWindow(GetDlgItem(hwndDlg, REFRESH_BUTTON), !IsDlgButtonChecked(hwndDlg, AUTO_REFRESH_CHKBOX));
            break;
        case A_MODE:
        case C_MODE:
            if (IsDlgButtonChecked(hwndDlg, A_MODE))
                cb_init_mode_a(hwndDlg);
            else if (IsDlgButtonChecked(hwndDlg, C_MODE))
                cb_init_mode_c(hwndDlg);
            break;
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
