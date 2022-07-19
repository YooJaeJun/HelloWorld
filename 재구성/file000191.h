#include "core/screen.h"
#include "core/fps.h"
#include "stage/game.h"

void init();
void update(clock_t curTime);
void render();
void release();
void waitRender(clock_t oldTime);
int getKeyEvent();

int main()
{
	init();
	srand(GetTickCount64());

	while (1)
	{
		int nKey = getKeyEvent();
		if (nKey == 'q') break;
		else if (nKey == 'r')
		{
			game::get().release();
			game::get().init();
		}
		game::get().keyProcess(nKey);

		update(clock());

		render();
		waitRender(clock());

	}

	release();
	screen::get().screenRelease();

	_CrtDumpMemoryLeaks();
	return 0;
}

void init()
{
	fps::get().init();
	game::get().init();
}

void update(clock_t curTime)
{
	game::get().update(curTime);
}

void render()
{
	screen::get().screenClear();

	game::get().render();
	fps::get().render();

	screen::get().screenFlipping();
}

void release()
{
	game::get().release();
}

void waitRender(clock_t oldTime)
{
	clock_t curTime;
	while (1)
	{
		curTime = clock();
		if (curTime - oldTime > 100)
			break;
	}
}

int getKeyEvent()
{
	if (_kbhit())
		return _getch();

	return -1;
}
