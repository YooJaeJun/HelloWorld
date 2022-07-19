#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	deque<int> dq;
	for (int i = 1; i <= n; i++) {
		dq.push_back(i);
	}
	int sum = 0;
	for (int i = 0; i != m; i++) {
		int x;
		cin >> x;
		auto it = find(dq.begin(), dq.end(), x);
		//�� �� �� ������� �������
		//end�� ������ �����̴� - 1 ���ص� ��
		if (it - dq.begin() <= dq.end() - it) {
			int num = it - dq.begin();
			sum += num;
			for (int j = 0; j != num; j++) {
				dq.push_back(dq.front());
				dq.pop_front();
			}
			dq.pop_front();
		}
		else if (it - dq.begin() > dq.end() - it) {
			int num = dq.end() - it;
			sum += num;
			for (int j = 0; j != num; j++) {
				dq.push_front(dq.back());
				dq.pop_back();
			}
			dq.pop_front();
		}
	}
	cout << sum;
	return 0;
}