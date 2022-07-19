#include <iostream>
#include "Unit/Player.h"
#include "Unit/Shop.h"
#include "Item/Weapon.h"
#include "Item/Armor.h"
using namespace std;

int main()
{
	Shop shop;
	Player player;
	shop.buy(Item("����1", 100));
	{ 
		{ Item("����1", 100) },
		{ Item("����2", 200) },
		{ Item("����1", 100) },
		{ Weapon({"���", 1000}, 9999) },
		{ Weapon({"ö��", 2000}, 10) },
		{ Armor({"��������", 1000}, 1) },
		{ Armor({"ö����", 2000}, 10) },
	};

	while (1)
	{
		player.printMoney();
		cout << "1. ����  2. �Ǹ� \n";
		int select;
		cin >> select;

		if (select == 1)
		{
			shop.printItemList();
			int itemIdx;
			cin >> itemIdx;
			if (player.isPossibleMoney(shop.inven[itemIdx]))
			{
				shop.sell(itemIdx);
				player.push(itemIdx);
			}
		}
		else if (select == 2)
		{
			player.printItemList();
			int itemIdx;
			cin >> itemIdx;
			if (player.hasItem(itemIdx))
			{
				shop.buy(player.pop(itemIdx));
			}
		}
		else
		{
			cout << "�߸� �Է��߽��ϴ�. 1 or 2 �� �Է����ּ���. \n";
			continue;
		}
	}
}


