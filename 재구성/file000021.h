#include <windows.h>
#include "Bitmap.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("BitmapClass");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;

	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

void MakeEllipseBitmap()
{
	Bitmap Bit(640,480);
	HBITMAP OldBitmap;
	HDC hdc,MemDC;
	int i;

	hdc=GetDC(NULL);
	MemDC=CreateCompatibleDC(hdc);
	ReleaseDC(NULL,hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC,Bit.GetBitmap());

	PatBlt(MemDC,0,0,640,480,WHITENESS);
	SelectObject(MemDC,GetStockObject(NULL_BRUSH));
	for (i=0;i<240;i+=10) {
		Ellipse(MemDC,320-i,240-i,320+i,240+i);
	}

	Bit.Save("c:\\ellipse.bmp");
	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static Bitmap Bit;
	Bitmap tBit;
	TCHAR *Mes="A:파일에서 비트맵 읽기, B:비트맵 저장, C:동심원 비트맵 생성";

	switch(iMessage) {
	case WM_CREATE:
		Bit.Load(IDB_BITMAP1);
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case 'A':
			hdc=GetDC(hWnd);
			if (tBit.Load("test.bmp")) {
				tBit.Draw(hdc,10,260);
			} else {
				MessageBox(hWnd,"test.bmp 파일이 없습니다.","알림",MB_OK);
			}
			ReleaseDC(hWnd,hdc);
			break;
		case 'B':
			Bit.Save("c:\\save.bmp");
			MessageBox(hWnd,"c:\\save.bmp 파일로 저장했습니다","알림",MB_OK);
			break;
		case 'C':
			MakeEllipseBitmap();
			MessageBox(hWnd,"c:\\ellipse.bmp 파일로 저장했습니다","알림",MB_OK);
			break;
		}
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,10,10,Mes,lstrlen(Mes));
		Bit.Draw(hdc,10,50);
		Bit.Draw(hdc,210,50,50,50,25,25);
		Bit.Stretch(hdc,410,50,Bit.GetWidth()*2,Bit.GetHeight()*2,0,0);
		Bit.Draw(hdc,210,150,RGB(0,255,0));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
