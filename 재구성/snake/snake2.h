#include "snake.h"
#include "gameCore.h"

snakeData::snakeData()
{
	const int x1 = 5, y1 = 5, x2 = 5, y2 = 6, x3 = 5, y3 = 7;

	hitbox()->pushFront({ x1, y1 });
	gameCore::get().setGrid(x1, y1, static_cast<int>(eGrid::snake));
	hitbox()->pushFront({ x2, y2 });
	gameCore::get().setGrid(x2, y2, static_cast<int>(eGrid::snake));
	hitbox()->pushFront({ x3, y3 });
	gameCore::get().setGrid(x3, y3, static_cast<int>(eGrid::snake));

	setMoveTime(500);
}

snakeData::~snakeData() {}

void snakeData::update(clock_t curTime)
{
	move();
}

void snakeData::move()
{
	if (life() == 0) return;

	node<coord>* cur = hitbox()->head();
	gameCore::get().setGrid(
		cur->val().x(), 
		cur->val().y(), 
		static_cast<int>(eGrid::snake));

	int nx = cur->val().x() + gameCore::get().dx()[dir()];
	int ny = cur->val().y() + gameCore::get().dy()[dir()];
	hitbox()->pushFront({ nx, ny });

	node<coord>* tail = hitbox()->tail();
	gameCore::get().setGrid(
		tail->val().x(), 
		tail->val().y(), 
		static_cast<int>(eGrid::empty));

	hitbox()->popBack();
}

void snakeData::render()
{
	screen::get().setColor(static_cast<int>(eColor::brightRed));
	if (life() == 0)
	{
		screen::get().screenPrint(6, 25, "¹ìÀÌ Á×¾ú½À´Ï´Ù !");
		return;
	};

	screen::get().setColor(static_cast<int>(eColor::brightYellow));

	node<coord>* cur = hitbox()->head();
	screen::get().screenPrint(cur->val().x(),
		cur->val().y(),
		headString());

	while (cur = cur->next())
	{
		screen::get().screenPrint(
			cur->val().x(),
			cur->val().y(),
			tailString());
	}
}

void snakeData::rotate(int input)
{
	switch (input)
	{
	case static_cast<int>(eDirInput::right):
		setDir(static_cast<int>(eDir::right));
		setHeadString("¢º");
		break;
	case static_cast<int>(eDirInput::down):
		setDir(static_cast<int>(eDir::down));
		setHeadString("¡å");
		break;
	case static_cast<int>(eDirInput::left):
		setDir(static_cast<int>(eDir::left));
		setHeadString("¢¸");
		break;
	case static_cast<int>(eDirInput::up):
		setDir(static_cast<int>(eDir::up));
		setHeadString("¡ã");
		break;
	}
}
void snakeData::release()
{
	setLife(0);
	node<coord>* cur = hitbox()->head();
	do {
		gameCore::get().setGrid(
			cur->val().x(), 
			cur->val().y(), 
			static_cast<int>(eGrid::empty));
	} while (cur = cur->next());

	hitbox()->clear();
}

void snakeData::eat()
{
	hitbox()->pushBack({ 
		hitbox()->tail()->val().x() - gameCore::get().dx()[dir()],
		hitbox()->tail()->val().y() - gameCore::get().dy()[dir()] });

	int x = hitbox()->head()->val().x();
	int y = hitbox()->head()->val().y();
	gameCore::get().setGrid(x, y, static_cast<int>(eGrid::snake));
}

int snakeData::dir() const { return dir_; }

int snakeData::score() const { return score_; };

const string snakeData::headString() const { return headString_; }

const string snakeData::tailString() const { return tailString_; }

int snakeData::life() const { return life_; }


void snakeData::setDir(const int dir) { dir_ = dir; }

void snakeData::setScore(const int score) { score_ = score; }

void snakeData::setHeadString(const string headString) { headString_ = headString; }

void snakeData::setTailString(const string tailString) { tailString_ = tailString; }

void snakeData::setLife(const int life) { life_ = life; }
