#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<string> v(n);
	string s;
	cin >> v[0];
	s = v[0];
	for (int i = 1; i != n; i++) {	//�Է°� �� ���ÿ�
		cin >> v[i];
		for (int j = 0; j != v[0].size(); j++) {
			if (v[i][j] != s[j]) {	//���� ���� �Ͱ� ��
				s[j] = '?';
			}
		}
	}
	cout << s;
	return 0;
}