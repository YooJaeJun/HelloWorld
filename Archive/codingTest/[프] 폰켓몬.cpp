#include <vector>
#include <map>
using namespace std;

int solution(vector<int> nums)
{
	int answer = 0;
	map<int, int> poketmons;	//����, ����
	//������ ���� ����
	for (const int elem : nums) {
		auto it = poketmons.find(elem);
		if (it != poketmons.end()) {
			poketmons[elem]++;
		}
		else {
			poketmons[elem] = 1;
		}
	}
	//�˻�
	if (poketmons.size() <= nums.size() / 2) {
		answer = poketmons.size();
	}
	else {
		answer = nums.size() / 2;
	}
	return answer;
}
//unorderd_map ���