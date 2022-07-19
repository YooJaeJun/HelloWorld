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
		{ Item("잡템1", 100, 1) }, 
		{ Item("잡템2", 200, 1) },
		{ Item("잡템1", 100, 1) },

	};

	while (1)
	{
		player.printMoney();
		cout << "1. 구매  2. 판매 \n";
		int select;
		cin >> select;
		if (select == 1)
		{
			
		}
		else if (select == 2)
		{

		}
		else
		{
			cout << "잘못 입력했습니다. 1 or 2 만 입력해주세요. \n";
			continue;
		}
	}
}


