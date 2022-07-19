
//첫 풀이
#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;
	vector<int> day;

	//작업일 구하기
	for (int i = 0; i != progresses.size(); i++) {
		if (speeds.at(i) != 0) {
			if ((100 - progresses.at(i)) % speeds.at(i) != 0) {
				day.push_back(((100 - progresses.at(i)) / speeds.at(i)) + 1);
			}
			else {
				day.push_back(((100 - progresses.at(i)) / speeds.at(i)));
			}
		}
	}
	//answer 배열 요소에 1씩 할당
	int order = 0;
	answer.push_back(1);
	int max_day = 0;

	for (int i = 1; i != progresses.size(); i++) {
		if (day.at(i - 1) >= day.at(i)) {
			if (max_day < day.at(i - 1)) {
				max_day = day.at(i - 1);
			}
			answer.at(order)++;
		}
		else {
			if (max_day != 0 && max_day >= day.at(i)) {
				answer.at(order)++;
			}
			if (max_day < day.at(i)) {
				max_day = day.at(i);
				answer.push_back(1);
				order++;
			}
		}
	}


	return answer;
}







//개선 코드
#include <string>
#include <vector>
using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;
	vector<int> day;

	//작업일 구하기
	for (int i = 0; i != progresses.size(); i++) {
		if ((100 - progresses.at(i)) % speeds.at(i) != 0) {
			day.push_back(((100 - progresses.at(i)) / speeds.at(i)) + 1);
		}
		else {
			day.push_back(((100 - progresses.at(i)) / speeds.at(i)));
		}
	}

	size_t idx = 0;
	size_t i = 1;
	for (; i != day.size(); ++i) {
		if (day[idx] < day[i]) {
			answer.push_back(i - idx);
			idx = i;
		}
	}

	answer.push_back(i - idx);
	return answer;
}








//승윤님 단순 코드
#include <string>
#include <vector>

using namespace std;

void main() {
	vector<int> progresses = { 93, 30, 55 };
	vector<int> speeds = { 1, 3, 9 };
	vector<int> answer;
	const size_t total_size = progresses.size();
	size_t front_idx = 0;

	while (total_size != front_idx) {
		for (size_t i = front_idx; i != total_size; ++i) {
			progresses[i] += speeds[i];
		}

		if (progresses[front_idx] >= 100) {
			size_t completed_count = 0;
			for (; front_idx != total_size; ++front_idx) {
				if (progresses[front_idx] < 100) {
					break;
				}
				++completed_count;
			}
			answer.push_back(completed_count);
		}
	}
}