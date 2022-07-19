#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
using namespace std;

vector<int> palNum;
vector<bool> isPal(40001);
const int mod = 1e9 + 7;

void checkPal() {
	for (int i = 1; i <= 40000; i++) {
		bool flag = true;
		string s = to_string(i);

		for (int j = 0; j != s.size() / 2 && flag; j++) {
			if (s[j] != s[s.size() - 1 - j]) {
				flag = false;
			}
		}
		if (flag) {
			isPal[i] = true;
			palNum.push_back(i);
		}
	}
}

void solution() {
	int n;
	cin >> n;

	vector<vector<int>> dp(n + 1, vector<int>(palNum.size()));

	for (int i = 1; i <= n; i++) {
		dp[i][1] = 1;
	}
	for (int j = 1; j <= n; j++) {
		dp[1][j] = j;
	}

	for (int i = 2; i <= n; i++) {
		for (int j = 2; j <= n; j++) {
			if (isPal[i]) {
				dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % mod;
			}
			else {
				dp[i][j] = dp[i - 1][j] % mod;
			}
		}
	}
	cout << dp[n][n];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	checkPal();

	int testCaseNum = 1;
	cin >> testCaseNum;
	for (int i = 0; i != testCaseNum; i++) { solution(); }
	return 0;
}