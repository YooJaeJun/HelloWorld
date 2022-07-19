#include <bits/stdc++.h>
using namespace std;

int history = 1e9;

struct node
{
    int cur, cnt;
    vector<bool> visited;
};

int findCnt(char ch)
{
    return min(ch - 'A', 'Z' - ch + 1);
}

bool check(vector<bool>& visited, string& name, int& nCnt)
{
    bool flag = true;
    for (int i = 0; i < name.size(); ++i)
    {
        if (visited[i] == false && name[i] != 'A')
            flag = false;
    }
    if (flag)
        int a = 2;
    return flag;
}

void bfs(string& name)
{
    string initS;
    for (auto& elem : name)
    {
        initS += 'A';
    }
    vector<bool> visited(20);
    visited[0] = true;
    queue<node> q;
    q.push({ 0, 0, visited });

    while (q.empty() == false)
    {
        int cur = q.front().cur;
        int cnt = q.front().cnt;
        vector<bool> visited(20);
        visited = q.front().visited;
        q.pop();

        int nCnt = cnt + findCnt(name[cur]);
        if (check(visited, name, nCnt))
        {
            visited = min(visited, nCnt);
            return;
        }

        // 0번은 첨에 이미 들러서 되돌아갈 필요 없음
        if (cur + 1 < (int)name.size())
        {
            bool alreadyTrue = false;
            if (visited[cur + 1]) alreadyTrue = true;
            visited[cur + 1] = true;

            q.push({ cur + 1, nCnt + 1, visited });

            if (alreadyTrue == false) visited[cur + 1] = false;

        }
        // 0->마지막
        if (cur == 0)
        {
            bool alreadyTrue = false;
            if (visited[name.size() - 1]) alreadyTrue = true;
            visited[name.size() - 1] = true;

            q.push({ (int)name.size() - 1, nCnt + 1, visited });

            if (alreadyTrue == false) visited[name.size() - 1] = false;
        }
        else
        {
            bool alreadyTrue = false;
            if (visited[cur - 1]) alreadyTrue = true;
            visited[cur - 1] = true;

            q.push({ cur - 1, nCnt + 1, visited });

            if (alreadyTrue == false) visited[cur - 1] = false;
        }
    }
}

int solution(string name) {
    bfs(name);
    return history;
}

int main()
{
    cout << solution("AZAAAZ");
}