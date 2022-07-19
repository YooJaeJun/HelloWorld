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


void solution()
{
	int n, newScore, p;
	cin >> n >> newScore >> p;
	vi score(n);
	forn(i, n) cin >> score[i];
	if (n == 0)
	{
		cout << 1;
		return;
	}
	int idx = lower_bound(score.rbegin(), score.rend(), newScore) - score.rbegin();
	idx = n - idx;
	int rank = idx + 1;	// 인덱스 1부터 시작 기준. 동점이어도 일단 밀어버림
	
	if (score[rank - 2] == newScore) rank--;		// 앞에 있는 게 동점이었으면 보정

	if (rank > p) cout << -1;
	else cout << rank;
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--) solution();
	return 0;
}