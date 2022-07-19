#include <vector>
#include <map>
using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	multimap<int, int> areas;	//영역 원소 picture[i][j], 영역 개수
	multimap<int, int>::iterator final_it_for_overlap;
	bool is_primary;
	for (int i = 0; i != m; i++) {
		for (int j = 0; j != n; j++) {
			is_primary = false;
			//0이면 판단안함
			if (picture[i][j] == 0) {
				continue;
			}
			//키 중복을 위해 해당 키의 마지막 값 불러오기 (upper_bound()가 마지막 원소가 아닌 마지막 다음 원소를 가리키기 때문에 바로 못 씀)
			for (auto it = areas.lower_bound(picture[i][j]); it != areas.upper_bound(picture[i][j]); it++) {
				if (it != areas.end()) {
					final_it_for_overlap = it;
				}
			}
			//좌, 상단 원소로 최초 판단
			if (i > 0 && (picture[i][j] == picture[i - 1][j]) || (j > 0 && (picture[i][j] == picture[i][j - 1]))) {
				is_primary = true;
				areas.insert(make_pair(picture[i][j], 1));
			}
			//인접 원소로 연속성 판단
			if (is_primary || i < m - 1 && (picture[i][j] == picture[i + 1][j]) || (j < n - 1 && (picture[i][j] == picture[i][j + 1]))) {
				final_it_for_overlap->second++;
			}
			//연속성 없으면 새로 추가.
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

	multimap<int, int> areas;	//영역 원소 picture[i][j]

	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
}