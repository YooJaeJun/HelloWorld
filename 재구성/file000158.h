#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
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
	forn(i, n) forn(j, n) cin >> grid[i][j];

	int ans = maxn;
	auto bfs = [&]()
	{
		int dx[4] = { 0,0,1,-1 };
		int dy[4] = { 1,-1,0,0 };

		ddb memo(n, db(m, maxn));
		queue<coord> q;
		q.push({ 0,0,0 });
		while (q.empty() == false)
		{
			int x = q.front().x;
			int y = q.front().y;
			int breaking = q.front().breaking;
			q.pop();

			forn(i, 4)
			{
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx < 0 or nx >= n or ny < 0 or ny >= m) continue;
				if (memo[nx][ny])
				if (grid[nx][ny] == 1)
				{

				}
			}
		}
	};
	bfs();

	cout << ans;
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--) solution();
	return 0;
}