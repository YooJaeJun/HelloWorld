//�������� �̿� Ǯ��
#include <string>
#include <vector>

using namespace std;

const int sum_num(const int begin, const int end) {
	int n = (end - begin) / 1 + 1;	// ���� ���� n ���ϱ�. an = a + (n - 1)d
	int sum = (n * (begin + end)) / 2;	//�������� (n(a+l))/2
	return sum;
}

int solution(vector<int> numbers) {
	int answer = -1;
	const int begin = 0, end = 9;
	int sum = sum_num(begin, end);
	for (const int elem : numbers) {
		sum -= elem;
	}
	answer = sum;
	return answer;
}

//�հ� ���� �̿� Ǯ��
/*
#include <string>
#include <vector>

using namespace std;

const int sum_num(const int begin, const int end) {
	int sum = 0;
	for (int i = begin; i != end + 1; i++) {
		sum += (begin + i);
	}
	return sum;
}

int solution(vector<int> numbers) {
	int answer = -1;
	int sum = sum_num(0, 9);
	for (const int elem : numbers) {
		sum -= elem;
	}
	answer = sum;
	return answer;
}
*/
//�ݺ���, find ��� Ǯ��
/*
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> numbers) {
	int answer = -1;
	vector<int> notfind = { 0,1,2,3,4,5,6,7,8,9 };
	for (const auto& elem : numbers) {
		auto it = find(notfind.begin(), notfind.end(), elem);
		if (it != notfind.end()) {
			*it = 0;
		}
	}
	answer = 0;
	for (const int& elem : notfind) {
		if (elem != 0) {
			answer += elem;
		}
	}
	return answer;
}
*/