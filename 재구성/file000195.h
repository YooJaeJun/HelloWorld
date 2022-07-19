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

struct coord { int x, y, breaking; };

void solution()
{
	int n, m;
	cin >> n >> m;
	vvi grid(n, vi(m));
	int hx, hy, ex, ey;
	cin >> hx >> hy >> ex >> ey;
	forn(i, n) forn(j, m) cin >> grid[i][j];
	vvvi dist(n, vvi(m, vi(2, maxn)));

	int ans = maxn;
	auto bfs = [&]()
	{
		int dx[4] = { 0,0,1,-1 };
		int dy[4] = { 1,-1,0,0 };

		deque<coord> dq;
		dq.push_back({ 0,0,0 });
		dist[0][0][0] = 1;

		while (dq.empty() == false)
		{
			int x = dq.front().x;
			int y = dq.front().y;
			int breaking = dq.front().breaking;
			dq.pop_front();

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

				if (x == 1 and y == 4 and nx == 1 and ny == 5)
					int s = 0;

				if (dist[nx][ny][breaking] != maxn)
				{
					if (dist[nx][ny][breaking] < dist[x][y][breaking] + 1) continue;
					else if (breaking == 1 and dist[nx][ny][breaking] < dist[x][y][breaking - 1] + 1) continue;
				}


				if (grid[nx][ny] == 1)
				{
					if (breaking >= 1) continue;
					dist[nx][ny][breaking + 1] = dist[x][y][breaking] + 1;
					dq.push_back({ nx, ny, breaking + 1 });
				}
				else
				{
					dist[nx][ny][breaking] = dist[x][y][breaking] + 1;
					dq.push_back({ nx, ny, breaking });
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