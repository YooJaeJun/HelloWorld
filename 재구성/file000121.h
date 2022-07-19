#include "Player.h"

void Player::printItemList()
{
	Unit::printItemList();
}

void Player::printMoney()
{
	printf("소지금: %i \n", money);
}

bool Player::isPossibleMoney(const Item& item)
{
	return item.price <= money;
}

void Player::push(const int itemIdx)
{
	inven[itemIdx].count++;
}

bool Player::hasItem(const int itemIdx)
{
	return inven[itemIdx].count > 0;
}

Item& Player::pop(const int itemIdx)
{
	inven[itemIdx].count--;
	printf("%s (을/를) 판매했습니다.", inven[itemIdx].name)
	std::string ret = inven[itemIdx].name;
	ret += "(을/를) 판매했습니다.";
	return ret;
}