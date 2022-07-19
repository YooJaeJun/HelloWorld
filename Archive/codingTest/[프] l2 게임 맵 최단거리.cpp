#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int solution(vector<vector<int>> maps) {
    const int dy[4] = { 1,0,-1,0 };
    const int dx[4] = { 0,1,0,-1 };
    const int m = maps.size();
    const int n = maps[0].size();

    vector<vector<int>> visited(m + 1, vector<int>(n + 1, 0));
    vector<vector<int>> dist(m + 1, vector<int>(n + 1, 0));

    queue<pair<int, int>> q;
    visited[1][1] = 1;
    dist[1][1] = 1;
    q.push(make_pair(1, 1));

    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();

        for (int i = 0; i != 4; i++) {
            int ny = y + dy[i];    //n = next
            int nx = x + dx[i];

            if (0 < nx && nx <= n && 0 < ny && ny <= m) {
                if (maps[ny - 1][nx - 1] && !visited[ny][nx]) {
                    dist[ny][nx] = dist[y][x] + 1;
                    if (ny == m && nx == n) {
                        return dist[ny][nx];
                    }
                    visited[ny][nx] = 1;
                    q.push(make_pair(ny, nx));
                }
            }
        }
    }
    return -1;
}

void main() {
    printf("%d", solution({ {1, 0, 1, 1, 1}, {1, 0, 1, 0, 1}, {1, 0, 1, 1, 1}, {1, 1, 1, 0, 1}, {0, 0, 0, 0, 1} }));
}


//효율성 틀린 풀이
/*
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<vector<int>> nodes;
int m, n;

int bfs(const int& from, const int& to) {
    vector<int> dist(nodes.size(), 0); //안 들른 곳 0
    queue<int> q;
    dist[from] = 1; //들른 곳 1
    q.push(from);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();

        for (const auto& elem : nodes[curr]) {
            int next = elem;
            if (dist[next] == 0) {
                dist[next] = dist[curr] + 1;
                if (next == to) return dist[next];
                q.push(next);
            }
        }
    }
    return -1;
}

int solution(vector<vector<int>> maps) {
    m = maps.size();
    n = maps[0].size();
    nodes.resize(m * n + 1);
    //처음, 끝 노드 막혀있으면 -1
    if ((maps[0][1] == 0 && maps[1][0] == 0)
        || (maps[m - 1][n - 2] == 0 && maps[m - 2][n - 1] == 0)) {
        return -1;
    }
    //노드 연결
    for (int y = 0; y != m; y++) {
        for (int x = 0; x != n; x++) {
            int curr = y * n + x + 1;
            if (x < n - 1 && maps[y][x] && maps[y][x + 1]) {
                nodes[curr].push_back(curr + 1);
                nodes[curr + 1].push_back(curr);
            }
            if (y < m - 1 && maps[y][x] && maps[y + 1][x]) {
                nodes[curr].push_back(curr + n);
                nodes[curr + n].push_back(curr);
            }
        }
    }
    int answer = bfs(1, m * n);
    return answer;
}

*/