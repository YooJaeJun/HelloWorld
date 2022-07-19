#include "Player.h"

void Player::printMoney()
{
	printf("������: %i \n", money);
}

bool Player::isPossibleMoney(const Item& item)
{
	if (item.price <= money) return true;
	else printf("���� ������� �ʽ��ϴ�.");
	return false;
}

void Player::push(const int itemIdx)
{
	inven[itemIdx].count++;
}

bool Player::hasItem(const int itemIdx)
{
	if (inven.size() <= itemIdx ||
		inven[itemIdx].count <= 0)
	{
		printf("�������� �����ϴ�.");
		return false;
	}
	else return true;
}

Item& Player::pop(const int itemIdx)
{
	inven[itemIdx].count--;
	printf("%s (��/��) �Ǹ��߽��ϴ�.", inven[itemIdx].name.c_str());
	return inven[itemIdx];
}