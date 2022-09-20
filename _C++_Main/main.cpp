#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using db = deque<bool>;
using ddb = deque<deque<bool>>;
#define forn(i, n) for (int i = 0; i < (int)n; i++)
#define forn1(i, n) for (int i = 1; i <= (int)n; i++)
#define inGrid() ((nr >= 0) and (nr < n) and (nc >= 0) and (nc < m))
int dr[4] = { 0,0,-1,1 };
int dc[4] = { -1,1,0,0 };	// ÁÂ¿ì»óÇÏ


void solution()
{
	struct Vector2 
	{ 
		float x, y; 
		Vector2(const float a, const float b) : x(a), y(b) {}
		bool operator<(const Vector2& other) const
		{
			return x < other.x&& y < other.y;
		}
	};
	map<Vector2, float> dic;
	dic.insert({ Vector2(1.5f, 2.5f), 1.0f });
	dic.insert({ Vector2(1.5f, 2.6f), 2.0f });




	map<pair<int, int>, vector<int>> m;
	m[{2, 3}].push_back(4);
	m[{2, 3}].push_back(5);

	return;
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--) solution();
	return 0;
}