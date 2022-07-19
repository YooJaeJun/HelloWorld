#include "Shop.h"

void Shop::printItemList()
{
	int idx = 0;
	for (auto& good : goods)
	{
		printf("%i", idx);
		good.second.printInfo();
		printf("��������: %i", goods[good.first]);
		idx++;
	}
	printf("������ �������� �Է����ּ���\n");
}

std::string Shop::sell(const int itemIdx)
{
	int idx = 0;
	for (auto& good : goods)
	{
		if (idx == itemIdx)
		{
			std::string ret = good.first.name;
			goods.erase(good.first);
			return ret;
		}
		idx++;
	}
	return "�߸��� �Է��Դϴ�.";
}

void Shop::buy(const Item& item)
{
	goods.emplace(item.name);
}
