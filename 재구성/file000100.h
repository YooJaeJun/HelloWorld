#include "Shop.h"

void Shop::printItemList()
{
	int idx = 0;
	for (auto& good : goods)
	{
		printf("%i", idx);
		good.second.printInfo();
		printf("소지개수: %i", goods[good.first]);
		idx++;
	}
	printf("구매할 아이템을 입력해주세요\n");
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
	return "잘못된 입력입니다.";
}

void Shop::buy(const Item& item)
{
	goods.emplace(item.name);
}
