#include "game.h"
#include "gameCore.h"

game& game::get()
{
	static std::unique_ptr<game> inst;
	if (!inst) inst = std::unique_ptr<game>(new game);
	return *inst;
}

void game::init()
{
}

void game::update(clock_t curTime)
{
	if (curTime - snake().oldTime() > snake().moveTime())
	{
		snake().update(curTime);
		hitProcess();
		snake().setOldTime(curTime);
	}
	item().update(curTime);
}

void game::hitProcess()
{
	if (snake().life() == 0) return;

	node<coord>* head = snake().hitbox()->head();
	const int maxWidth = gameCore::get().maxWidth();
	const int targetInHead = gameCore::get().gridXY(head->val().x(), head->val().y());

	if (head->val().x() < 1 ||
		head->val().x() >= maxWidth / 2 ||
		head->val().y() < 5 ||
		head->val().y() >= maxWidth / 2)
	{
		snake().release();
	}
	else if (targetInHead == static_cast<int>(eGrid::wall) ||
		targetInHead == static_cast<int>(eGrid::snake))
	{
		snake().release();
	}
	else if (targetInHead == static_cast<int>(eGrid::item))
	{
		snake().eat();
		item().pop(head->val().x(), head->val().y());
	}
}

void game::render()
{
	renderBackgroundLine();
	renderScore();
	renderSpeed();
	renderMessage();
	item().render();
	snake().render();
	screen::get().setColor(static_cast<int>(eColor::gray));
}

void game::renderBackgroundLine()
{
	screen::get().setColor(static_cast<int>(eColor::gray));
	screen::get().screenPrint(0, 4, "■■■■■■■■■■■■■■■■■■■■■");
	for (int y = 5; y < 20; y++)
	{
		screen::get().screenPrint(0, y, "■");
		screen::get().screenPrint(20, y, "■");
	}
	screen::get().screenPrint(0, 20, "■■■■■■■■■■■■■■■■■■■■■");
}

void game::renderScore()
{
	screen::get().setColor(static_cast<int>(eColor::white));
	scoreStr = "Score :  ";
	scoreStr += to_string(snake().score());
	screen::get().screenPrint(24, 10, scoreStr);
}


void game::renderSpeed()
{
	screen::get().setColor(static_cast<int>(eColor::white));
	speedStr += to_string(static_cast<float>(snake().moveTime()) / 1000);
	screen::get().screenPrint(24, 12, speedStr);
	speedStr += to_string(static_cast<float>(snake().moveTime()) / 1000);
	speedStr += speedStrMeterPerSecond;
	screen::get().screenPrint(24, 12, speedStr);
}

void game::renderMessage()
{
	screen::get().setColor(static_cast<int>(eColor::white));
	screen::get().screenPrint(24, 13, msgStr1);
	screen::get().screenPrint(24, 14, msgStr2);
	screen::get().screenPrint(24, 15, msgStr3);
}

void game::keyProcess(int key)
{
	if (key == 224)	// 방향키 입력 시 "224 방향키idx" 가 들어옴
	{
		int input = _getch();
		snake().rotate(input);
	}
}

void game::release()
{
	if (false == snake_.hitbox()->empty()) 
		snake().hitbox()->clear();
}


snakeData& game::snake() { return snake_; }

itemData& game::item() { return item_; }
