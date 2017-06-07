#undef UNICODE
#include <windows.h>
#include "resource.h"
#include <cstdlib>

void IntToHex(unsigned int n, char* res)
{
	static const char HEX_TABLE[] = "0123456789ABCDEF";
	__asm {
		mov		edx, n
		xor		ecx, ecx
		xor		ebx, ebx
hex_loop:
		mov		eax, edx
		shr		edx, 4
		and		eax, 0xf
		
		mov		bl, HEX_TABLE[eax]
		push	bx
		inc		ecx

		cmp		edx, 0
		jne		hex_loop

		mov		edi, res
		mov		eax, 0
write_loop:
		pop		bx
		mov		byte ptr[edi + eax], bl
		inc		eax
		loop write_loop
		mov		byte ptr[edi + eax], 0
		
	}
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
		case IDOK:
		{
			char input[100];
			GetDlgItemText(hwndDlg, IDC_INPUT, input, sizeof(input));
			unsigned int n = atoi(input);
			char output[100];
			IntToHex(n, output);
			SetDlgItemText(hwndDlg, IDC_OUTPUT, output);
		}
		}
	}
	return TRUE;

	default:
		return FALSE;
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgMain);
	return 0;
}
