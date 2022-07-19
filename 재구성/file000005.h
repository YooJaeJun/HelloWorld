#include <bits/stdc++.h>
using namespace std;
// #define int int64_t
using ll = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vector<int>>;

string dest;
vi remo(10, true);
int directPlusOrMinus = 1e9;
int zeroBtn = 0;

void bt(string& s, int idx) {
	if (s.size() == dest.size()) {
		int curZeroBtn = 0;
		if (s.size() > 1) {
			for (auto& elem : s) {
				if (elem == '0') curZeroBtn--;
				else break;
			}
		}
		if (directPlusOrMinus > abs(stoi(s) - stoi(dest))) {
			directPlusOrMinus = abs(stoi(s) - stoi(dest));
			zeroBtn = curZeroBtn;
		}
		return;
	}

	for (int i = idx; i < dest.size(); i++) {
		for (int num = 0; num <= 9; num++) {
			if (remo[num]) {
				s += to_string(num);
				bt(s, i + 1);
				s.pop_back();
			}
		}
	}
}

void solution() {
	cin >> dest;
	int n;
	cin >> n;

	for (int i = 0; i != n; i++) {
		int num;
		cin >> num;
		remo[num] = false;
	}

	string s;
	bt(s, 0);

	int direct = abs(stoi(dest) - 100);
	int btnDown = zeroBtn + dest.size() + directPlusOrMinus;
	if (direct < btnDown) cout << direct;
	else cout << btnDown;
}

int32_t main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int t = 1;
	// cin >> t;
	for (int i = 0; i != t; i++) { solution(); }
	return 0;
}