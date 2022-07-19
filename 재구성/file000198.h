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
const int mod = 1000;


void solution()
{
	int n, m, k;
	cin >> n >> m >> k;
	vvi grid(n, vi(m));

	forn(i, n)
	{
		string s;
		cin >> s;
		for (int j = 0; j < m; j++) 
			grid[i][j] = (s[j] - '0');
	}
	vvvi dp = vvvi(n, vvi(m, vi(k)));

	int dx[4] = { 0,0,1,-1 };
	int dy[4] = { 1,-1,0,0 };
	int ans = 0;

	function<void(int, int, int)> dfs = [&](int x, int y, int breaking)
	{
		if (x == n - 1 and y == m - 1)
		{
			ans = max(ans, dp[x][y][breaking]);
			return;
		}

		for (int i = 0; i < 4; i++)
		{
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (dp[nx][ny][breaking]) continue;
			
			if (grid[nx][ny] == '1')
			{
				if (breaking + 1 > k) continue;
				
				dp[nx][ny][breaking + 1] = dp[nx][ny][breaking] + 1;
				dfs(nx, ny, breaking + 1);
			}
			else
			{
				dp[nx][ny][breaking] = dp[nx][ny][breaking] + 1;
				dfs(nx, ny, breaking);
			}
		}
	};
	dp[0][0][0] = true;
	dfs(0, 0, 0);

	cout << ans;
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}