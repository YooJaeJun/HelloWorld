#include <bits/stdc++.h>
using namespace std;
#define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
const int mod = 1e9 + 7;

int n;
vvi nums;
vi v1(n), v2(n), v3(n);
int cnt = 0;
vi isUse;

void bt(int depth) {
	if (depth == n) {
		cnt++;
		return;
	}
	if (depth == n - 1) {
		for (auto& elem : v3) {
			if (elem == 0) {
				return;
			}
		}
		cnt++;
	}

	for (int i = depth; i != v3.size(); i++) {
		if (v3[i] == 0) {
			if (nums[i].size() == 0) continue;
			if (isUse[nums[i][0]] == false) {
				v3[i] = nums[i][0];
				isUse[v3[i]] = true;
				bt(i + 1);
				isUse[v3[i]] = false;
				v3[i] = 0;
			}

			if (nums[i].size() == 1) continue;
			if (isUse[nums[i][1]] == false) {
				v3[i] = nums[i][1];
				isUse[v3[i]] = true;
				bt(i + 1);
				isUse[v3[i]] = false;
				v3[i] = 0;
			}
		}
	}
}

void solution() {
	cin >> n;
	v1 = vi(n), v2 = vi(n), v3 = vi(n);
	nums = vvi(n + 1);
	isUse = vi(n + 1, false);
	cnt = 0;

	for (int i = 0; i != n; i++) {
		cin >> v1[i];
	}
	for (int i = 0; i != n; i++) {
		cin >> v2[i];
	}

	for (int i = 0; i != n; i++) {
		cin >> v3[i];
		if (v3[i] == 0) {
			if (v1[i] != v2[i]) {
				nums[i].push_back(v1[i]);
				nums[i].push_back(v2[i]);
			}
			else {
				v3[i] = v1[i];
			}
		}
		else {
			isUse[v3[i]] = true;
		}
	}

	bt(0);
	if (v3.size() == 1) cnt = 1;
	cout << cnt << '\n';
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	cin >> t;
	for (int i = 0; i != t; i++) { solution(); }
	return 0;
}