#include <vector>
#include <map>
using namespace std;

// ���� ������ ������ ��� �Լ� ���� �ʱ�ȭ �ڵ带 �� �ۼ����ּ���.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	multimap<int, int> areas;	//���� ���� picture[i][j], ���� ����
	multimap<int, int>::iterator final_it_for_overlap;
	bool is_primary;
	for (int i = 0; i != m; i++) {
		for (int j = 0; j != n; j++) {
			is_primary = false;
			//0�̸� �Ǵܾ���
			if (picture[i][j] == 0) {
				continue;
			}
			//Ű �ߺ��� ���� �ش� Ű�� ������ �� �ҷ����� (upper_bound()�� ������ ���Ұ� �ƴ� ������ ���� ���Ҹ� ����Ű�� ������ �ٷ� �� ��)
			for (auto it = areas.lower_bound(picture[i][j]); it != areas.upper_bound(picture[i][j]); it++) {
				if (it != areas.end()) {
					final_it_for_overlap = it;
				}
			}
			//��, ��� ���ҷ� ���� �Ǵ�
			if (i > 0 && (picture[i][j] == picture[i - 1][j]) || (j > 0 && (picture[i][j] == picture[i][j - 1]))) {
				is_primary = true;
				areas.insert(make_pair(picture[i][j], 1));
			}
			//���� ���ҷ� ���Ӽ� �Ǵ�
			if (is_primary || i < m - 1 && (picture[i][j] == picture[i + 1][j]) || (j < n - 1 && (picture[i][j] == picture[i][j + 1]))) {
				final_it_for_overlap->second++;
			}
			//���Ӽ� ������ ���� �߰�.
			else {
				areas.insert(make_pair(picture[i][j], 1));
			}
		}
	}
	int number_of_area = 0;
	int max_size_of_one_area = 0;
	number_of_area = areas.size();
	for (auto it = areas.begin(); it != areas.end(); it++) {
		if (max_size_of_one_area < it->second) {
			max_size_of_one_area = it->second;
		}
	}
	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
	return answer;
}

void main() {
	int m = 4;
	int n = 4;
	vector<vector<int>> picture = { {1, 2, 3, 4}, {4, 3, 2, 1}, {2, 2, 2, 3}, {1, 2, 2, 1} };

	multimap<int, int> areas;	//���� ���� picture[i][j]

	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
}