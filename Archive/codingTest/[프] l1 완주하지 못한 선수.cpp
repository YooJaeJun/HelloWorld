//����. �ؽ� �Ⱦ�. ȿ���� ����. �ؽ����� �� �����ٰ� ��.
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";

	sort(participant.begin(), participant.end());
	sort(completion.begin(), completion.end());
	for (int i = 0; i != participant.size(); i++) {
		if (i = participant.size() - 1 || participant[i] != completion[i]) {	//���������� ���ų� ���� ������
			answer = participant[i];
			break;
		}
	}
	return answer;
}


//ȿ���� ���г�
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