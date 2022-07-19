#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int nodes[51][51];
bool visited[51][51];
int n, m;
int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
int maxCnt;
bool infinity = false;

void dfs(int x, int y, int count) {
	if (infinity) {
		return;
	}
	for (int i = 0; i != 4; i++) {
		int nx = x + dx[i] * nodes[x][y];
		int ny = y + dy[i] * nodes[x][y];
		if (nx >= 1 && nx <= n &&
			ny >= 1 && ny <= m &&
			nodes[nx][ny] != 24/*'H'*/ &&
			visited[nx][ny] == false) {
			visited[nx][ny] = true;
			dfs(nx, ny, count + 1);
		}
		else if (visited[nx][ny] == true) {
			infinity = true;
			return;
		}
		else {
			if (maxCnt < count) {
				maxCnt = count;
			}
		}
	}
}

int main() {
	cin >> n >> m;
	for (int x = 1; x <= n; x++) {
		string s;
		cin >> s;
		for (int y = 0; y < m; y++) {
			nodes[x][y + 1] = s[y] - '0';
		}
	}
	if (nodes[1][1] == 24/*'H'*/) {
		printf("-1");
		return 0;
	}
	dfs(1, 1, 1);
	int ans = infinity ? -1 : maxCnt;
	cout << ans;
	return 0;
}