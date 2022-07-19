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

struct tagShark { int r, c, s, d, z, state; };
enum eState { alive, die };

void solution()
{
	int r, c, m;
	cin >> r >> c >> m;
	vector<tagShark> sharks;
	vvi grid(r, vi(c, -1));	// shark index

	forn(i, m)
	{
		cin >> sharks[i].r >> sharks[i].c >> sharks[i].s >> sharks[i].d >> sharks[i].z;
		sharks[i].s = (sharks[i].d == 1 or sharks[i].d == 2 ?
				sharks[i].s % ((r - 1) * 2) :
				sharks[i].s % ((c - 1) * 2));
		sharks[i].state = alive;
		grid[sharks[i].r][sharks[i].c] = i;
	}


	int ans = 0;
	int fisherPos = 0;

	while (++fisherPos <= c)
	{
		// 낚시꾼
		forn(row, r)
		{
			int& sharkIdx = grid[row][fisherPos];
			if (sharkIdx != -1)
			{
				ans += sharks[sharkIdx].z;
				sharkIdx = -1;
				sharks[sharkIdx].state = die;
				break;
			}
		}
		// 상어
		int idx = 0;
		for (auto& shark : sharks)
		{
			if (shark.state == die) continue;
			// 이동
			grid[shark.r][shark.c] = -1;
			if (shark.d == 1)
			{
				shark.r -= shark.s;
				shark.r = shark.r < 0 ? shark.r + (r - 1) : shark.r;
				shark.d = 2;
				if (shark.r < 0)	// 방향 한 번 더 바뀌는 경우
				{
					shark.r += (r - 1);
					shark.d = 1;
				}
			}
			else if (shark.d == 2)
			{
				shark.r += shark.s;
				shark.r = shark.r > r - 1 ? shark.r - (r - 1) : shark.r;
				shark.d = 1; 
				if (shark.r > r - 1)
				{
					shark.r -= (r - 1);
					shark.d = 2;
				}
			}
			else if (shark.d == 3)
			{
				shark.c += shark.s;
				shark.c = shark.c > c - 1 ? shark.c - (c - 1) : shark.c;
				shark.d = 4;
				if (shark.c > c - 1)
				{
					shark.c -= (c - 1);
					shark.d = 3;
				}
			}
			else if (shark.d == 4)
			{
				shark.c -= shark.s;
				shark.c = shark.c < 0 ? shark.c + (c - 1) : shark.c;
				shark.d = 3;
				if (shark.c < 0)
				{
					shark.c += (c - 1);
					shark.d = 4;
				}
			}
			int& beforeSharkIdx = grid[shark.r][shark.c];
			if (beforeSharkIdx != -1)
			{
				if (sharks[beforeSharkIdx].z > shark.z) shark.state = die;
				else
				{
					beforeSharkIdx = shark.z;
					sharks[beforeSharkIdx].state = die;
				}
			}
			else grid[shark.r][shark.c] = idx;
			idx++;
		}
	}
}

int32_t main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) solution();
	return 0;
}