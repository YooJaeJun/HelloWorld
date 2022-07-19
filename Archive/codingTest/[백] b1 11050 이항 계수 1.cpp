#include <iostream>
using namespace std;

int fac(int x) {
	int mul = 1;
	for (int i = 1; i <= x; i++) {
		mul *= i;
	}
	return mul;
}

int main() {
	int n, k;
	cin >> n >> k;

	if (k > n) {
		cout << "0";
		return 0;
	}
	else {
		cout << fac(n) / (fac(k) * fac(n - k));
	}

	return 0;
}

// �Ľ�Į �ﰢ��: ��� f(n - 1)(r - 1) + f(n - 1)(r)
// 10�� �� 2�� ������ ���� ��, 
// x�� �̸� �̾Ƶΰ� ������ 9���� 1���� �̴� x�� ����Ǵ� ��� 
// + x�� �̸� �����ϰ� ������ 9���� 2���� �̾� x�� ������� �ʴ� ���