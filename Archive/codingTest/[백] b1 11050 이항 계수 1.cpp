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

// 파스칼 삼각형: 재귀 f(n - 1)(r - 1) + f(n - 1)(r)
// 10명 중 2명 무작위 선출 시, 
// x를 미리 뽑아두고 나머지 9명에서 1명을 뽑는 x가 선출되는 경우 
// + x를 미리 제외하고 나머지 9명에서 2명을 뽑아 x가 선축되지 않는 경우