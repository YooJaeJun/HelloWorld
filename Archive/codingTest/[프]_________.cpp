#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> solution(vector<string> orders, vector<int> course) {
    vector<string> answer;
    for (int i = 0; i != orders.size(); i++) {
        for (int j = 0; j != orders.size(); j++) {
            if (i != j) {
                string tmp;
                for (const char& elem : orders[j]) {
                    if (orders[i].find(elem) != string::npos) {
                        tmp += elem;
                    }
                }
                if (tmp.size() >= 2) {
                    answer.push_back(tmp);
                }
            }
        }
    }// vs에 주문 횟수 2회 이상인 것들이 주문횟수-1개 만큼 푸쉬됨.

    //중복 요소 제거
    for (string& elem : answer) {
        sort(elem.begin(), elem.end());
    }
    sort(answer.begin(), answer.end());
    answer.erase(unique(answer.begin(), answer.end()), answer.end());

    //코스 개수 맞는지 판단
    bool is_course_size = false;
    for (int i = 0; i != answer.size();) {
        for (const int c : course) {
            is_course_size = answer[i].size() == c ? true : false;
            if (is_course_size) {
                break;
            }
        }
        if (is_course_size) {
            i++;
        }
        else {
            answer.erase(answer.begin() + i);
        }
    }

    return answer;
}

int main() {

    cout << solution({ "ABCDE", "AB", "CD", "ADE", "XYZ", "XYZ", "ACD" }, { 2, 3, 5 })[0];
}