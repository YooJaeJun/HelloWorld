#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int N, M, hx, hy, ex, ey;
int arr[1001][1001];
int visit[1001][1001][2];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

int bfs() {
	queue <pair<pair<long, long>, long>> q;
	q.push({ {hx,hy},1 });
	visit[hx][hy][1] = 1;

	while (!q.empty()) {
		int x = q.front().first.first;
		int y = q.front().first.second;
		int block = q.front().second;
		q.pop();

		if (x == ex && y == ey) return visit[x][y][block];

		for (int i = 0; i < 4; i++) {
			int xx = x + dir[i][0];
			int yy = y + dir[i][1];

			if (1 <= xx && xx <= N && 0 <= yy && yy <= M) {
				if (arr[xx][yy] == 1 && block) {
					visit[xx][yy][block - 1] = visit[x][y][block] + 1;
					q.push({ {xx,yy},block - 1 });
				}
				else if (arr[xx][yy] == 0 && visit[xx][yy][block] == 0) {
					visit[xx][yy][block] = visit[x][y][block] + 1;
					q.push({ {xx,yy},block });
				}
			}
		}
	}
	return -1;
}

int main() {
	cin >> N >> M >> hx >> hy >> ex >> ey;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= M; j++) {
			cin >> arr[i][j];
		}
	}
	cout << bfs() - 1 << endl;
	return 0;
}