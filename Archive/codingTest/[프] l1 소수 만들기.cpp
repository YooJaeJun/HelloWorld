#include <vector>
#include <iostream>
using namespace std;

const bool is_prime_num(const int n1, const int n2, const int n3) {
	int sum = n1 + n2 + n3;
	for (int i = 2; i != sum - 1; i++) {
		if (sum % i == 0) return false;
	}
	return true;
}

int solution(vector<int> nums) {
	int answer = -1;

	// [����] ��ư�� ������ ��� ���� �� �� �ֽ��ϴ�.
	cout << "Hello Cpp" << endl;

	answer = 0;
	for (int i = 0; i != nums.size() - 2; i++) {
		for (int j = i + 1; j != nums.size() - 1; j++) {
			for (int k = j + 1; k != nums.size(); k++) {
				if (is_prime_num(nums[i], nums[j], nums[k])) {
					answer++;
				}
			}
		}
	}
	return answer;
}