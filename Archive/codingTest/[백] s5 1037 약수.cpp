#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int t;
	cin >> t;
	vector<int> v(t);
	for (int i = 0; i != t; i++) {
		cin >> v[i];
	}
	//����� ����: ����� ������ ¦����, �߰� 2�� ��. ����� ������ Ȧ����, �߰� 1�� ����.
	sort(v.begin(), v.end());
	if (v.size() % 2 == 0) {
		cout << v[v.size() / 2 - 1] * v[v.size() / 2];
	}
	else {
		cout << v[v.size() / 2] * v[v.size() / 2];
	}
	return 0;
}
//����� �ּҰ��� �ִ밪�� �����ε� Ǯ�� ����