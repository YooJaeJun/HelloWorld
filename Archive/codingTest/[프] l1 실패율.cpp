#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

//���Ŀ�. vector<pair<int, double>>�� first�� Ű(�������� ����), second�� ��(������)
/*const bool cmp(const pair<int, double> a, const pair<int, double> b) {
	if (a.second == b.second) {
		return a.first < b.first;	//���� ���� �� Ű ��������
	}
	return a.second > b.second;
}*/

vector<int> solution(int N, vector<int> stages) {
	vector<int> answer;
	double fail_num = 0;
	double challenge_num = 0;
	unordered_map<int, double> fail_rate;	//<stage idx, ������>.
	for (int i = 1; i <= N; i++) {
		//�������� 1�� ����, ���� �Ǵ�
		for (const auto& elem : stages) {
			if (i < elem) {
				challenge_num++;
			}
			else if (i == elem) {
				fail_num++;
				challenge_num++;
			}
		}
		//0���� ���� ����� ���� ����
		if (challenge_num != 0) {
			fail_rate[i] = fail_num / challenge_num;
		}
		else {
			fail_rate[i] = 0;
		}
		fail_num = 0;
		challenge_num = 0;
	}
	//���Ŀ�
	/*vector<pair<int, double>> sort_rate(fail_rate.begin(), fail_rate.end());
	sort(sort_rate.begin(), sort_rate.end(), cmp);
	for (const auto& elem : sort_rate) {
		answer.push_back(elem.first);
	}*/
	vector<double> sort_rate;
	for (int i = 1; i <= N; i++) {
		sort_rate.push_back(fail_rate[i]);
	}
	sort(sort_rate.begin(), sort_rate.end(), greater<double>());
	for (int i = 0; i != sort_rate.size(); i++) {
		for (int j = 1; j <= fail_rate.size(); j++) {
			if (sort_rate[i] == fail_rate[j]) {
				answer.push_back(j);
				fail_rate[j] = -1;	//�� �߰��ϸ� Ű �������� �� ��ȿȭ(�ߺ� ��� ���)
			}
		}
	}
	return answer;
}