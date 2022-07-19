#include "gameCore.h"


gameCore& gameCore::get()
{
	static std::unique_ptr<gameCore> inst;
	if (!inst) inst = std::unique_ptr<gameCore>(new gameCore());
	return *inst;
}

gameCore::gameCore()
{
	grid_ = std::vector<std::vector<int>>(maxWidth() + 1, std::vector<int>(maxWidth() + 1));
}

const int gameCore::maxWidth() const { return maxWidth_; }

std::vector<std::vector<int>> gameCore::grid() const { return grid_; }

const int gameCore::gridXY(const int x, const int y) const { return grid_[x][y]; }

const std::vector<int> gameCore::dy() const { return dy_; }
const std::vector<int> gameCore::dx() const { return dx_; }


void gameCore::setGrid(const int x, const int y, const int target)
{
	grid_[x][y] = target;
}
