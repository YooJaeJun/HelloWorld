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
const int mod = 1000;

struct tagNodes
{
	int dist, end;
};

void solution()
{
	int n, m;
	cin >> n >> m;
	vector<vector<tagNodes>> nodes(n + 1);
	forn(i, n)
	{
		int start, end, distance;
		cin >> start >> end >> distance;
		nodes[start].push_back({ distance, end });
	}

	int start, end;
	cin >> start >> end;

	auto dijk = [&]()
	{
		priority_queue<tagNodes, vector<tagNodes>, greater<tagNodes>()> pq;

	};
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}