#include <windows.h>
#include <assert.h>
#include "Bitmap.h"

Bitmap::Bitmap(int w,int h)
{
	HDC hdc;

	hdc=GetDC(NULL);
	hBit=CreateCompatibleBitmap(hdc,width=w,height=h);
	ReleaseDC(NULL,hdc);
}

bool Bitmap::Load(int ID)
{
	UnLoad();
	hBit=LoadBitmap(GetModuleHandle(NULL),MAKEINTRESOURCE(ID));
	if (hBit==NULL) {
		return false;
	}
	PrepareSize();
	return true;
}

bool Bitmap::Load(TCHAR *Path)
{
	HANDLE hFile;
	DWORD FileSize, dwRead;
	BITMAPFILEHEADER *fh;
	PVOID ih;
	HDC hdc;

	UnLoad();
	hFile=CreateFile(Path,GENERIC_READ,0,NULL,
		OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	if (hFile==INVALID_HANDLE_VALUE) {
		return false;
	}
	FileSize=GetFileSize(hFile,NULL);

	fh=(BITMAPFILEHEADER *)malloc(FileSize);
	ReadFile(hFile,fh,FileSize,&dwRead,NULL);
	CloseHandle(hFile);

	ih=((PBYTE)fh+sizeof(BITMAPFILEHEADER));
	hdc=GetDC(NULL);
	hBit=CreateDIBitmap(hdc,(BITMAPINFOHEADER *)ih,CBM_INIT,
		(PBYTE)fh+fh->bfOffBits,(BITMAPINFO *)ih,DIB_RGB_COLORS);
	ReleaseDC(NULL,hdc);
	free(fh);
	PrepareSize();
	return true;
}

void Bitmap::Save(TCHAR *Path)
{
	BITMAPFILEHEADER fh;
	BITMAPINFOHEADER ih;
	BITMAP bit;
	BITMAPINFO *pih;
	int PalSize;
	HANDLE hFile;
	DWORD dwWritten,Size;
	HDC hdc;
	assert(hBit != NULL);

	// 전체 화면에 대한 DC를 구한다.
	hdc=GetDC(NULL);

	// 비트맵 정보로부터 정보 구조체를 초기화한다.
	GetObject(hBit,sizeof(BITMAP),&bit);
	ih.biSize=sizeof(BITMAPINFOHEADER);
	ih.biWidth=bit.bmWidth;
	ih.biHeight=bit.bmHeight;
	ih.biPlanes=1;
	ih.biBitCount=bit.bmPlanes*bit.bmBitsPixel;
	if (ih.biBitCount > 8) ih.biBitCount=24;
	ih.biCompression=BI_RGB;
	ih.biSizeImage=0;
	ih.biXPelsPerMeter=0;
	ih.biYPelsPerMeter=0;
	ih.biClrUsed=0;
	ih.biClrImportant=0;

	// 정보 구조체 + 팔레트 크기만큼 메모리를 할당하고 이 버퍼에 
	// 정보 구조체를 복사한다.
	PalSize=(ih.biBitCount==24 ? 0:1 << ih.biBitCount)*sizeof(RGBQUAD);
	pih=(BITMAPINFO *)malloc(ih.biSize+PalSize);
	pih->bmiHeader=ih;

	// 비트맵의 크기를 구한다.
	GetDIBits(hdc,hBit,0,bit.bmHeight,NULL,pih,DIB_RGB_COLORS);
	ih=pih->bmiHeader;

	// 비트맵 크기가 구해지지 않았을 경우 수작업으로 직접 계산한다.
	if (ih.biSizeImage == 0) {
		ih.biSizeImage=((((ih.biWidth*ih.biBitCount)+31) & ~31) >> 3) * ih.biHeight;
	}

	// 래스터 데이터를 읽기위해 메모를 재할당한다.
	Size=ih.biSize+PalSize+ih.biSizeImage;
	pih=(BITMAPINFO *)realloc(pih,Size);

	// 래스터 데이터를 읽어들인다.
	GetDIBits(hdc,hBit,0,bit.bmHeight,(PBYTE)pih+ih.biSize+PalSize,pih,DIB_RGB_COLORS);

	// 파일 헤더를 만든다.
	fh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+PalSize;
	fh.bfReserved1=0;
	fh.bfReserved2=0;
	fh.bfSize=Size+sizeof(BITMAPFILEHEADER);
	fh.bfType=0x4d42;

	// 파일을 생성하고 파일 헤더와 정보 구조체, 팔레트, 래스터 데이터를 출력한다.
	hFile=CreateFile(Path,GENERIC_WRITE,0,NULL,
		CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	WriteFile(hFile,&fh,sizeof(fh),&dwWritten,NULL);
	WriteFile(hFile,pih,Size,&dwWritten,NULL);

	free(pih);
	ReleaseDC(NULL,hdc);
	CloseHandle(hFile);
}

void Bitmap::PrepareSize()
{
	BITMAP bit;
	assert(hBit != NULL);

	GetObject(hBit,sizeof(BITMAP),&bit);
	width=bit.bmWidth;
	height=bit.bmHeight;
}

void Bitmap::Draw(HDC hdc,int x,int y)
{
	Draw(hdc,x,y,width,height);
}

void Bitmap::Draw(HDC hdc,int x,int y,int w,int h,int sx/*=0*/,int sy/*=0*/)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	assert(hBit != NULL);

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hBit);

	BitBlt(hdc,x,y,w,h,MemDC,sx,sy,SRCCOPY);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void Bitmap::Stretch(HDC hdc,int x,int y,int w,int h,int sx,int sy,
	int sw/*=-1*/,int sh/*=-1*/)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int srcw,srch;
	assert(hBit != NULL);

	MemDC=CreateCompatibleDC(hdc);
	OldBitmap=(HBITMAP)SelectObject(MemDC, hBit);

	if (sw==-1) srcw=width; else srcw=sw;
	if (sh==-1) srch=height; else srcw=sh;
	StretchBlt(hdc,x,y,w,h,MemDC,sx,sy,srcw,srch,SRCCOPY);

	SelectObject(MemDC,OldBitmap);
	DeleteDC(MemDC);
}

void Bitmap::Draw(HDC hdc,int x,int y,COLORREF Mask)
{
	BITMAP bm;
	COLORREF cColor;
	HBITMAP bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC		hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT	ptSize;
	assert(hBit != NULL);

	hdcTemp = CreateCompatibleDC(hdc);
	SelectObject(hdcTemp, hBit);
	GetObject(hBit, sizeof(BITMAP), (LPSTR)&bm);
	ptSize.x = bm.bmWidth;
	ptSize.y = bm.bmHeight;
	DPtoLP(hdcTemp, &ptSize,1);

	hdcBack   = CreateCompatibleDC(hdc);
	hdcObject = CreateCompatibleDC(hdc);
	hdcMem    = CreateCompatibleDC(hdc);
	hdcSave   = CreateCompatibleDC(hdc);

	bmAndBack   = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem    = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);
	bmSave      = CreateCompatibleBitmap(hdc, ptSize.x, ptSize.y);

	bmBackOld   = (HBITMAP) SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP) SelectObject(hdcObject, bmAndObject);
	bmMemOld    = (HBITMAP) SelectObject(hdcMem, bmAndMem);
	bmSaveOld   = (HBITMAP) SelectObject(hdcSave, bmSave);

	SetMapMode(hdcTemp, GetMapMode(hdc));

	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	cColor = SetBkColor(hdcTemp, Mask);

	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	SetBkColor(hdcTemp, cColor);

	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);
	BitBlt(hdcMem , 0, 0, ptSize.x, ptSize.y, hdc      , x, y, SRCCOPY);
	BitBlt(hdcMem , 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack  , 0, 0, SRCAND);
	BitBlt(hdcMem , 0, 0, ptSize.x, ptSize.y, hdcTemp  , 0, 0, SRCPAINT);
	BitBlt(hdc    , x, y, ptSize.x, ptSize.y, hdcMem   , 0, 0, SRCCOPY);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave  , 0, 0, SRCCOPY);

	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));
	
	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}

