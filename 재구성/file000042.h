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
		// 원본 문자열의 처음부터 끝까지 탐색
		for (int begin = 0; begin + search.size() <= src.size(); begin++)
		{
			bool matched = true;
			// 탐색할 문자열과 원본 문자열을 비교
			forn(i, search.size())
			{
				// 불일치 발생
				if (src[begin + i] != search[i])
				{
					matched = false;
					break;
				}
			}
			// 탐색할 문자열과 원본 문자열이 일치
			if (matched) ret.push_back(begin);
		}
		return ret;
	};

	auto kmp = [&](string& src, string& search) ->vi
	{
		int n = src.size(), m = search.size();
		vi ret;
		// 탐색할 문자열의 접두사, 접미사 길이를 문자열의 처음부터 끝까지 미리 계산
		vi pi = getPartialMatch(search);
		int begin = 0, matched = 0;
		while (begin <= n - m)
		{
			// 탐색할 문자열과 원본 문자열에서 현재 위치의 문자가 동일한 경우
			if (matched < m and src[begin + matched] == search[matched])
			{
				matched++;
				// 문자열이 모두 일치하는 경우
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