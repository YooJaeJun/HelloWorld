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


int n;
int dx[4] = { 0,0,-1,1 };	// 좌우상하
int dy[4] = { -1,1,0,0 };
int ans = 0;
vi limit;	// 뎁스별 제한값
ddb already;
vvi curBoard;

bool isValid(int x, int y)
{
	return x >= 0 && x < n&& y >= 0 && y < n;
}

void goBack(vvi& curBoard, int x, int y, int nx, int ny, int i)
{
	nx -= dx[i];
	ny -= dy[i];
	if (curBoard[nx][ny] == 0)
	{
		curBoard[nx][ny] = curBoard[x][y];
		curBoard[x][y] = 0;
	}
}

void dfs(vvi& board, int depth)
{
	// cout << '\n'; forn(i, n) { forn(j, n) { cout << board[i][j] << ' '; } cout << '\n'; } cout << '\n';

	if (depth == 10)
		return;

	for (int i = 0; i < 4; ++i)
	{
		for (int x = 0; x < n; x++)
			for (int y = 0; y < n; y++)
				curBoard[x][y] = board[x][y];

		forn(i, n) fill(already[i].begin(), already[i].end(), false);	// 한 번 합쳐졌었나
		bool moved = false;	// 안 움직였으면 dfs no

		// 좌0 우1 상2 하3. sx == startX, ex == endX, cx == coefX ...
		int sx = 0, sy = 0, ex = n, ey = n, cx = 1, cy = 1;
		if (i == 1) sx = 0, sy = n - 1, ex = n, ey = -1, cx = 1, cy = -1;
		else if (i == 3) sx = n - 1, sy = 0, ex = -1, ey = n, cx = -1, cy = 1;

		for (int x = sx; x != ex; x += cx)
		{
			for (int y = sy; y != ey; y += cy)
			{
				if (curBoard[x][y] == 0) continue;
				if (already[x][y]) continue;

				int nx = x + dx[i];
				int ny = y + dy[i];
				while (1)
				{
					if (isValid(nx, ny) == false)
					{
						goBack(curBoard, x, y, nx, ny, i);
						break;
					}
					if (curBoard[nx][ny] != 0)
					{
						if (already[nx][ny] ||
							(curBoard[nx][ny] != curBoard[x][y]))
						{
							goBack(curBoard, x, y, nx, ny, i);
						}
						else
						{
							curBoard[nx][ny] *= 2;
							curBoard[x][y] = 0;
							already[nx][ny] = true;
							moved = true;
						}
						break;
					}
					nx += dx[i];
					ny += dy[i];
					moved = true;
				}
			}
		}

		int curMax = 0;
		for (int x = 0; x < n; x++)
			for (int y = 0; y < n; y++)
				curMax = max(curMax, curBoard[x][y]);
		// 최적화
		if (limit[depth] < curMax)
		{
			if (ans < curMax) ans = curMax;
			limit[depth] = curMax;
			if (depth < 9)
				for (int i = depth + 1; i > 0; i--)
					limit[i - 1] = limit[i] / 2;
		}

		if (moved)
			if (depth == 9 || curMax > limit[depth])
				dfs(curBoard, depth + 1);
	}
}

void solution() {
	cin >> n;
	vvi board(n, vi(n));
	limit = vi(11);
	already = ddb(n, db(n));
	curBoard = vvi(n, vi(n));

	for (int i = 0; i != n; i++)
		for (int j = 0; j != n; j++)
			cin >> board[i][j];

	dfs(board, 0);
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