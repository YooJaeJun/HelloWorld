#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int main() {
	int x;
	cin >> x;
	if (x == 1) {
		cout << 1;
	}
	else if (x >= 2 && x <= 7) {
		cout << 2;
	}
	else {
		for (int i = 1;; i++) {
			int sum = 3 * i * (i + 1);		//ù��6, ���� 6�� ���������� ���� Ǯ� ��. (i(2a+(i-1)d))/2
			int sum_next = 3 * (i + 1) * (i + 2);
			if (x >= 2 + sum && x < 2 + sum_next) {	//��Ģ���� 2 + �������������� ���� �Ǵ�
				cout << i + 2;	//ĭ �� ����
				break;
			}
		}
	}
	return 0;
}