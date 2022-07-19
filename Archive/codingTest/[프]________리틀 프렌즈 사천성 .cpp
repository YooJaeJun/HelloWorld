#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<string> nodes;
vector<vector<bool>> visited;
int dx[4];
int dy[4];
int turn;
int m_, n_;
char deleteChar;
string answer;

void bfs(int x, int y) {
    int origin_x = x;
    int origin_y = y;
    int beforeX = -1;
    int beforeY = -1;
    visited[x][y] = true;
    queue<vector<int>> q;   // x, y, (turn체크용)before_x, before_y
    q.push({ x, y, beforeX, beforeY });
    while (false == q.empty()) {
        x = q.front()[0];
        y = q.front()[1];
        beforeX = q.front()[2];
        beforeY = q.front()[3];
        q.pop();
        for (int i = 0; i != 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < m_ &&
                ny >= 0 && ny < n_ &&
                visited[nx][ny] == false) {

                visited[nx][ny] = true;

                if (nodes[nx][ny] == '.') {
                    if (nx != beforeX && ny != beforeY) {
                        turn++;
                    }
                    if (turn >= 2) {
                        turn = 0;
                        while (false == q.empty()) {
                            q.pop();
                        }
                        break;
                    }
                    else if (nodes[x][y] != '*') {
                        q.push({ nx, ny, x, y });
                    }
                }
                else if (nodes[nx][ny] == nodes[origin_x][origin_y]) {

                    deleteChar = nodes[nx][ny];
                    answer += nodes[nx][ny];
                    nodes[origin_x][origin_y] = '.';
                    nodes[nx][ny] = '.';
                    while (false == q.empty()) {
                        q.pop();
                    }
                    break;
                }
            }

        }
    }
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
string solution(int m, int n, vector<string> board) {
    // 초기화
    nodes = board;  // 전역으로 쓰기 위해
    m_ = m;
    n_ = n;
    dx[0] = { 0 };  dx[1] = { 0 }; dx[2] = { -1 }; dx[3] = { 1 };
    dy[0] = { 1 };  dy[1] = { -1 }; dy[2] = { 0 }; dy[3] = { 0 };
    turn = 0;
    visited.resize(m);
    for (auto& elem : visited) {
        elem.resize(n);
    }
    // 문자 정렬
    vector<char> range;
    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            if (nodes[x][y] != '.' &&
                nodes[x][y] != '*') {
                range.push_back(nodes[x][y]);
            }
        }
    }
    sort(range.begin(), range.end());
    range.erase(unique(range.begin(), range.end()), range.end());

    // 반복
    deleteChar == ']';  // 최초
    while (deleteChar != '~') { // 지워진 문자가 있으면 다시 반복
        // 정렬된 문자
        deleteChar = '~';
        int idx = 0;

        for (int x = 0; x < m; x++) {
            for (int y = 0; y < n; y++) {
                // 방문 초기화
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        visited[i][j] = 0;
                    }
                }
                // 정렬된 것부터 검사
                if (range.empty() == false &&
                    idx < range.size() &&
                    range[idx] == nodes[x][y]) {
                    bfs(x, y);

                    if (deleteChar == '~') {
                        idx++;
                    }
                    else {
                        auto it = find(range.begin(), range.end(), deleteChar);
                        if (it != range.end()) {
                            range.erase(it);
                        }
                        idx = 0;
                        deleteChar = '~';
                    }
                    x = 0;
                    y = 0;
                }
            }
        }
    }
    return answer != "" ? answer : "IMPOSSIBLE";
}


int main() {
    cout << solution(3, 3, { "A.B", "B.A", "C.C" });
    return 0;
}
