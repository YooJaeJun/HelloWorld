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
	auto brute = [&](string& src, string& search) ->vi
	{
		vi ret;
		// ���� ���ڿ��� ó������ ������ Ž��
		for (int begin = 0; begin + search.size() <= src.size(); begin++)
		{
			bool matched = true;
			// Ž���� ���ڿ��� ���� ���ڿ��� ��
			forn(i, search.size())
			{
				// ����ġ �߻�
				if (src[begin + i] != search[i])
				{
					matched = false;
					break;
				}
			}
			// Ž���� ���ڿ��� ���� ���ڿ��� ��ġ
			if (matched) ret.push_back(begin);
		}
		return ret;
	};

	auto kmp = [&](string& src, string& search) ->vi
	{
		int n = src.size(), m = search.size();
		vi ret;
		// Ž���� ���ڿ��� ���λ�, ���̻� ���̸� ���ڿ��� ó������ ������ �̸� ���
		vi pi = getPartialMatch(search);
		int begin = 0, matched = 0;
		while (begin <= n - m)
		{
			// Ž���� ���ڿ��� ���� ���ڿ����� ���� ��ġ�� ���ڰ� ������ ���
			if (matched < m and src[begin + matched] == search[matched])
			{
				matched++;
				// ���ڿ��� ��� ��ġ�ϴ� ���
				if (matched == m)
					ret.push_back(begin);
			}
		}
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