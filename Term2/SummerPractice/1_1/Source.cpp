#undef UNICODE
#include <windows.h>
#include "resource.h"

OPENFILENAME ofn;

char* asm_strtok(char* s, bool new_str = false)
{
	static int pos = 0;
	static bool string_ended = false;
	
	if (new_str) string_ended = pos = 0;
	if (string_ended) return NULL;
	
	int len = strlen(s + pos);
	char* res;
	
	__asm {
		cld
		mov		al, '\\'
		mov		edi, s
		add		edi, pos
		mov		ecx, len
		repne	scasb
		jecxz	not_found
		mov		byte ptr [edi-1], 0

		mov		eax, s
		add		eax, pos
		mov		res, eax

		mov		eax, edi
		sub		eax, s
		mov		pos, eax
		jmp		f_end

not_found:
		mov		eax, s
		add		eax, pos
		mov		res, eax
		mov		string_ended, 1
f_end:
	}
	return res;
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		EndDialog(hwndDlg, 0);
		break;
	
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
		{
			EndDialog(hwndDlg, 1);
			break;
		}
		case IDOK:
		{
			EndDialog(hwndDlg, 2);
			break;
		}
		case IDADD:
		{
			char szFile[260] = {0};
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = NULL;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
			GetOpenFileName(&ofn);
			SendDlgItemMessage(hwndDlg, IDLIST, LB_ADDSTRING, 0, (LPARAM)szFile);
			char *w = asm_strtok(szFile, true);
			while (w) {
				SendDlgItemMessage(hwndDlg, IDLIST, LB_ADDSTRING, 0, (LPARAM)w);
				w = asm_strtok(szFile);
			}

			break;
		}

		}
	}
	return TRUE;

	
	default:
		return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	int code = DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgMain);
	if (code == 1) MessageBox(NULL, "CANCEL was pressed","Exit", MB_OK);
	if (code == 2) MessageBox(NULL, "OK was pressed", "Exit", MB_OK);
	return 0;
}
