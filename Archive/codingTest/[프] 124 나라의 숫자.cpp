#include <iostream>
#include <string>
#include <vector>
using namespace std;

string solution(int n) {
    string answer;
    char tmp;
    int share, rest;
    share = n;
    while (true) {
        //3������ ����. ��, 0�� ��� 3���� ������ �������� -1 ó��
        if (share % 3 == 0) {
            rest = 3;
            share = share / 3 - 1;
        }
        else {
            rest = share % 3;
            share = share / 3;
        }
        if (rest == 3) { rest = 4; }
        answer.insert(answer.begin(), rest + '0');
        if (share < 3) {
            answer.insert(answer.begin(), share + '0');
            break;
        }
    }
    if (answer.front() == '0') {
        answer.erase(answer.begin());
    }
    return answer;
}

void main() {
    cout << solution(15);
}