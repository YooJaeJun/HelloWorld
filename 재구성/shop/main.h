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
	shop.buy(Item("����1", 100, 1));
	shop.buy(Item("����2", 200, 1));
	shop.buy(Weapon("���", 1000, 1, 5));
	shop.buy(Weapon("ö��", 2000, 1, 10));
	shop.buy(Armor("��������", 1000, 1, 5));
	shop.buy(Armor("ö����", 2000, 1, 10));

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
				player.pop(itemIdx);
			}
		}
		else
		{
			cout << "�߸� �Է��߽��ϴ�. 1 or 2 �� �Է����ּ���. \n";
			continue;
		}
	}
}


