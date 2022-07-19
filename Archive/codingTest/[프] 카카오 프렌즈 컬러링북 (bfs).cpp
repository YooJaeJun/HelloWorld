#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

void bfs(const int& start, vector<vector<int>>& nodes, vector<int>& areas, vector<bool>& checked) {
	queue<int> q;
	q.push(start);
	checked[start] = true;
	areas.push_back(1);	//�� ���� ���� 1����
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < nodes[x].size(); ++i) {
			long unsigned int y = nodes[x][i];	//��� ���� ����� ����
			if (!checked[y]) {
				q.push(y);
				checked[y] = true;
				areas.back()++;
			}
		}
	}
}
// ���� ������ ������ ��� �Լ� ���� �ʱ�ȭ �ڵ带 �� �ۼ����ּ���.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	vector<vector<int>> nodes;
	vector<int> areas;
	vector<bool> checked;
	vector<vector<int>> piccopy;
	nodes.resize(m * n + 1);
	for (int y = 0; y != m; y++) {	//��忡 ����� ���� �ֱ�
		for (int x = 0; x != n; x++) {
			if (x < n - 1 && picture[y][x] != 0 && picture[y][x] == picture[y][x + 1]) {
				nodes[y * n + x + 1].push_back(y * n + x + 2);
				nodes[y * n + x + 2].push_back(y * n + x + 1);
			}
			if (y < m - 1 && picture[y][x] != 0 && picture[y][x] == picture[y + 1][x]) {
				nodes[y * n + x + 1].push_back(y * n + x + 1 + n);
				nodes[y * n + x + 1 + n].push_back(y * n + x + 1);
			}
		}
	}
	piccopy = picture;	//picture ������ �ǵ帮�� �ȵȴٰ� ��.
	checked.resize(m * n + 1, false);
	int start;
	int idx = 0;
	for (int y = 0; y != m; y++) {	//
		for (int x = 0; x != n; x++) {
			if (!checked[y * n + x + 1] && piccopy[y][x] != 0) {
				start = y * n + x + 1;
				bfs(start, nodes, areas, checked);	//bfs
			}
			if (checked[y * n + x + 1]) {
				piccopy[y][x] = 0;	//üũ������ picture�� 0�� ���� ó��
			}
		}
	}
	int number_of_area = areas.size();
	int max_size_of_one_area = *max_element(areas.begin(), areas.end());
	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
	return answer;
}

int main() {
	vector<int> ans = solution(6, 4, { {1, 1, 1, 0}, {1, 2, 2, 0}, {1, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 3}, {0, 0, 0, 3} });
	std::cout << ans[0] << " " << ans[1] << endl;
	ans = solution(6, 4, { { 1, 0, 0, 1 }, { 1, 0, 0, 1 }, { 1, 0, 0, 1 }, { 1, 0, 0, 1 }, { 1, 0, 0, 1 }, { 1, 1, 1, 1 } });
	std::cout << ans[0] << " " << ans[1] << endl;
	ans = solution(4, 4, { { 1, 1, 1, 1 }, { 1, 4, 1, 1 }, { 1, 3, 2, 1 }, { 1, 1, 1, 1 } });
	std::cout << ans[0] << " " << ans[1] << endl;
	ans = solution(2, 2, { { 1, 1 }, { 0, 1 } });
	std::cout << ans[0] << " " << ans[1] << endl;
	ans = solution(13, 16, {
	{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,2,1,1,1,1,2,1,1,1,1,0},
	{0,1,1,1,2,1,2,1,1,2,1,2,1,1,1,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{0,1,3,3,3,1,1,1,1,1,1,3,3,3,1,0},
	{0,1,1,1,1,1,3,1,1,3,1,1,1,1,1,0},
	{0,0,1,1,1,1,1,3,3,1,1,1,1,1,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0}
		});
	std::cout << ans[0] << " " << ans[1] << endl;
}