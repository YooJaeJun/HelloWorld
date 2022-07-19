#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int d(const int i) {
	if (i < 100) {
		return i + (i / 10) + i % 10;
	}
	else if (i < 1000) {
		return i + (i / 100) + (i % 100 / 10) + i % 10;
	}
	else if (i < 10000) {
		return i + (i / 1000) + (i % 1000 / 100) + (i % 100 / 10) + i % 10;
	}
	else {
		return 10001;
	}
}
int main() {
	vector<int> v;
	for (int i = 1; i != 10000; i++) {
		v.push_back(d(i));
	}
	vector<int> ans;
	for (int i = 1; i <= 10000; i++) {
		ans.push_back(i);
	}
	int idx = 0;
	for (const auto& elem : v) {
		auto it = find(ans.begin() + idx, ans.end(), elem);
		if (it != ans.end()) {
			ans.erase(it);
		}
	}
	for (const auto& elem : ans) {
		printf("%d\n", elem);
	}
	return 0;
}

//다른 사람 풀이
/*
#include <stdio.h>

int addr(int num) {
	int ret;
	ret = num;
	while (num) {
		ret += (num % 10);
		num /= 10;
	}
	return (ret);
}

int main() {
	bool arr[10001] = { 0 };
	int tmp;
	for (int i = 1; i < 10001; i++) {
		tmp = addr(i);
		if (tmp < 10001)
			arr[tmp] = 1;
	}
	for (int i = 1; i < 10001; i++)
	{
		if (!arr[i])
			printf("%d\n", i);
	}
}
*/