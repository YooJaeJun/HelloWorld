#include <iostream>
#include <vector>
using namespace std;

void solution() {
	int l;
	cin >> l;
	string s;
	cin >> s;
	long long coef = 1;
	long long sum = 0;
	const long long m = 1234567891;
	for (auto& ch : s) {
		sum += (ch - 'a' + 1) * coef;
		sum %= m;
		coef *= 31;
		coef %= m;
	}
	cout << sum;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	solution();
	return 0;
}

/*
// 풀이분 shift 연산 왼쪽 5번 시 -hash ==> (2^5-1)*hash + c
unsigned long get_hash(string str)
{
	unsigned long hash = 0;
	int c;
	for (int i = (int)str.size() - 1; i >= 0; i--)
	{
		c = str[i] - 'a' + 1;
		hash = (((hash << 5) - hash) + c) % TABLE_SIZE;
		continue;
	}
	return hash % TABLE_SIZE;
}
*/