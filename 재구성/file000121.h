#include "Player.h"

void Player::printItemList()
{
	Unit::printItemList();
}

void Player::printMoney()
{
	printf("������: %i \n", money);
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
	printf("%s (��/��) �Ǹ��߽��ϴ�.", inven[itemIdx].name)
	std::string ret = inven[itemIdx].name;
	ret += "(��/��) �Ǹ��߽��ϴ�.";
	return ret;
}