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

	// ȭ�� ���� 2�� ����
	screenBuffer[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
	screenBuffer[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
		0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);

	// Ŀ�� �����
	cci.dwSize = 1;	// Ŀ���� ä������ ���� ���� ����(1~100)
	cci.bVisible = false;	// ȭ�� ǥ�� ����
	SetConsoleCursorInfo(screenBuffer[0], &cci);	// ������ ��ũ�� ���ۿ� ������ Ŀ���� ������ �����Ѵ�.
	SetConsoleCursorInfo(screenBuffer[1], &cci);

	nScreenIndex = 0;
}

void screen::screenFlipping()
{
	SetConsoleActiveScreenBuffer(screenBuffer[nScreenIndex]);	// ���۸� �ܼ�ȭ�鿡 �׸���.
	nScreenIndex = (nScreenIndex == false);
}

void screen::screenClear()
{
	COORD coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(screenBuffer[nScreenIndex], ' ', 160 * 50, coor, &dw);	
	// buffer�� 0,0���� AxB ��ŭ ' '�� ä���.
	// dw ���� ���ۿ� ���� ��ϵ� ���ڼ��� �޴� ���� ������
}

void screen::screenRelease()
{
	CloseHandle(screenBuffer[0]);
	CloseHandle(screenBuffer[1]);
}

void screen::screenPrint(int x, int y, string str)	// x, y ��ǥ�� string ���
{
	DWORD dw;
	COORD cursorPosition = { (short)x * 2, (short)y };
	SetConsoleCursorPosition(screenBuffer[nScreenIndex], cursorPosition);
	WriteFile(screenBuffer[nScreenIndex], (LPCVOID)str.c_str(), (DWORD)str.size(), &dw, nullptr);	// string �Է�
}

void screen::setColor(unsigned short color)
{
	SetConsoleTextAttribute(screenBuffer[nScreenIndex], color);
}