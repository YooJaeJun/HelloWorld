#include <cstdio>
#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

//칼라 외부 자료
void ColorSet(int backColor, int textColor) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
}
//커서를 x,y좌표로 이동시킨다.
void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
struct coord {
	size_t x = 0;
	size_t y = 1;
};
coord co;	//콘솔에 차례로 출력 위한 전역변수

enum color_kinds {
	black, blue, green, skyblue, red, pink, orange, white, gray, lightblue, breightgreen, sky, brightred, brightpink, brightyellow, brightwhite
};

//아이템
class item_data {
public:
	item_data() : id_(' '), x_(0), y_(0), color_vari_(0) {}
	explicit item_data(char id, size_t x, size_t y, size_t color_vari) : x_(x), y_(y), color_vari_(color_vari) {
		if (id_ != id) {
			id_ = id;
		}
	}
	char get_id() const { return id_; }
	size_t get_x() const { return x_; }
	size_t get_y() const { return y_; }
	size_t get_color() const { return color_vari_; }
	void set(char id, size_t x, size_t y, size_t color_vari) {
		if (id_ != id) {
			id_ = id;
			x_ = x;
			y_ = y;
			color_vari_ = color_vari;
		}
	}
private:
	char id_;
	size_t x_;
	size_t y_;
	size_t color_vari_;
};

//인벤토리
class inventory {
public:
	inventory() : x_(10), y_(4), isSpace(false) { }
	explicit inventory(size_t x, size_t y) : x_(x), y_(y), isSpace(false) { }
	size_t get_x() const { return x_; }
	size_t get_y() const { return y_; }
	void add(const vector<item_data> items);
	void coord_check(const vector<item_data> items, size_t items_final);
	void item_set(const vector<item_data> items);
	void remove(const vector<item_data> items, char id);
	size_t coord_remove(const vector<item_data> items, char id);
private:
	size_t arr[4][10] = { 0, };	//[핵심] 유효 좌표 기록 및 판단
	size_t x_;
	size_t y_;
	bool isSpace;
};
void inventory::add(const vector<item_data> items) {

	size_t final = items.size() - 1;
	//아이템 유효 좌표 기록
	coord_check(items, final);

	if (isSpace) {
		printf("Success Add Item (id = %c Size= %dx%d)\n"
			, items[final].get_id(), items[final].get_x(), items[final].get_y());
	}
	else {
		printf("Fail Add Item (id = %c Size= %dx%d)\n"
			, items[final].get_id(), items[final].get_x(), items[final].get_y());
	}

	//아이템 채우기
	item_set(items);

	//콘솔창 출력 위한 거리
	puts("");
	co.y += 6;
}

void inventory::coord_check(const vector<item_data> items, size_t items_final) {
	isSpace = false;
	//아이템 들어갈 자리 있는지 검사 로직
	for (size_t y = 0; y != y_; y++) {
		for (size_t x = 0; x != x_; x++) {
			//최초로 할당된 자리 보이면 아이템 들어갈 공간 있는지 다시 검사
			if (arr[y][x] == 0) {
				for (size_t j = y; j != y + items[items_final].get_y(); j++) {
					for (size_t k = x; k != x + items[items_final].get_x(); k++) {
						if (arr[j][k] == 0) {
							isSpace = true;
						}
						else {
							isSpace = false;
							break;
						}
					}
					//남은 공간 없으니 다음 자리 알아보기~
					if (!isSpace) {
						break;
					}
				}
			}
			//남은 공간 찾았으니 좌표 기록하고 순회 검사 빠져나옴
			if (isSpace) {
				for (size_t j = y; j != y + items[items_final].get_y(); j++) {
					for (size_t k = x; k != x + items[items_final].get_x(); k++) {
						arr[j][k] = items_final + 1;
					}
				}
				break;
			}
		}
		if (isSpace) {
			break;
		}
	}
}

void inventory::item_set(const vector<item_data> items) {
	gotoxy(co.x, co.y);
	for (size_t y = 0; y != y_; y++) {
		for (size_t x = 0; x != x_; x++) {
			//좌표에 맞는 아이템 세팅
			if (arr[y][x] != 0) {
				ColorSet(items[arr[y][x] - 1].get_color(), black);
				printf("%c ", items[arr[y][x] - 1].get_id());
			}
			else {
				ColorSet(black, white);
				printf("0 ");
			}
			ColorSet(black, white);
		}
		puts("");
	}
}

void inventory::remove(const vector<item_data> items, char id) {

	//아이템 좌표 판단 및 제거
	int item_index = coord_remove(items, id);

	if (item_index != -1) {
		printf("Success Remove Item (id = %c Size= %dx%d)\n"
			, items[item_index].get_id(), items[item_index].get_x(), items[item_index].get_y());
	}
	else {
		printf("Fail Remove Item (id = %c Size= %dx%d)\n"
			, items[item_index].get_id(), items[item_index].get_x(), items[item_index].get_y());
	}

	item_set(items);

	//콘솔창 출력 위한 거리
	puts("");
	co.y += 6;
}

size_t inventory::coord_remove(const vector<item_data> items, char id) {
	//아이템 순번 찾기
	int item_index = -1;
	for (size_t i = 0; i != items.size(); i++) {
		if (items[i].get_id() == id) {
			item_index = i;
			break;
		}
	}
	if (item_index != -1) {
		//인벤 순회하면서 아이템 좌표 0으로 만들기 (벡터에선 erase 안 함. 땡기지 않음)
		for (size_t y = 0; y != y_; y++) {
			for (size_t x = 0; x != x_; x++) {
				if (arr[y][x] == item_index + 1) {
					arr[y][x] = 0;
				}
			}
		}
	}
	return item_index;	//아이템 있는지
}

int main() {
	vector<item_data> items;
	inventory inven;
	
	items.push_back(item_data('a', 3, 3, blue));
	inven.add(items);
	items.push_back(item_data('b', 1, 1, green));
	inven.add(items);
	items.push_back(item_data('c', 1, 1, skyblue));
	inven.add(items);
	items.push_back(item_data('d', 3, 3, red));
	inven.add(items);
	items.push_back(item_data('e', 1, 4, pink));
	inven.add(items);
	items.push_back(item_data('f', 2, 3, orange));
	inven.add(items);
	items.push_back(item_data('g', 2, 2, white));
	inven.add(items);
	items.push_back(item_data('h', 2, 2, brightpink));
	inven.add(items);
	inven.remove(items, 'd');
	items.push_back(item_data('i', 2, 2, lightblue));
	inven.add(items);
	items.push_back(item_data('j', 2, 2, breightgreen));
	inven.add(items);
	items.push_back(item_data('k', 2, 1, sky));
	inven.add(items);
	items.push_back(item_data('l', 2, 2, brightpink));
	inven.add(items);
	items.push_back(item_data('m', 3, 1, brightpink));
	inven.add(items);

	return 0;
}