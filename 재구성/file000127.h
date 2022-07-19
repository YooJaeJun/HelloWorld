#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
#define yes cout << "YES\n";
#define no cout << "NO\n";
const int maxn = 100001;
const double mod = 1e9 + 7;


void solution()
{
	int n;
	cin >> n;
	vi s(n), p(n);
	for (int i = 0; i < n; i++)
	{
		cin >> s[i];
		p[i] = i + 1;
	}
	int l = 0, r = 0;
	bool ans = true;

	while (r < n)
	{
		while (r < n - 1 and s[r] == s[r + 1])
			++r;
		if (l == r)
			ans = false;
		else
			rotate(p.begin() + 1, p.begin() + r, p.begin() + r + 1);
		l = r + 1;
		++r;
	}
	if (ans)
	{
		for (auto& x : p)
			cout << x << ' ';
		cout << '\n';
	}
	else
		cout << -1 << '\n';
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}