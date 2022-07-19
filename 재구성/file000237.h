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

struct unit { int x, y; };

enum eGrid { empty, wall, player };

void solution()
{
	const int n = 8;
	unit player;
	unit wall;
	vector<string> grid(n);
	vector<unit> walls;
	forn(i, n)
	{
		cin >> grid[i];
		forn(j, n)
		{
			if (grid[i][j] == '#') walls.push_back({ i, j });
		}
	}
	
	grid[7][0] = eGrid::player;

	int ans = 1;
	auto bfs = [&]()
	{
		queue<unit>
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