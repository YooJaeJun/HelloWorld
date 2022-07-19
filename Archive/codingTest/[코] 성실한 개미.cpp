#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<vector<int>> v(11, vector<int>(11, 0));

	int num, now_x = 0, now_y = 0;
	bool stop = false;
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			cin >> num;
			v[i][j] = num;

			//먹이를 찾은 경우 셋
			if ((i == 2 && j == 2 && v[i][j] == 2)
				|| (v[i][j] == 2 && j == now_x + 1 && i == now_y)
				|| (v[i][j] == 2 && i == now_y + 1 && j == now_x)
				//맨 아래 가장 오른쪽
				|| (!stop && i == 9 && j == 9)
				//더 이상 움직일 수 없는 경우
				|| (!stop && v[i][j] == 0 && v[now_y][now_x + 1] == 1 && v[now_y + 1][now_x] == 1)) {

				v[i][j] = 9;
				stop = true;
			}

			if (!stop) {
				if (i == 2 && j == 2) {
					v[i][j] = 9;
					now_y = i;
					now_x = j;
				}
				else if (num == 0) {
					if ((v[i][j - 1] == 9 && j == now_x + 1 && i == now_y)
						|| (v[i - 1][j] == 9 && i == now_y + 1 && j == now_x)) {
						v[i][j] = 9;
						now_y = i;
						now_x = j;
					}
				}
			}
		}
	}
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			cout << v[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}