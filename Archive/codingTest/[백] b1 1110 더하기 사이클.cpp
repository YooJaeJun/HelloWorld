#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	int n;
	cin >> n;
	int ans = n;
	int n1, n2, i = 0;
	do {
		n1 = n / 10;
		n2 = n - (n / 10 * 10);
		if (n1 + n2 >= 10) {
			n = n2 * 10 + n1 + n2 - 10;	// ���ο� �� = (��° �ڸ� * 10 + (ù° �ڸ� + ��° �ڸ�)). % 10 �ᵵ ��.
		}
		else {
			n = n2 * 10 + n1 + n2;
		}
		i++;
	} while (ans != n);
	cout << i;
	return 0;
}