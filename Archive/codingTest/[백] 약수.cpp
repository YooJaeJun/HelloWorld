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
	//약수의 성질: 약수의 개수가 짝수면, 중간 2개 곱. 약수의 개수가 홀수면, 중간 1개 제곱.
	sort(v.begin(), v.end());
	if (v.size() % 2 == 0) {
		cout << v[v.size() / 2 - 1] * v[v.size() / 2];
	}
	else {
		cout << v[v.size() / 2] * v[v.size() / 2];
	}
	return 0;
}
//약수의 최소값과 최대값의 곱으로도 풀이 가능