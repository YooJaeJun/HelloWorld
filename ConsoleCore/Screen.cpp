#include "framework.h"

void Screen::Init()
{    
	CONSOLE_CURSOR_INFO cci;     //화면 버퍼 2개를 만든다.    
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);	
	
	//커서 숨기기    
	cci.dwSize = 1;    
	cci.bVisible = FALSE;    
	SetConsoleCursorInfo(g_hScreen[0], &cci);    
	SetConsoleCursorInfo(g_hScreen[1], &cci);
} 

void Screen::Flipping()
{    
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);    
	g_nScreenIndex = (false == g_nScreenIndex);
} 

void Screen::Clear()
{    
	COORD coor = { 0,0 };    
	DWORD dw;    
	FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, coor, &dw);
} 

void Screen::Release()
{    
	CloseHandle(g_hScreen[0]);    
	CloseHandle(g_hScreen[1]);
} 

void Screen::Print(const int x, const int y, string str)
{    
	DWORD dw;    
	COORD CursorPosition = { x, y };    
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	// string to char*
	vector<char> writable(str.begin(), str.end());
	writable.push_back('\0');
	char* ptr = &writable[0];
	WriteFile(g_hScreen[g_nScreenIndex], ptr, writable.size() - 1, &dw, NULL);
} 

void Screen::SetColor(unsigned short color)
{    
	SetConsoleTextAttribute(g_hScreen[g_nScreenIndex], color);
}