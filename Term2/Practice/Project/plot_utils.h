#ifndef PLOT_UTILS_H_INCLUDED
#define PLOT_UTILS_H_INCLUDED

void ScreenShot(char*BmpName, HWND hDlg)
{
	HDC DevC = GetDC(hDlg);
	RECT DesktopParams;
	GetClientRect(hDlg,&DesktopParams);
	DWORD Width = DesktopParams.right - DesktopParams.left;
	DWORD Height = DesktopParams.bottom - DesktopParams.top;


	DWORD FileSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+(sizeof(RGBTRIPLE)+1*(Width*Height*4));
	char *BmpFileData = (char*)GlobalAlloc(0x0040,FileSize);

	PBITMAPFILEHEADER BFileHeader = (PBITMAPFILEHEADER)BmpFileData;
	PBITMAPINFOHEADER  BInfoHeader = (PBITMAPINFOHEADER)&BmpFileData[sizeof(BITMAPFILEHEADER)];

	BFileHeader->bfType = 0x4D42; // BM
	BFileHeader->bfSize = sizeof(BITMAPFILEHEADER);
	BFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER);

	BInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
	BInfoHeader->biPlanes = 1;
	BInfoHeader->biBitCount = 24;
	BInfoHeader->biCompression = BI_RGB;
	BInfoHeader->biHeight = Height;
	BInfoHeader->biWidth = Width;

	RGBTRIPLE *Image = (RGBTRIPLE*)&BmpFileData[sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)];
	HDC CaptureDC = CreateCompatibleDC(DevC);
	HBITMAP CaptureBitmap = CreateCompatibleBitmap(DevC,Width,Height);
	SelectObject(CaptureDC,CaptureBitmap);
	BitBlt(CaptureDC,0,0,Width,Height,DevC,0,0,SRCCOPY|CAPTUREBLT);
	GetDIBits(CaptureDC,CaptureBitmap,0,Height,Image,(LPBITMAPINFO)BInfoHeader, DIB_RGB_COLORS);

	DWORD Junk;
	HANDLE FH = CreateFileA(BmpName,GENERIC_WRITE,FILE_SHARE_WRITE,0,CREATE_ALWAYS,0,0);
	WriteFile(FH,BmpFileData,FileSize,&Junk,0);
	CloseHandle(FH);
        GlobalFree(BmpFileData);
}

#endif // PLOT_UTILS_H_INCLUDED
