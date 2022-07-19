#include <memory>
#include "screen.h"

screen& screen::get()
{
	static std::unique_ptr<screen> inst;
	if (!inst) inst = std::unique_ptr<screen>(new screen());
	return *inst;
}

screen::screen() 
{
	CONSOLE_CURSOR_INFO cci;

	// 화면 버퍼 2개 생성
	screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
	screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

	// 커서 숨기기
	cci.dwSize = 1;	// 커서로 채워지는 문자 셀의 비율(1~100)
	cci.bVisible = false;	// 화면 표시 여부
	SetConsoleCursorInfo(screenBuffer[0], &cci);	// 생성한 스크린 버퍼에 정의한 커서의 정보를 설정한다.
	SetConsoleCursorInfo(screenBuffer[1], &cci);

	nScreenIndex = 0;
}

void screen::screenFlipping()
{
	SetConsoleActiveScreenBuffer(screenBuffer[nScreenIndex]);	// 버퍼를 콘솔화면에 그린다.
	nScreenIndex = (nScreenIndex == false);
}

void screen::screenClear()
{
	COORD coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(screenBuffer[nScreenIndex], ' ', 160 * 50, coor, &dw);	
	// buffer에 0,0부터 AxB 만큼 ' '로 채운다.
	// dw 값은 버퍼에 실제 기록된 문자수를 받는 변수 포인터
}

void screen::screenRelease()
{
	CloseHandle(screenBuffer[0]);
	CloseHandle(screenBuffer[1]);
}

void screen::screenPrint(int x, int y, string str)	// x, y 좌표에 string 출력
{
	DWORD dw;
	COORD cursorPosition = { (short)x * 2, (short)y };
	SetConsoleCursorPosition(screenBuffer[nScreenIndex], cursorPosition);
	WriteFile(screenBuffer[nScreenIndex], (LPCVOID)str.c_str(), (DWORD)str.size(), &dw, nullptr);	// string 입력
}

void screen::setColor(unsigned short color)
{
	SetConsoleTextAttribute(screenBuffer[nScreenIndex], color);
}