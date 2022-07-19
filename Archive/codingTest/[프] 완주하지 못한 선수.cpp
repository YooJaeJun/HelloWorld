//정렬. 해쉬 안씀. 효율성 성공. 해쉬보다 더 느리다고 함.
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";

	sort(participant.begin(), participant.end());
	sort(completion.begin(), completion.end());
	for (int i = 0; i != participant.size(); i++) {
		if (i = participant.size() - 1 || participant[i] != completion[i]) {	//마지막까지 없거나 같지 않으면
			answer = participant[i];
			break;
		}
	}
	return answer;
}


//효율성 실패남
/*
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";

	for (const auto& elem : completion) {
		auto it = find(participant.begin(), participant.end(), elem);
		participant.erase(it);
	}
	answer = participant.front();
	return answer;
}
*/