#include <iostream>
#include "Unit/Player.h"
#include "Unit/Shop.h"
#include "Item/Item.h"
#include "Item/Weapon.h"
#include "Item/Armor.h"
using namespace std;

int main()
{
	Shop shop;
	Player player;
	vector<Item> item = 
	{ 
		{ Item("잡템1", 100) }, 
		{ Item("잡템2", 200) },
		{ Item("잡템1", 100) },
		{ Weapon({"목검", 1000}, 9999) },
		{ Weapon({"철검", 2000}, 10) },
		{ Armor({"나무투구", 1000}, 1) },
		{ Armor({"철투구", 2000}, 10) },
	};

	while (1)
	{
		player.printMoney();
		cout << "1. 구매  2. 판매 \n";
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
			else cout << "돈이 충분하지 않습니다.";
		}
		else if (select == 2)
		{
			player.printItemList();
			int itemIdx;
			cin >> itemIdx;

		}
		else
		{
			cout << "잘못 입력했습니다. 1 or 2 만 입력해주세요. \n";
			continue;
		}
	}
}


