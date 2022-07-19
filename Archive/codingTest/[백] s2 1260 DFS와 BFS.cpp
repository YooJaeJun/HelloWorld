#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> visited;
vector<vector<int>> nodes;

void initVisited() {
	for (auto& elem : visited) {
		elem = 0;
	}
}

void dfs(int v) {
	visited[v] = true;
	printf("%d ", v);
	for (auto& elem : nodes[v]) {
		if (visited[elem] == false) {
			dfs(elem);
		}
	}
}

void bfs(int v) {
	visited[v] = true;
	queue<int> q;
	q.push(v);
	while (false == q.empty()) {
		int w = q.front();
		q.pop();
		printf("%d ", w);
		for (auto& elem : nodes[w]) {
			if (visited[elem] == false) {
				visited[elem] = true;
				q.push(elem);
			}
		}
	}
	
}

int main() {
	int n, m, v;
	cin >> n >> m >> v;
	visited.resize(n + 1);
	nodes.resize(n + 1);
	for (int i = 1; i <= m; i++) {
		int n1, n2;
		cin >> n1 >> n2;
		nodes[n1].push_back(n2);
		nodes[n2].push_back(n1);
	}
	for (auto& elem : nodes) {
		sort(elem.begin(), elem.end());
	}
	dfs(v);
	initVisited();
	puts("");
	bfs(v);

	return 0;
}





// �� ���ſ� Ǯ���� ��... �� �����ϰ� Ǯ����
/*
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

//�����Լ� ���ְ� �������ڷ�..
void dfs(vector<vector<int>>& a, const int& size, const int& x, vector<bool>& checked) {	//�� ��� ȣ�⿡�� x == start
	if (checked[x]) return;	//��� �湮�ߴٸ� ����
	checked[x] = true;
	printf("%d ", x);
	if (a[x].size() < 1) { return; }
	for (int i = 0; i < a[x].size(); ++i) {
		long unsigned int y = a[x][i];	//vector<int>::size_type�� ���Ŷ� ��
		dfs(a, size, y, checked);	//���
	}
}
void bfs(vector<vector<int>>& a, const int& size, const int& start, vector<bool>& checked) {
	queue<int> q;
	q.push(start);
	checked[start] = true;
	while (!q.empty()) {
		long unsigned int x = q.front();
		q.pop();
		printf("%d ", x);
		if (a[x].size() < 1) { return; }
		for (int i = 0; i < a[x].size(); ++i) {
			long unsigned int y = a[x][i];	//��� �ȿ� ����� ������ �������
			if (!checked[y]) {	//�� ��� �˻� �� �ߴ� �Ÿ�
				q.push(y);
				checked[y] = true;
			}
		}
	}
}
int main() {
	int size, total, start;
	scanf("%d %d %d", &size, &total, &start);
	vector<vector<int>> a;
	a.resize(size + 1);
	int n1, n2;
	if (total == 0) { return -1; }
	for (int i = 0; i != total; ++i) {
		scanf("%d %d", &n1, &n2);
		a[n1].push_back(n2);
		a[n2].push_back(n1);
	}
	for (int i = 1; i <= size; ++i) {	//�����ͺ��� �����϶� į
		if (a[i].begin() != a[i].end()) {
			sort(a[i].begin(), a[i].end());
		}
	}
	vector<bool> checked;
	checked.resize(size + 1);
	dfs(a, size, start, checked);
	checked = { false };
	checked.resize(size + 1);	//���� ��Ȱ��
	puts("");
	bfs(a, size, start, checked);

	return 0;
}
*/