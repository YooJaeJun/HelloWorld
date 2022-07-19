#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vc = vector<char>;
using vvc = vector<vector<char>>;


struct coord
{
	int x, y;
};

int n, m;
vvc grid;
vector<coord> robotsOrigin;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,1,0,0 };
bool ansFlag = false;

void dfs(vector<coord> robots, vvi visited)
{
	for (int i = 0; i < 4; i++)
	{
		for (auto& robot : robots)
		{
			robot.x += dx[i];
			robot.y += dy[i];
			if (robot.x < 0 || robot.x >= n || robot.y < 0 || robot.y >= m) return;
		}

		for (auto& robot : robots)
		{
			if (robot.x == 0 && robot.y == 0)
			{
				ansFlag = true;
				return;
			}
			if (visited[robot.x][robot.y]) return;
			visited[robot.x][robot.y] = true;
		}

		dfs(robots, visited);

		if (ansFlag)
			return;

		for (auto& robot : robots)
		{
			visited[robot.x][robot.y] = false;
		}

	}
}

void solution()
{
	cin >> n >> m;
	grid = vvc(n, vc(m));
	vvi visited(n, vi(m));
	for (int i = 0; i != n; i++)
	{
		for (int j = 0; j != m; j++)
		{
			cin >> grid[i][j];
			if (grid[i][j] == 'R')
			{
				if (i == 0 && j == 0)
				{
					cout << "YES" << '\n';
					return;
				}
				robotsOrigin.push_back({ i, j });
			}
		}
	}

	dfs(robotsOrigin, visited);

	if (ansFlag) cout << "YES" << '\n';
	else cout << "NO" << '\n';

	robotsOrigin.clear();
	ansFlag = false;
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	cin >> t;
	for (int i = 0; i != t; i++) { solution(); }
	return 0;
}