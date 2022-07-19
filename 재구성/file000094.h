#include <iostream>
#include <vector>
using namespace std;

class unit
{
protected:
	int hp;
	int atk;
	vector<string> dropItems;
public:
	unit() : hp(50), atk{5}, dropItems{"잡템", "목검", "천옷"}
	{
	}
	void PrintInfo()
	{
		cout << "hp: " << Hp() << '\n';
		cout << "atk: " << Atk() << '\n';

		cout << "dropItems: ";
		int size = DropItems().size();
		for (int i = 0; i < size; i++)
		{
			cout << DropItems()[i] << " ";
		}
	}
public:
	int Hp() const { return hp; }
	int Atk() const { return atk; }
	vector<string> DropItems() const { return dropItems; }
};

int main()
{
	unit monster;
	monster.PrintInfo();
}