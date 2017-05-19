#undef UNICODE
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>


HINSTANCE hInst;
HWND hDialog;

struct Student
{
    std::string Surname;
    int Score;
    Student(std::string& sur, int score): Surname(sur), Score(score)
    {}
    operator std::string() const
    {
        std::ostringstream tmp;
        tmp << Surname << " (" << Score << ")";
        return tmp.str();
    }
};

std::vector <Student> _students;

void AddStudent(char* surname, char* score)
{
    using namespace std;
    string t_surname(surname, strlen(surname));
    int t_score = atoi(score);
    if (t_surname.size() == 0){
        MessageBox(hDialog, "Surname can't be empty!", "Error", MB_OK | MB_ICONERROR);
        return;
    }
    else if (strlen(score) == 0 || t_score < 0 || t_score > 10){
        MessageBox(hDialog, "Score is invalid!\n\nMust be a number from 0 to 10", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    Student t_student(t_surname, t_score);
    _students.push_back(t_student);

    SendDlgItemMessage(hDialog, ID_STUDENTS_LIST, LB_ADDSTRING, 0, (LPARAM)((string)t_student).c_str());
}

void RenderStudentsList()
{
    SendDlgItemMessage(hDialog, ID_STUDENTS_LIST, LB_RESETCONTENT, 0, 0);
    for(auto it = _students.begin(); it != _students.end(); it++)
        SendDlgItemMessage(hDialog, ID_STUDENTS_LIST, LB_ADDSTRING, 0, (LPARAM)((std::string)*it).c_str());
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        hDialog = hwndDlg;
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
        exit(0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        char surname[100];
        char score[100];
        GetDlgItemText(hwndDlg, ID_SURNAME_TEXTBOX, surname, sizeof(surname));
        GetDlgItemText(hwndDlg, ID_SCORE_TEXTBOX, score, sizeof(score));

        switch(LOWORD(wParam)) {

        case ACC_ADD:
        case ID_ADD_BUTTON:{
            AddStudent(surname, score);
            break;
        }

        case ACC_FIND:
        case ID_FIND_BUTTON: {
            std::string t_surname(surname, strlen(surname));
            auto found_student = std::find_if(_students.begin(), _students.end(), [&t_surname](const Student& st){
                if (st.Surname == t_surname)
                    return true;
                return false;
            });
            int item_index = found_student - _students.begin();
            if (item_index >= _students.size()) { // not found
                SendDlgItemMessage(hDialog, ID_STUDENTS_LIST, LB_SETCURSEL, -1, 0);
            }
            else {
                SendDlgItemMessage(hDialog, ID_STUDENTS_LIST, LB_SETCURSEL, item_index, 0);
            }
            break;
        }

        case ID_SORT_BUTTON: {
            std::sort(_students.begin(), _students.end(), [](const Student& st1, const Student& st2){
                return st1.Surname < st2.Surname;
            });
            RenderStudentsList();
            break;
        }

        case ACC_REMOVE:
        case ID_REMOVE_BUTTON: {
            int selected_index = SendDlgItemMessage(hDialog, ID_STUDENTS_LIST, LB_GETCURSEL, 0, 0);
            if (selected_index < 0) break;
            _students.erase (_students.begin()+selected_index);
            RenderStudentsList();
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
    //InitCommonControls();
    CreateDialog(hInstance, MAKEINTRESOURCE(DLG_MAIN), nullptr, (DLGPROC)DlgMain);
    ShowWindow(hDialog, nShowCmd);

    auto accelerators = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));;
    MSG message;
    while (GetMessage(&message, nullptr, 0, 0))
    {
        if (TranslateAccelerator(hDialog, accelerators, &message)) continue;
        if (IsDialogMessage(hDialog, &message)) continue;
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    DestroyAcceleratorTable(accelerators);

    return (int)message.wParam;

}
