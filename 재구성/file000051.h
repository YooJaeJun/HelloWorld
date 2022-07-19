#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vvvi = vector<vector<vector<int>>>;
using db = deque<bool>;
using ddb = deque<deque<bool>>;
#define yes cout << "YES\n";
#define no cout << "NO\n";
#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define forn1(i, n) for (int i = 1; i <= (int)n; i++)
const int maxn = 1e9 + 7;
const double mod = 1e9 + 7;

struct coord { int x, y, breaking, distance; };

void solution()
{
	int n, m;
	cin >> n >> m;
	vvi grid(n, vi(m));
	int hx, hy, ex, ey;
	cin >> hx >> hy >> ex >> ey;
	forn(i, n) forn(j, n) cin >> grid[i][j];
	vvvi dist(n, vvi(m, vi(2, maxn)));

	int ans = maxn;
	auto bfs = [&]()
	{
		int dx[4] = { 0,0,1,-1 };
		int dy[4] = { 1,-1,0,0 };

		queue<coord> q;
		q.push({ 0,0,0 });
		dist[0][0][0] = 1;

		while (q.empty() == false)
		{
			int x = q.front().x;
			int y = q.front().y;
			int breaking = q.front().breaking;
			int distance = q.front().distance;
			q.pop();

			forn(i, 4)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx < 0 or nx >= n or ny < 0 or ny >= m) continue;

				if (x == n - 1 and y == m - 1)
				{
					ans = min(ans, dist[x][y][breaking]);
					continue;
				}

				if (dist[nx][ny][breaking] <= distance) continue;

				if (grid[nx][ny] == 1)
				{
					if (breaking >= 1) continue;
					dist[nx][ny][breaking + 1] = dist[x][y][breaking] + 1;
					q.push({ nx, ny, breaking + 1, distance + 1 });
				}
				else
				{
					dist[nx][ny][breaking] = dist[x][y][breaking] + 1;
					q.push({ nx, ny, breaking, distance + 1 });
				}

			}
		}
	};
	bfs();

	cout << '\n'; forn(i, n) { forn(j, m) { cout << dist[i][j][0] << ' '; } cout << '\n'; } cout << '\n';
	cout << '\n'; forn(i, n) { forn(j, m) { cout << dist[i][j][1] << ' '; } cout << '\n'; } cout << '\n';

	cout << (ans == maxn ? -1 : ans - 1);
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--) solution();
	return 0;
}