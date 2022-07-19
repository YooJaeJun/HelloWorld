#include "Player.h"

void Player::printMoney()
{
	printf("소지금: %i \n", money);
}

bool Player::isPossibleMoney(const Item& item)
{
	if (item.price <= money) return true;
	else printf("돈이 충분하지 않습니다.");
	return false;
}

void Player::push(const int itemIdx)
{
	inven[itemIdx].count++;
}

bool Player::hasItem(const int itemIdx)
{
	if (inven[itemIdx].count > 0) return true;
	else printf("아이템이 없습니다.");
	return false;
}

Item& Player::pop(const int itemIdx)
{
	inven[itemIdx].count--;
	printf("%s (을/를) 판매했습니다.", inven[itemIdx].name.c_str());
	return inven[itemIdx];
}