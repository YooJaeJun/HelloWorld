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
		{ Item("����1", 100, 1) }, 
		{ Item("����2", 200, 1) },
		{ Item("����1", 100, 1) },

	};

	while (1)
	{
		player.printMoney();
		cout << "1. ����  2. �Ǹ� \n";
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
			cout << "�߸� �Է��߽��ϴ�. 1 or 2 �� �Է����ּ���. \n";
			continue;
		}
	}
}


