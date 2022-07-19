#include <string>
#include <vector>

using namespace std;

int solution(string s) {
	int answer = 0;
	string s2;
	for (int i = 1; i <= s.size(); i++) {
		for (int j = 0; j != i; j++) {
			s2 += s[j];
		}

		auto it = find(s.begin() + i, s.end(), s2);
		if (it != s.end()) {
			string num = "2";
			s2.insert(0, num);
		}

	}
	return answer;
}

void main() {
	solution("aabbaccc");
}