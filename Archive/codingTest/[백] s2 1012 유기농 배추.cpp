#include <iostream>
using namespace std;

const int dx[4] = { 0, -1, 0, 1 };
const int dy[4] = { -1, 0, 1, 0 };

int cabbage[50][50];
int n, m, cnt;

void dfs(int x, int y) {
	cabbage[x][y] = false;

	for (int i = 0; i != 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (0 <= nx && nx < m &&
			0 <= ny && ny < n &&
			cabbage[nx][ny]) {
			dfs(nx, ny);
		}
	}
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int k;
		cin >> m >> n >> k;
		cnt = 0;
		while (k--) {
			int x, y;
			cin >> x >> y;
			cabbage[x][y] = 1;
		}
		for (int x = 0; x != m; x++) {
			for (int y = 0; y != n; y++) {
				if (cabbage[x][y]) {
					cnt++;
					dfs(x, y);
				}
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}



/*
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> visited;
vector<vector<int>> nodes;
vector<vector<int>> cabbage;
int cnt;

void bfs(int start) {
	queue<int> q;
	q.push(start);
	while (false == q.empty()) {
		int idx = q.front();
		q.pop();
		visited[idx] = 1;
		for (auto& elem : nodes[idx]) {
			if (visited[elem] != 1) {
				q.push(elem);
				visited[elem] = 1;
			}
		}
	}
}

int main() {
	int t, m, n, k;
	cin >> t;
	while (t--) {
		cnt = 0;
		cin >> m >> n >> k;
		// {0, 0}부터..
		visited.clear();
		nodes.clear();
		cabbage.clear();

		visited.resize(n * m);
		nodes.resize(n * m);
		for (int i = 0; i != n * m; i++) {
			visited[i] = 0;
		}
		cabbage.resize(n);
		for (int y = 0; y != n; y++) {
			cabbage[y].resize(m);
		}

		// 연결
		for (int i = 0; i != k; i++) {
			int x, y;
			cin >> x >> y;
			cabbage[y][x] = 1;
		}

		// 좌우상하 연결 검사
		for (int y = 0; y != n; y++) {
			for (int x = 0; x != m; x++) {
				if (cabbage[y][x] == 1) {
					// 좌
					if (x > 0 && cabbage[y][x - 1] == 1) {
						nodes[x + y * m].push_back(x + y * m - 1);
						nodes[x + y * m - 1].push_back(x + y * m);
					}
					// 우
					if (x < m - 1 && cabbage[y][x + 1] == 1) {
						nodes[x + y * m].push_back(x + y * m + 1);
						nodes[x + y * m + 1].push_back(x + y * m);
					}
					// 상
					if (y > 0 && cabbage[y - 1][x] == 1) {
						nodes[x + y * m].push_back(x + (y - 1) * m);
						nodes[x + (y - 1) * m].push_back(x + y * m);
					}
					// 하
					if (y < n - 1 && cabbage[y + 1][x] == 1) {
						nodes[x + y * m].push_back(x + (y + 1) * m);
						nodes[x + (y + 1) * m].push_back(x + y * m);
					}
				}
			}
		}
		for (int y = 0; y != n; y++) {
			for (int x = 0; x != m; x++) {
				if (cabbage[y][x] == 1 && visited[x + y * m] == 0) {
					bfs(x + y * m);
					cnt++;
				}
			}
		}
		printf("%d\n", cnt);
	}
	return 0;
}
*/