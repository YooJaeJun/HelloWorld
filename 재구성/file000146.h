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
#define gridCheck() if (nx < 0 or nx >= n or ny < 0 or ny >= n) continue;

struct coord
{
	int x, y, dist;
	bool operator<(const coord& other) const
	{
		return dist < other.dist;
	}
};

void solution()
{
	int n, m;
	cin >> n >> m;
	vector<coord> nodes(n + 1);
	forn(i, m)
	{
		int s, e, d;
		cin >> s >> e >> d;
		nodes[s].push_back({ d, e });
	}

	auto dijk = [&]()
	{
		priority_queue<
	};
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--) solution();
	return 0;
}